# Embedded Systems Programming - Homework Assignment 2 - CRISTIAN DAVID CHALACA SALAS

## 📋 Descripción del Proyecto

Este proyecto implementa un **sistema de control en lazo cerrado** que monitorea un sensor y controla actuadores (LED y buzzer) basándose en umbrales predefinidos. El sistema fue desarrollado en tres etapas progresivas que practican conceptos esenciales de programación en C.

## 🎯 Objetivos Cumplidos

- ✅ **Proceso de compilación y enlazado** en C
- ✅ **Uso correcto de headers y `extern`**
- ✅ **Diseño de interfaces/wrappers** polimórficos
- ✅ **Control en lazo cerrado** con temporizaciones
- ✅ **Compilación cruzada** 64-bit y 32-bit

## 🏗️ Estructura del Proyecto

```
embedded-session-hw/
├── Makefile # Sistema de build para 64/32-bit
├── README.md 
├── ai_log.md # Registro de interacciones con IA
├── sensor/
│ ├── sensor.h # Interface del sensor
│ └── sensor.c # Implementación (random + CSV)
├── actuators/
│ ├── actuator.h # Interface polimórfica
│ ├── actuator.c # Funciones generales
│ ├── led_actuator.c # Implementación LED
│ └── buzzer_actuator.c # Implementación buzzer
├── controller/
│ └── ctl.c # Controlador principal
└── tests/
├── sensor_feed.csv # Datos de prueba
├── test_sensor.c # Test del sensor
└── test_actuators.c # Test de actuadores
```
## 🧩 Componentes Técnicos
### 1. Biblioteca del Sensor (sensor/)
- Header guards para prevenir inclusiones múltiples
- Uso correcto de extern para declaraciones
- Dos modos de operación: random y CSV replay
- Auto-inicialización segura

### 2. Interface Polimórfica de Actuadores (actuators/)
- Punteros a funciones para polimorfismo

- Estructuras encapsuladas para cada actuador

- Manejo uniforme de diferentes tipos

- Gestión automática de memoria

### 3. Controlador en Lazo Cerrado (controller/)
- Tiempo monotónico para precisión

- Timers independientes para cada actuador

- Manejo graceful de señales (Ctrl+C)

- Logging detallado con timestamps

## 🐛 Solución de Problemas
### Error de compilación 32-bit
```
# Si make ctl32 falla:
make install-32bit
sudo apt update
sudo apt install gcc-multilib
```
### Errores de enlazado
```
# Limpiar y recompilar
make clean
make ctl64
```
### Permisos de ejecución
```
chmod +x ctl64 ctl32
```

## 📈 Log de Ejecución Ejemplo

```
=== Iniciando controlador en lazo cerrado ===
Intervalo de muestreo: 100 ms
Umbral: 50.0
Presiona Ctrl+C para detener

[0.000] Sensor: 25.50, BAJO - Desactivación programada (Buzzer: +1s, LED: +5s)
[0.100] Sensor: 30.20, BAJO - Desactivación programada (Buzzer: +1s, LED: +5s)
[1.000] Buzzer apagado por timer
[5.000] LED apagado por timer
[10.100] Sensor: 75.90, ALTO - Activados inmediatamente
```

## 🔄 Reflexiones sobre el Desarrollo
### Errores de Compilación vs Enlazado
- Compilación: Resueltos con headers guards y declaraciones extern

- Enlazado: Solucionados con separación correcta .h/.c y Makefile

### Wrappers/Interfaces
- La interface polimórfica permite agregar nuevos actuadores fácilmente

- El sistema sensor puede extenderse con nuevos modos sin afectar el controlador

### Uso de Tiempo Monotónico
- Esencial para sistemas embebidos en tiempo real

- Previene problemas con ajustes de reloj del sistema


