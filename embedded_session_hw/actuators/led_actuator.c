#include "actuator.h"
#include <stdio.h>
#include <stdlib.h>

// Estructura específica para LED
typedef struct {
    actuator_params_t base;  // Base común
    int brightness;         // Propiedad específica del LED
} led_params_t;

// Función de activación para LED
static void led_activate(void* params) {
    led_params_t* led = (led_params_t*)params;
    led->base.is_active = 1;
    led->brightness = 100; // Brillo máximo
    printf("LED en pin %d ACTIVADO (brillo: %d%%)\n", led->base.pin, led->brightness);
}

// Función de desactivación para LED
static void led_deactivate(void* params) {
    led_params_t* led = (led_params_t*)params;
    led->base.is_active = 0;
    led->brightness = 0;
    printf("LED en pin %d DESACTIVADO\n", led->base.pin);
}

// Función de estado para LED
static int led_status(void* params) {
    led_params_t* led = (led_params_t*)params;
    printf("LED pin %d - Estado: %s, Brillo: %d%%\n", 
           led->base.pin, 
           led->base.is_active ? "ACTIVO" : "INACTIVO",
           led->brightness);
    return led->base.is_active;
}

// Función para crear una instancia de LED
actuator_t* led_actuator_create(int pin) {
    // Reservar memoria para el actuador
    actuator_t* actuator = (actuator_t*)malloc(sizeof(actuator_t));
    if (!actuator) return NULL;
    
    // Reservar memoria para los parámetros específicos del LED
    led_params_t* led_params = (led_params_t*)malloc(sizeof(led_params_t));
    if (!led_params) {
        free(actuator);
        return NULL;
    }
    
    // Inicializar parámetros del LED
    led_params->base.pin = pin;
    led_params->base.is_active = 0;
    led_params->brightness = 0;
    
    // Configurar el actuador con los punteros a funciones del LED
    actuator->params = led_params;
    actuator->activate = led_activate;
    actuator->deactivate = led_deactivate;
    actuator->status = led_status;
    
    printf("LED actuator creado en pin %d\n", pin);
    return actuator;
}