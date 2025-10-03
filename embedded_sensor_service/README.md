# Embedded Sensor Service - Cristian David Chalaca Salas

Este proyecto implementa un servicio de **systemd** que simula la lectura de un sensor y escribe periódicamente sus valores en un archivo de log.  
El programa está escrito en **C** y empaquetado como un servicio para ejecutarse automáticamente en Linux.

---

## 📂 Estructura del repositorio

embedded_sensor_service/
├─ src/assignment_sensor.c # Código fuente principal
├─ systemd/assignment_sensor.service # Archivo de unidad systemd
├─ Makefile # Compilación con make
├─ tests/ # Scripts y notas de pruebas
├─ ai/ # Evidencia de uso de AI
└─ README.md # Este archivo

yaml
Copiar código

---

## ⚙️ Prerrequisitos

- Linux con `systemd` >= 245  
- Compilador C (ej. `gcc`)  
- Permisos `sudo` para instalar binarios y unidades systemd  

---

## 🔨 Clonación y compilación

```bash
git clone <URL_DEL_REPO>
cd embedded_sensor_service
make
```
El binario resultante quedará en:

```bash
./build/assignment_sensor
```

## 📦 Instalación del servicio
Copiar el binario y la unidad systemd:
```bash
sudo cp build/assignment_sensor /usr/local/bin/
sudo cp systemd/assignment_sensor.service /etc/systemd/system/
sudo systemctl daemon-reload
sudo systemctl enable --now assignment_sensor.service
```

## ⚙️ Configuración
El programa acepta parámetros opcionales:

```bash
assignment_sensor [--interval <segundos>] [--logfile <ruta>] [--device <ruta>]
```

- `--interval:` intervalo en segundos entre muestras (default: 5s)

- `--logfile:` ruta del archivo de log (default: /tmp/assignment_sensor.log)

- `--device:` dispositivo mock a leer (default: /dev/urandom)

## 📌 Fallback del log
Si `/tmp` no es escribible, el programa usará `/var/tmp/assignment_sensor.log` como ruta de respaldo.

## 🧪 Pruebas
1. Verificar que el servicio corre

```bash
systemctl status assignment_sensor.service
```
Debe mostrar active (running).

2. Ver logs generados
```bash
tail -f /tmp/assignment_sensor.log
```
Ejemplo:

```bash
2025-10-02T23:23:24Z | 0x549669B6
2025-10-02T23:23:29Z | 0x4F9B2FAF
```
3. Prueba de parada limpia (SIGTERM)
```bash
sudo systemctl stop assignment_sensor.service
```
El servicio debe detenerse sin errores y cerrar correctamente el archivo.

4. Prueba de reinicio automático
```bash
pgrep -f assignment_sensor
sudo kill -9 <PID>
```
Después de unos segundos, systemd lo reiniciará automáticamente.
Verificar con:

```bash
systemctl status assignment_sensor.service
```
5. Prueba de error
```bash
/usr/local/bin/assignment_sensor --device /dev/fake0
```
El programa debe fallar inmediatamente con un código de salida distinto de 0.

## 🗑️ Desinstalación
```bash
sudo systemctl disable --now assignment_sensor.service
sudo rm /etc/systemd/system/assignment_sensor.service
sudo rm /usr/local/bin/assignment_sensor
sudo systemctl daemon-reload
```
##📖 Notas
El servicio puede ejecutarse como usuario no-root agregando `User=...` en la unidad systemd y ajustando permisos del log.

El formato de log es *ISO-8601* con un valor aleatorio de 32 bits en hexadecimal.