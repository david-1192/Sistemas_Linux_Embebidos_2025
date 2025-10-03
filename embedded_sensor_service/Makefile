# Nombre del binario
TARGET = assignment_sensor

# Carpeta de salida
BUILD_DIR = build

# Carpeta de código fuente
SRC_DIR = src

# Archivos fuente
SRC = $(SRC_DIR)/assignment_sensor.c

# Compilador y banderas
CC = gcc
CFLAGS = -Wall -O2

# Ruta completa del binario
BIN = $(BUILD_DIR)/$(TARGET)

# Regla por defecto: compilar
all: $(BIN)

# Crear la carpeta build si no existe y compilar
$(BIN): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Crear carpeta build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpiar archivos compilados
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
