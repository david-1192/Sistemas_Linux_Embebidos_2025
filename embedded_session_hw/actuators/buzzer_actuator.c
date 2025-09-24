#include "actuator.h"
#include <stdio.h>
#include <stdlib.h>

// Estructura específica para Buzzer
typedef struct {
    actuator_params_t base;  // Base común
    int frequency;          // Propiedad específica del buzzer
    int volume;            // Otra propiedad específica
} buzzer_params_t;

// Función de activación para Buzzer
static void buzzer_activate(void* params) {
    buzzer_params_t* buzzer = (buzzer_params_t*)params;
    buzzer->base.is_active = 1;
    buzzer->frequency = 1000; // Hz
    buzzer->volume = 80;      // %
    printf("BUZZER en pin %d ACTIVADO (freq: %dHz, vol: %d%%)\n", 
           buzzer->base.pin, buzzer->frequency, buzzer->volume);
}

// Función de desactivación para Buzzer
static void buzzer_deactivate(void* params) {
    buzzer_params_t* buzzer = (buzzer_params_t*)params;
    buzzer->base.is_active = 0;
    buzzer->frequency = 0;
    buzzer->volume = 0;
    printf("BUZZER en pin %d DESACTIVADO\n", buzzer->base.pin);
}

// Función de estado para Buzzer
static int buzzer_status(void* params) {
    buzzer_params_t* buzzer = (buzzer_params_t*)params;
    printf("BUZZER pin %d - Estado: %s, Frecuencia: %dHz, Volumen: %d%%\n", 
           buzzer->base.pin,
           buzzer->base.is_active ? "ACTIVO" : "INACTIVO",
           buzzer->frequency,
           buzzer->volume);
    return buzzer->base.is_active;
}

// Función para crear una instancia de Buzzer
actuator_t* buzzer_actuator_create(int pin) {
    // Reservar memoria para el actuador
    actuator_t* actuator = (actuator_t*)malloc(sizeof(actuator_t));
    if (!actuator) return NULL;
    
    // Reservar memoria para los parámetros específicos del buzzer
    buzzer_params_t* buzzer_params = (buzzer_params_t*)malloc(sizeof(buzzer_params_t));
    if (!buzzer_params) {
        free(actuator);
        return NULL;
    }
    
    // Inicializar parámetros del buzzer
    buzzer_params->base.pin = pin;
    buzzer_params->base.is_active = 0;
    buzzer_params->frequency = 0;
    buzzer_params->volume = 0;
    
    // Configurar el actuador con los punteros a funciones del buzzer
    actuator->params = buzzer_params;
    actuator->activate = buzzer_activate;
    actuator->deactivate = buzzer_deactivate;
    actuator->status = buzzer_status;
    
    printf("Buzzer actuator creado en pin %d\n", pin);
    return actuator;
}