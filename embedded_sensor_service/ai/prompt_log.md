# *Prompt Log*

## 1
**Pregunta:** ¿Qué es un servicio en Linux y cómo funciona con systemd?  
**Respuesta (resumen):** Un servicio es un proceso gestionado por systemd, que corre en segundo plano y puede iniciarse/detenerse con `systemctl`.  

## 2
**Pregunta:** Diseña un programa en C que simule la lectura de un sensor y guarde datos en un log.  
**Respuesta (resumen):** Se sugirió un programa en C que lee bytes desde `/dev/urandom` y escribe en un archivo con timestamp en formato ISO8601.  

## 3
**Pregunta:** ¿Cómo añado la opción de configurar el intervalo entre lecturas?  
**Respuesta (resumen):** Se explicó cómo usar `getopt` para aceptar `--interval <segundos>` y aplicar `sleep()` en el bucle principal.  

## 4
**Pregunta:** ¿Cómo manejo señales para terminar el programa correctamente?  
**Respuesta (resumen):** Se propuso capturar `SIGINT` y `SIGTERM` con `signal()`, asegurando cerrar el log antes de salir.  

## 5
**Pregunta:** Dame un Makefile simple para compilar este programa.  
**Respuesta (resumen):** Se entregó un Makefile con reglas para compilar (`make`), limpiar (`make clean`) y generar el binario en `/usr/local/bin`.  

## 6
**Pregunta:** ¿Cómo creo un archivo systemd .service para este binario?  
**Respuesta (resumen):** Se mostró una unidad con `ExecStart=/usr/local/bin/assignment_sensor`, `Restart=on-failure`, y `WantedBy=multi-user.target`.  

## 7
**Pregunta:** ¿Cómo pruebo el servicio manualmente antes de instalarlo?  
**Respuesta (resumen):** Se recomendó correr el binario directamente, verificar la salida en `/tmp/assignment_sensor.log`, y usar `tail -f`.  

## 8
**Pregunta:** ¿Cómo pruebo el servicio con systemd?  
**Respuesta (resumen):** Se explicó habilitarlo con `systemctl enable assignment_sensor`, iniciarlo con `systemctl start`, y revisar estado/logs con `systemctl status` y `journalctl`.  

## 9
**Pregunta:** ¿Cómo comprobar que el reinicio automático funciona si el proceso falla?  
**Respuesta (resumen):** Se recomendó matar el proceso con `kill -9` y confirmar que systemd lo relance gracias a `Restart=on-failure`.  

## 10
**Pregunta:** ¿Qué hago si el nombre del proceso es largo y `pgrep` no lo encuentra?  
**Respuesta (resumen):** Se sugirió usar `pgrep -f assignment_sensor` para buscar por nombre completo.  

## 11
**Pregunta:** ¿Cómo organizar un README.md claro para este proyecto?  
**Respuesta (resumen):** Se sugirió una plantilla con descripción, estructura del repositorio, instalación, pruebas y desinstalación.  

## 12
**Pregunta:** ¿Qué archivos necesito para documentar el uso de IA en este proyecto?  
**Respuesta (resumen):** Se indicó crear la carpeta `ai/` con `prompt-log.md`, `reflection.md` y `provenance.json`.  

## 13
**Pregunta:** ¿Qué debo escribir en cada archivo de la carpeta ai/?  
**Respuesta (resumen):** Se dieron ejemplos: `prompt-log.md` con historial resumido de prompts, `reflection.md` con análisis crítico del uso de IA, y `provenance.json` con información de procedencia del modelo usado.

## 14
**Pregunta:** ¿Cómo asegurar que el archivo de log tenga los permisos correctos para no dar errores de acceso?  
**Respuesta (resumen):** Se recomendó borrar cualquier log previo creado como root y permitir que el servicio lo genere con el usuario correcto, usando `rm` y luego `systemctl restart`.  

## 15
**Pregunta:** ¿Qué usuario debería ejecutar el servicio?  
**Respuesta (resumen):** Lo ideal es usar un usuario sin privilegios (`User=someuser` en el .service) para mayor seguridad, ajustando permisos del log si es necesario.  

## 16
**Pregunta:** ¿Cómo puedo verificar en tiempo real que el servicio está funcionando?  
**Respuesta (resumen):** Usando `tail -f /tmp/assignment_sensor.log` en una terminal mientras el servicio corre en segundo plano.  

## 17
**Pregunta:** ¿Cómo puedo cambiar dinámicamente el intervalo de muestreo?  
**Respuesta (resumen):** Se explicó que debe modificarse el archivo `.service` o ejecutar el binario con `--interval X` manualmente, y luego reiniciar el servicio.  

## 18
**Pregunta:** ¿Qué debo incluir en la documentación final para que alguien más pueda replicar el proyecto?  
**Respuesta (resumen):** Código fuente en C, Makefile, unidad `.service`, instrucciones de instalación/uso en README, y carpeta `ai/` con trazabilidad del uso de IA.
