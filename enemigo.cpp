#include "Enemigo.h"

// Constructor
Enemigo::Enemigo(sf::Texture& texture, float scale) : vivo(true) {
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
    sprite.setPosition(rand() % 800, rand() % 800);
    temporizador.restart();
}

// Función para actualizar la lógica del enemigo
void Enemigo::actualizar() {
    if (vivo && temporizador.getElapsedTime().asSeconds() > 0.9) {
        // Realiza alguna lógica aquí cuando ha pasado 0.9 segundos
        temporizador.restart();  // Reinicia el temporizador
    }
}

// Función para marcar al enemigo como muerto
void Enemigo::morir() {
    vivo = false;
}

// Función para verificar si el enemigo está vivo
bool Enemigo::estaVivo() const {
    return vivo;
}

// Función para obtener el sprite del enemigo
sf::Sprite& Enemigo::getSprite() {
    return sprite;
}