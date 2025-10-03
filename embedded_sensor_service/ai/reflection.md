# *Reflection*

Usé un asistente de IA (ChatGPT GPT-5, septiembre-octubre 2025) durante el desarrollo del proyecto.  

- **Qué pregunté:** Empecé con dudas generales sobre qué es un servicio en Linux, luego pedí ayuda para diseñar el programa en C, hacer el Makefile, escribir la unidad de systemd y finalmente resolver dudas acerca del contenido del el README.  
- **Qué acepté:** Acepté la estructura de carpetas y el esqueleto del código en C, además del archivo .service propuesto. También adopté la mayoría de las pruebas sugeridas para validar el servicio.  
- **Qué rechacé o modifiqué:** En algunos casos la IA propuso rutas de log que me dieron problemas de permisos, tuve que ajustar manualmente los permisos en `/tmp`. También cambié algunos comandos (`pgrep` → `pgrep -f`) porque el nombre del proceso era largo.  
- **Validación:** Probé cada paso ejecutando el binario manualmente, usando `tail -f` para ver los logs, y verificando el estado con `systemctl status`. Además forcé fallos (usando `--device /dev/fake0`) para comprobar que el servicio respondiera correctamente.  
- **Aprendizaje:** La IA me ayudó a organizar el proyecto en bloques claros y a entender mejor cómo funciona systemd. También me mostró cómo documentar pruebas y fallback de logs.  
- **Conclusión:** La IA fue una herramienta útil para guiarme, pero yo fui responsable de probar, depurar y asegurarme de que el código realmente funcionara en mi entorno.
