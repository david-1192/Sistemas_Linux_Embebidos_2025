#include "../sensor/sensor.h"
#include <stdio.h>
#include <unistd.h> // Para sleep

int main() {
    printf("=== Test completo de la biblioteca del sensor ===\n");
    
    // Test 1: Modo aleatorio
    printf("\n--- Test 1: Modo Aleatorio ---\n");
    sensor_set_mode(SENSOR_MODE_RANDOM);
    sensor_init();
    
    for (int i = 0; i < 3; i++) {
        double value = sensor_read();
        printf("Lectura %d: %.2f\n", i+1, value);
        sleep(1);
    }
    
    // Test 2: Modo CSV
    printf("\n--- Test 2: Modo CSV ---\n");
    sensor_set_csv_file("tests/sensor_feed.csv");
    
    for (int i = 0; i < 5; i++) {
        double value = sensor_read();
        printf("Lectura %d: %.2f\n", i+1, value);
        sleep(1);
    }
    
    return 0;
}