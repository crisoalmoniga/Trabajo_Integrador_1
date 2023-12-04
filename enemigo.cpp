#include "Enemigo.h"

// Constructor
Enemigo::Enemigo(sf::Texture& texture, float scale) : vivo(true) {
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
    sprite.setPosition(rand() % 800, rand() % 800);
    temporizador.restart();
}

// Funci�n para actualizar la l�gica del enemigo
void Enemigo::actualizar() {
    if (vivo && temporizador.getElapsedTime().asSeconds() > 0.9) {
        // Realiza alguna l�gica aqu� cuando ha pasado 0.9 segundos
        temporizador.restart();  // Reinicia el temporizador
    }
}

// Funci�n para marcar al enemigo como muerto
void Enemigo::morir() {
    vivo = false;
}

// Funci�n para verificar si el enemigo est� vivo
bool Enemigo::estaVivo() const {
    return vivo;
}

// Funci�n para obtener el sprite del enemigo
sf::Sprite& Enemigo::getSprite() {
    return sprite;
}