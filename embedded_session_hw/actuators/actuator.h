#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <stdint.h>

// Estructura base para parámetros de actuadores
typedef struct {
    int pin;            // Pin del actuador (simulado)
    int is_active;      // Estado actual
} actuator_params_t;

// Estructura para la interface polimórfica
typedef struct {
    void* params;  // Parámetros específicos del actuador
    
    // Punteros a funciones - la "interface polimórfica"
    void (*activate)(void* params);
    void (*deactivate)(void* params);
    int (*status)(void* params);
} actuator_t;

// Funciones para crear instancias de actuadores
extern actuator_t* led_actuator_create(int pin);
extern actuator_t* buzzer_actuator_create(int pin);

// Funciones generales para manejar actuadores
extern void actuator_activate(actuator_t* actuator);
extern void actuator_deactivate(actuator_t* actuator);
extern int actuator_status(actuator_t* actuator);
extern void actuator_destroy(actuator_t* actuator);

#endif /* ACTUATOR_H */