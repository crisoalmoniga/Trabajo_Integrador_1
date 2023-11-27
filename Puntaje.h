#pragma once

class Puntaje {

public:
    // Constructor
    Puntaje();

    // Funciones miembro
    int getPuntos() const;
    void agregarPuntos(int cantidad);
    void resetearPuntos();

private:
    // Variable miembro para almacenar los puntos
    int puntos;
};