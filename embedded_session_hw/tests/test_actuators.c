#include "../actuators/actuator.h"
#include <stdio.h>
#include <unistd.h>

// Función que demuestra polimorfismo - misma función para diferentes actuadores
void test_actuator(actuator_t* actuator, const char* name) {
    printf("\n=== Probando %s ===\n", name);
    
    // Ver estado inicial
    actuator_status(actuator);
    
    // Activar
    actuator_activate(actuator);
    
    // Ver estado activo
    actuator_status(actuator);
    
    // Desactivar después de 2 segundos
    sleep(2);
    actuator_deactivate(actuator);
    
    // Ver estado final
    actuator_status(actuator);
}

int main() {
    printf("=== DEMOSTRACIÓN DE POLIMORFISMO EN C ===\n");
    
    // Crear diferentes actuadores
    actuator_t* led = led_actuator_create(13);
    actuator_t* buzzer = buzzer_actuator_create(7);
    
    // Array polimórfico - diferentes tipos, misma interface
    actuator_t* actuators[] = {led, buzzer};
    const char* names[] = {"LED", "BUZZER"};
    
    // Probar cada actuador con la misma función
    for (int i = 0; i < 2; i++) {
        test_actuator(actuators[i], names[i]);
    }
    
    // Demostrar que podemos manejar diferentes tipos uniformemente
    printf("\n=== Manejo uniforme de diferentes actuadores ===\n");
    for (int i = 0; i < 2; i++) {
        printf("\nActivando %s:\n", names[i]);
        actuator_activate(actuators[i]);
        actuator_status(actuators[i]);
    }
    
    // Limpiar memoria
    for (int i = 0; i < 2; i++) {
        actuator_destroy(actuators[i]);
    }
    
    return 0;
}