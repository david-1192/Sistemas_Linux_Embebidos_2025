## 🎯 Estrategia de Desarrollo

## 📝 Registro de Interacciones con IA Asistente

IA utilizada: **DeepSeek (latest version)**, 
modelo de lenguaje grande especializado en programación y análisis técnico.

### ¿Podrías explicarme qué son los guards de inclusión y por qué son necesarios?
Los guards de inclusión (#ifndef, #define, #endif) previenen la inclusión múltiple del mismo header. Son esenciales para evitar errores de redefinición cuando un header es incluido desde múltiples archivos.

### ¿Cómo uso correctamente 'extern' en las declaraciones de funciones?
'extern' se usa en headers para declarar que la definición está en otro archivo. En sensor.h debes usar 'extern void sensor_init(void);' mientras que en sensor.c defines la función sin extern.

### ¿Qué diferencia hay entre compilación y enlazado?
La compilación convierte código C a objeto (.c → .o), el enlazado combina múltiples .o en un ejecutable. Los errores de compilación son de sintaxis, los de enlazado son de símbolos no encontrados.

### ¿Cómo implemento polimorfismo en C sin clases?
Usando punteros a funciones y estructuras que contienen estos punteros. Cada "clase" (LED, buzzer) implementa sus propias funciones pero comparten la misma firma.

### ¿Qué es el tiempo monotónico y por qué usarlo en sistemas embebidos?
El tiempo monotónico (CLOCK_MONOTONIC) siempre avanza hacia adelante, no se afecta por ajustes del sistema. Es crucial para temporizadores precisos en sistemas de control.

### ¿Cómo manejo señales como Ctrl+C para apagado graceful?
Usando signal(SIGINT, handler) para capturar la interrupción. El handler debe limpiar recursos y cambiar una variable flag para salir del bucle principal.

### ¿Por qué separar declaraciones en .h y definiciones en .c?
Para permitir inclusión múltiple sin redefiniciones. Los .h declaran qué existe, los .c definen cómo funciona. Esto facilita la modularidad.

### ¿Cómo compilo para 32-bit en WSL?
Necesitas instalar gcc-multilib: 'sudo apt install gcc-multilib'. Luego compilas con 'gcc -m32' en lugar del compilador normal.

### ¿Qué herramientas uso para inspeccionar binarios?
'file' muestra arquitectura básica, 'readelf -h' da información detallada del header ELF como clase (32/64-bit) y máquina objetivo.

### ¿Cómo implemento un sistema de timers con tiempo monotónico?
Usando clock_gettime(CLOCK_MONOTONIC) para obtener tiempo actual, calculando diferencias en ms, y verificando si el tiempo objetivo ya pasó.

### ¿Qué ventajas tiene usar punteros a funciones para actuadores?
Permite tratar diferentes actuadores de manera uniforme. Puedes agregar nuevos actuadores sin modificar el código del controlador.

### ¿Cómo manejo memoria dinámica correctamente en C?
Cada malloc debe tener su free. En actuator_destroy liberamos tanto la estructura principal como los parámetros específicos.

### ¿Por qué usar static para variables internas del módulo?
'static' limita la visibilidad al archivo actual. Previene que otras partes del programa accedan accidentalmente a estado interno.

### ¿Cómo diseño una interface que permita extensibilidad?
Definiendo una estructura con punteros a funciones. Nuevos actuadores solo necesitan implementar estas funciones y registrarse.

### ¿Qué diferencia hay entre CLOCK_REALTIME y CLOCK_MONOTONIC?
CLOCK_REALTIME puede retroceder si el sistema ajusta la hora. CLOCK_MONOTONIC siempre avanza, ideal para intervalos y timeout.

### ¿Cómo logro que el sensor pueda usar tanto random como CSV?
Usando un enum para el modo y una función set_mode. En sensor_read, un switch decide qué implementación usar.

### ¿Qué debo considerar para el manejo de errores en sistemas embebidos?
Verificar retornos de funciones, tener valores por defecto, limpiar recursos en fallos, y logging informativo para diagnóstico.

### ¿Cómo aseguro que mi Makefile compile correctamente para ambas arquitecturas?
Definiendo targets separados para 32 y 64-bit, con flags específicos. Usando variables para no duplicar código.

### ¿Por qué es importante el logging en sistemas de control?
Permite debuggear sin detener el sistema. Los timestamps ayudan a entender secuencias de eventos y timing issues.

### ¿Cómo diseño un sistema que responda en tiempo real?
Midiendo tiempos con precisión, procesando eventos rápidamente, y usando delays no bloqueantes como usleep en lugar de sleep.

### ¿Qué patrones de diseño aplican mejor en C para sistemas embebidos?
Factory pattern para crear actuadores, Strategy pattern para los diferentes comportamientos, y Module pattern para encapsulación.

## 🎯 Estrategia de Desarrollo con IA

### Consultas Técnicas Específicas
Cada pregunta abordaba un concepto técnico específico necesario para cumplir con los requisitos del proyecto. La IA proporcionaba explicaciones conceptuales junto con ejemplos de código relevantes.

### Refinamiento Iterativo
Las implementaciones evolucionaron mediante preguntas de seguimiento como "¿cómo manejo el caso donde el CSV no existe?" o "¿qué pasa si un actuador falla al crearse?" llevando a código más robusto.

### Validación de Conceptos
Antes de implementar, confirmaba entendimiento con preguntas como "¿esta aproximación al polimorfismo es la correcta para C?" asegurando que las soluciones fueran idiomáticas.

### Resultado del Proceso Colaborativo

El diálogo técnico permitió construir un sistema que no solo funciona, sino que demuestra comprensión profunda de los conceptos de sistemas embebidos. Cada componente fue diseñado considerando extensibilidad, mantenibilidad y corrección técnica.

La combinación de preguntas conceptuales y de implementación resultó en un proyecto que cumple todos los requisitos mientras mantiene código limpio y bien documentado.


### Uso de IA como Asistente
- **Consultas específicas**: Cada prompt abordaba un problema concreto
- **Verificación técnica**: Todas las implementaciones fueron validadas conceptualmente
- **Aprendizaje activo**: La IA explicaba el "porqué" de cada solución

- **Comprensión inicial** del enunciado y requisitos
- **Implementación modular** por componentes
- **Integración progresiva** y pruebas

## 📊 Resultados Obtenidos

### Código Funcional
- ✅ Sistema de control en lazo cerrado operativo
- ✅ Compilación 64-bit y 32-bit exitosa
- ✅ Pruebas individuales y integradas funcionando

### Cumplimiento de Requisitos
- ✅ Headers con guards y `extern` correctos
- ✅ Interface polimórfica demostrada
- ✅ Makefile con targets específicos
- ✅ Documentación de uso de IA

### Aprendizajes Demostrados
- Proceso de compilación y enlazado en C
- Diseño de interfaces y wrappers
- Programación para sistemas embebidos
- Uso efectivo de herramientas de asistencia

---

*Este log documenta el proceso de desarrollo colaborativo con IA, manteniendo el enfoque en el aprendizaje y comprensión conceptual.*