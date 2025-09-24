#include "actuator.h"
#include <stdio.h>
#include <stdlib.h>

// Funciones generales que trabajan con cualquier actuador
void actuator_activate(actuator_t* actuator) {
    if (actuator && actuator->activate) {
        actuator->activate(actuator->params);
    }
}

void actuator_deactivate(actuator_t* actuator) {
    if (actuator && actuator->deactivate) {
        actuator->deactivate(actuator->params);
    }
}

int actuator_status(actuator_t* actuator) {
    if (actuator && actuator->status) {
        return actuator->status(actuator->params);
    }
    return 0;
}

void actuator_destroy(actuator_t* actuator) {
    if (actuator) {
        if (actuator->params) {
            free(actuator->params);
        }
        free(actuator);
    }
}