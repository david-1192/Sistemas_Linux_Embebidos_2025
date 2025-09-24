#define _POSIX_C_SOURCE 199309L
#include "../sensor/sensor.h"
#include "../actuators/actuator.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

// Configuración del sistema
#define SAMPLE_INTERVAL_MS 100    // 100 ms entre lecturas
#define BUZZER_OFF_DELAY_MS 1000  // 1 segundo para apagar buzzer
#define LED_OFF_DELAY_MS 5000     // 5 segundos para apagar LED
#define THRESHOLD 50.0           // Umbral de activación

// Estructura para el estado del controlador
typedef struct {
    actuator_t* led;
    actuator_t* buzzer;
    double threshold;
    
    // Timers para desactivación retardada
    struct timespec buzzer_off_time;
    struct timespec led_off_time;
    
    // Estado actual
    int led_scheduled_off;
    int buzzer_scheduled_off;
} controller_t;

// Variable global para manejar señal de interrupción
static volatile int running = 1;

// Función para manejar Ctrl+C
void signal_handler(int sig) {
    running = 0;
    printf("\nApagando sistema...\n");
}

// Obtener tiempo monotónico actual
struct timespec get_monotonic_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts;
}

// Calcular diferencia en milisegundos entre dos tiempos
double time_diff_ms(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 + 
           (end.tv_nsec - start.tv_nsec) / 1000000.0;
}

// Verificar si un tiempo ya pasó
int is_time_elapsed(struct timespec target_time) {
    struct timespec current = get_monotonic_time();
    return time_diff_ms(target_time, current) >= 0;
}

// Inicializar el controlador
controller_t* controller_init(double threshold) {
    controller_t* ctl = malloc(sizeof(controller_t));
    if (!ctl) return NULL;
    
    // Crear actuadores
    ctl->led = led_actuator_create(13);
    ctl->buzzer = buzzer_actuator_create(7);
    ctl->threshold = threshold;
    
    // Inicializar timers
    ctl->buzzer_off_time = get_monotonic_time();
    ctl->led_off_time = get_monotonic_time();
    ctl->led_scheduled_off = 0;
    ctl->buzzer_scheduled_off = 0;
    
    if (!ctl->led || !ctl->buzzer) {
        free(ctl);
        return NULL;
    }
    
    printf("Controlador inicializado con umbral: %.1f\n", threshold);
    return ctl;
}

// Limpiar recursos del controlador
void controller_cleanup(controller_t* ctl) {
    if (ctl) {
        // Asegurar que todo esté apagado
        actuator_deactivate(ctl->buzzer);
        actuator_deactivate(ctl->led);
        
        actuator_destroy(ctl->buzzer);
        actuator_destroy(ctl->led);
        free(ctl);
    }
}

// Procesar una lectura del sensor
void process_sensor_reading(controller_t* ctl, double sensor_value) {
    struct timespec current_time = get_monotonic_time();
    
    // Log de la lectura
    printf("[%.3f] Sensor: %.2f, ", 
           time_diff_ms((struct timespec){0}, current_time) / 1000.0,
           sensor_value);
    
    if (sensor_value >= ctl->threshold) {
        // VALOR ALTO - Activar inmediatamente
        printf("ALTO - ");
        
        actuator_activate(ctl->led);
        actuator_activate(ctl->buzzer);
        
        // Cancelar timers de desactivación
        ctl->led_scheduled_off = 0;
        ctl->buzzer_scheduled_off = 0;
        
        printf("Activados inmediatamente\n");
    } else {
        // VALOR BAJO - Programar desactivación
        printf("BAJO - ");
        
        // Programar apagado del buzzer en 1 segundo
        ctl->buzzer_off_time = current_time;
        ctl->buzzer_off_time.tv_sec += BUZZER_OFF_DELAY_MS / 1000;
        ctl->buzzer_scheduled_off = 1;
        
        // Programar apagado del LED en 5 segundos
        ctl->led_off_time = current_time;
        ctl->led_off_time.tv_sec += LED_OFF_DELAY_MS / 1000;
        ctl->led_scheduled_off = 1;
        
        printf("Desactivación programada (Buzzer: +1s, LED: +5s)\n");
    }
}

// Verificar y ejecutar desactivaciones programadas
void check_scheduled_actions(controller_t* ctl) {
    if (ctl->buzzer_scheduled_off && is_time_elapsed(ctl->buzzer_off_time)) {
        actuator_deactivate(ctl->buzzer);
        ctl->buzzer_scheduled_off = 0;
        printf("Buzzer apagado por timer\n");
    }
    
    if (ctl->led_scheduled_off && is_time_elapsed(ctl->led_off_time)) {
        actuator_deactivate(ctl->led);
        ctl->led_scheduled_off = 0;
        printf("LED apagado por timer\n");
    }
}

// Bucle principal del controlador
void controller_run(controller_t* ctl) {
    struct timespec last_sample = get_monotonic_time();
    struct timespec next_sample = last_sample;
    
    printf("=== Iniciando controlador en lazo cerrado ===\n");
    printf("Intervalo de muestreo: %d ms\n", SAMPLE_INTERVAL_MS);
    printf("Umbral: %.1f\n", ctl->threshold);
    printf("Presiona Ctrl+C para detener\n\n");
    
    while (running) {
        struct timespec current_time = get_monotonic_time();
        
        // Verificar si es tiempo de tomar muestra
        if (time_diff_ms(last_sample, current_time) >= SAMPLE_INTERVAL_MS) {
            double sensor_value = sensor_read();
            process_sensor_reading(ctl, sensor_value);
            last_sample = current_time;
        }
        
        // Verificar acciones programadas
        check_scheduled_actions(ctl);
        
        // Pequeña pausa para no saturar la CPU
        usleep(10000); // 10 ms
    }
}

int main(int argc, char* argv[]) {
    // Configurar manejo de señal para Ctrl+C
    signal(SIGINT, signal_handler);
    
    // Inicializar sensor (usaremos modo CSV para pruebas consistentes)
    sensor_set_csv_file("tests/sensor_feed.csv");
    sensor_init();
    
    // Crear controlador
    controller_t* ctl = controller_init(THRESHOLD);
    if (!ctl) {
        fprintf(stderr, "Error al inicializar controlador\n");
        return 1;
    }
    
    // Ejecutar bucle principal
    controller_run(ctl);
    
    // Limpiar recursos
    controller_cleanup(ctl);
    printf("Sistema apagado correctamente\n");
    
    return 0;
}