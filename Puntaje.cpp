#include "Puntaje.h"

// Constructor
Puntaje::Puntaje() : puntos(0) {
    // Inicializa los puntos a 0 al construir un objeto Puntaje
}

// Función para obtener los puntos actuales
int Puntaje::getPuntos() const {
    return puntos;
}

// Función para agregar puntos
void Puntaje::agregarPuntos(int cantidad) {
    puntos += cantidad;
}

// Función para resetear los puntos a 0
void Puntaje::resetearPuntos() {
    puntos = 0;
}
