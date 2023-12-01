#include "Puntaje.h"

// Constructor
Puntaje::Puntaje() : puntos(0) {
    // Inicializa los puntos a 0 al construir un objeto Puntaje
}

// Funci�n para obtener los puntos actuales
int Puntaje::getPuntos() const {
    return puntos;
}

// Funci�n para agregar puntos
void Puntaje::agregarPuntos(int cantidad) {
    puntos += cantidad;
}

// Funci�n para resetear los puntos a 0
void Puntaje::resetearPuntos() {
    puntos = 0;
}
