#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define LOGFILE "/tmp/assignment_sensor.log"
#define DEVICE "/dev/urandom"
#define DEFAULT_INTERVAL 5

// Variable global para detectar señal
volatile sig_atomic_t keep_running = 1;

// Manejador de SIGTERM
void handle_sigterm(int sig) {
    (void)sig; // evitar warning
    keep_running = 0;
}

int main(int argc, char *argv[]) {
    int interval = DEFAULT_INTERVAL;

    // Procesar argumento opcional --interval
    if (argc == 3 && strcmp(argv[1], "--interval") == 0) {
        interval = atoi(argv[2]);
        if (interval <= 0) {
            fprintf(stderr, "Intervalo inválido, usando valor por defecto (%d s)\n", DEFAULT_INTERVAL);
            interval = DEFAULT_INTERVAL;
        }
    }

    // Registrar manejador de señal SIGTERM
    signal(SIGTERM, handle_sigterm);
    signal(SIGINT, handle_sigterm); // opcional: también soporta Ctrl+C

    FILE *dev = fopen(DEVICE, "rb");
    if (!dev) {
        perror("Error abriendo /dev/urandom");
        return 1;
    }

    FILE *log = fopen(LOGFILE, "a");
    if (!log) {
        perror("Error abriendo log file");
        fclose(dev);
        return 1;
    }

    printf("Sampler iniciado: intervalo = %d s, log = %s\n", interval, LOGFILE);

    while (keep_running) {
        // Leer 4 bytes del "sensor"
        uint32_t value;
        if (fread(&value, sizeof(value), 1, dev) != 1) {
            perror("Error leyendo del dispositivo");
            break;
        }

        // Obtener hora en ISO-8601 (UTC)
        time_t now = time(NULL);
        struct tm *utc_time = gmtime(&now);
        char timestamp[64];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%SZ", utc_time);

        // Escribir en log
        fprintf(log, "%s | 0x%08X\n", timestamp, value);
        fflush(log);

        // Esperar intervalo (interrumpible por señal)
        sleep(interval);
    }

    printf("Recibida señal de terminación. Cerrando...\n");

    fclose(dev);
    fclose(log);
    return 0;
}
