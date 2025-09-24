#!/bin/bash
echo "=== Probando sistema completo ==="

# Compilar
make clean
make ctl64

echo "=== Ejecutando controlador por 10 segundos ==="
timeout 10s ./ctl64 || true

echo "=== Inspección de binarios ==="
make inspect

echo "=== Test completado ==="