#include "Puntaje.h"

// Implementación del constructor
Puntaje::Puntaje() : puntos(0) {}

// Implementación de la función getPuntos
int Puntaje::getPuntos() const {
    return puntos;
}

// Implementación de la función agregarPuntos
void Puntaje::agregarPuntos(int cantidad) {
    if (cantidad > 0) {
        puntos += cantidad;
    }
}

// Implementación de la función resetearPuntos
void Puntaje::resetearPuntos() {
    puntos = 0;
}