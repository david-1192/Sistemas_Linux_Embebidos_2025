# System Monitor

Monitor del sistema en tiempo real que muestra información sobre memoria, CPU y carga del procesador.

## 🚀 Características

- **Memoria**: Total instalada, memoria física y virtual utilizada
- **Procesador**: Modelo, número de núcleos
- **Carga del CPU**: Uso porcentual por núcleo y total
- **Tiempo real**: Actualización cada 2 segundos

## 📋 Requisitos

- Sistema Linux con WSL (Ubuntu)
- GCC compilador
- Kernel Linux con sistema de archivos /proc

## 🛠️ Instalación y Compilación

```bash
# Compilar
make

# Ejecutar
./system_monitor