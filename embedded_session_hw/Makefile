# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200112L

# Targets principales
TARGET_64 = ctl64
TARGET_32 = ctl32

# Directorios
SENSOR_DIR = sensor
ACTUATORS_DIR = actuators
CONTROLLER_DIR = controller
TESTS_DIR = tests

# Archivos objeto para 64-bit
SENSOR_OBJ_64 = $(SENSOR_DIR)/sensor_64.o
ACTUATOR_OBJ_64 = $(ACTUATORS_DIR)/actuator_64.o
LED_OBJ_64 = $(ACTUATORS_DIR)/led_actuator_64.o
BUZZER_OBJ_64 = $(ACTUATORS_DIR)/buzzer_actuator_64.o
CONTROLLER_OBJ_64 = $(CONTROLLER_DIR)/ctl_64.o

# Archivos objeto para 32-bit
SENSOR_OBJ_32 = $(SENSOR_DIR)/sensor_32.o
ACTUATOR_OBJ_32 = $(ACTUATORS_DIR)/actuator_32.o
LED_OBJ_32 = $(ACTUATORS_DIR)/led_actuator_32.o
BUZZER_OBJ_32 = $(ACTUATORS_DIR)/buzzer_actuator_32.o
CONTROLLER_OBJ_32 = $(CONTROLLER_DIR)/ctl_32.o

# Targets de prueba
TEST_SENSOR = test_sensor
TEST_ACTUATORS = test_actuators

# Reglas principales
all: $(TARGET_64) $(TARGET_32)

# Target para 64-bit
$(TARGET_64): $(SENSOR_OBJ_64) $(ACTUATOR_OBJ_64) $(LED_OBJ_64) $(BUZZER_OBJ_64) $(CONTROLLER_OBJ_64)
	$(CC) $(CFLAGS) -o $@ $^

# Target para 32-bit (requiere herramientas de 32-bit)
$(TARGET_32): CC = gcc -m32
$(TARGET_32): $(SENSOR_OBJ_32) $(ACTUATOR_OBJ_32) $(LED_OBJ_32) $(BUZZER_OBJ_32) $(CONTROLLER_OBJ_32)
	$(CC) $(CFLAGS) -o $@ $^

# Compilación para 64-bit
$(SENSOR_DIR)/sensor_64.o: $(SENSOR_DIR)/sensor.c $(SENSOR_DIR)/sensor.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ACTUATORS_DIR)/actuator_64.o: $(ACTUATORS_DIR)/actuator.c $(ACTUATORS_DIR)/actuator.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ACTUATORS_DIR)/led_actuator_64.o: $(ACTUATORS_DIR)/led_actuator.c $(ACTUATORS_DIR)/actuator.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ACTUATORS_DIR)/buzzer_actuator_64.o: $(ACTUATORS_DIR)/buzzer_actuator.c $(ACTUATORS_DIR)/actuator.h
	$(CC) $(CFLAGS) -c $< -o $@

$(CONTROLLER_DIR)/ctl_64.o: $(CONTROLLER_DIR)/ctl.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilación para 32-bit
$(SENSOR_DIR)/sensor_32.o: $(SENSOR_DIR)/sensor.c $(SENSOR_DIR)/sensor.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ACTUATORS_DIR)/actuator_32.o: $(ACTUATORS_DIR)/actuator.c $(ACTUATORS_DIR)/actuator.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ACTUATORS_DIR)/led_actuator_32.o: $(ACTUATORS_DIR)/led_actuator.c $(ACTUATORS_DIR)/actuator.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ACTUATORS_DIR)/buzzer_actuator_32.o: $(ACTUATORS_DIR)/buzzer_actuator.c $(ACTUATORS_DIR)/actuator.h
	$(CC) $(CFLAGS) -c $< -o $@

$(CONTROLLER_DIR)/ctl_32.o: $(CONTROLLER_DIR)/ctl.c
	$(CC) $(CFLAGS) -c $< -o $@

# Targets de prueba
$(TEST_SENSOR): $(SENSOR_DIR)/sensor_64.o $(TESTS_DIR)/test_sensor_64.o
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_ACTUATORS): $(ACTUATOR_OBJ_64) $(LED_OBJ_64) $(BUZZER_OBJ_64) $(TESTS_DIR)/test_actuators_64.o
	$(CC) $(CFLAGS) -o $@ $^

$(TESTS_DIR)/test_sensor_64.o: $(TESTS_DIR)/test_sensor.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTS_DIR)/test_actuators_64.o: $(TESTS_DIR)/test_actuators.c
	$(CC) $(CFLAGS) -c $< -o $@

# Instalar herramientas para 32-bit en WSL
install-32bit:
	sudo apt update
	sudo apt install gcc-multilib

# Limpiar todo
clean:
	rm -f $(TARGET_64) $(TARGET_32) $(TEST_SENSOR) $(TEST_ACTUATORS) \
	      $(SENSOR_DIR)/*.o \
	      $(ACTUATORS_DIR)/*.o \
	      $(CONTROLLER_DIR)/*.o \
	      $(TESTS_DIR)/*.o

# Inspeccionar binarios
inspect: $(TARGET_64) $(TARGET_32)
	@echo "=== Inspección de binarios ==="
	@echo "64-bit:"
	@file $(TARGET_64)
	@readelf -h $(TARGET_64) | grep -E "(Class|Machine|Type)"
	@echo "32-bit:"
	@file $(TARGET_32)
	@readelf -h $(TARGET_32) | grep -E "(Class|Machine|Type)"

.PHONY: all clean install-32bit inspect