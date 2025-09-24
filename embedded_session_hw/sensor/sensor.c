#include "sensor.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

// Estructura para el estado interno del sensor
typedef struct {
    int initialized;
    sensor_mode_t mode;
    FILE* csv_file;
    double* csv_values;
    int csv_count;
    int csv_index;
} sensor_state_t;

// Variable interna del módulo
static sensor_state_t state = {
    .initialized = 0,
    .mode = SENSOR_MODE_RANDOM,
    .csv_file = NULL,
    .csv_values = NULL,
    .csv_count = 0,
    .csv_index = 0
};

// Función para leer valores desde CSV
static int read_csv_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: No se pudo abrir el archivo %s\n", filename);
        return 0;
    }
    
    // Contar líneas (valores)
    int count = 0;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file)) {
        count++;
    }
    
    if (count == 0) {
        fclose(file);
        return 0;
    }
    
    // Reservar memoria para los valores
    state.csv_values = (double*)malloc(count * sizeof(double));
    if (!state.csv_values) {
        fclose(file);
        return 0;
    }
    
    // Leer valores
    rewind(file);
    count = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        double value;
        if (sscanf(buffer, "%lf", &value) == 1) {
            state.csv_values[count++] = value;
        }
    }
    
    fclose(file);
    state.csv_count = count;
    state.csv_index = 0;
    
    printf("CSV cargado: %d valores\n", count);
    return 1;
}

void sensor_init(void) {
    if (!state.initialized) {
        srand(time(NULL));
        state.initialized = 1;
        printf("Sensor inicializado (modo: %s)\n", 
               state.mode == SENSOR_MODE_RANDOM ? "random" : "CSV");
    }
}

void sensor_set_mode(sensor_mode_t mode) {
    state.mode = mode;
    printf("Modo del sensor cambiado a: %s\n", 
           mode == SENSOR_MODE_RANDOM ? "random" : "CSV");
}

void sensor_set_csv_file(const char* filename) {
    if (state.csv_values) {
        free(state.csv_values);
        state.csv_values = NULL;
    }
    
    if (filename && read_csv_file(filename)) {
        state.mode = SENSOR_MODE_CSV;
    } else {
        state.mode = SENSOR_MODE_RANDOM;
    }
}

double sensor_read(void) {
    if (!state.initialized) {
        sensor_init();
    }
    
    double value;
    
    switch (state.mode) {
        case SENSOR_MODE_RANDOM:
            // Valor aleatorio entre 0.0 y 100.0
            value = (double)rand() / RAND_MAX * 100.0;
            break;
            
        case SENSOR_MODE_CSV:
            if (state.csv_count > 0) {
                value = state.csv_values[state.csv_index];
                state.csv_index = (state.csv_index + 1) % state.csv_count; // Loop
            } else {
                value = 0.0; // Fallback si no hay CSV
            }
            break;
            
        default:
            value = 0.0;
            break;
    }
    
    printf("Lectura del sensor: %.2f (modo: %s)\n", value,
           state.mode == SENSOR_MODE_RANDOM ? "random" : "CSV");
    
    return value;
}