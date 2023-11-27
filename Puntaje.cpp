#include "Puntaje.h"

// Implementaci�n del constructor
Puntaje::Puntaje() : puntos(0) {}

// Implementaci�n de la funci�n getPuntos
int Puntaje::getPuntos() const {
    return puntos;
}

// Implementaci�n de la funci�n agregarPuntos
void Puntaje::agregarPuntos(int cantidad) {
    if (cantidad > 0) {
        puntos += cantidad;
    }
}

// Implementaci�n de la funci�n resetearPuntos
void Puntaje::resetearPuntos() {
    puntos = 0;
}