#ifndef SENSOR_H
#define SENSOR_H

// Modos de operación del sensor
typedef enum {
    SENSOR_MODE_RANDOM,    // Valores aleatorios
    SENSOR_MODE_CSV        // Valores desde archivo CSV
} sensor_mode_t;

// Declaraciones de las funciones
extern void sensor_init(void);
extern void sensor_set_mode(sensor_mode_t mode);
extern void sensor_set_csv_file(const char* filename);
extern double sensor_read(void);

#endif /* SENSOR_H */