#include "Enemigo.h"

Enemigo::Enemigo(sf::Texture& texture, float scale, sf::Vector2f position, int tiempoSpawn, int tiempoDesaparicion)
    : tiempoSpawn(tiempoSpawn), tiempoDesaparicion(tiempoDesaparicion), visible(false) {
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
    sprite.setPosition(position);
    resetSpawnTimer();
}

void Enemigo::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}

bool Enemigo::isClicked(sf::Vector2f mousePosition) const {
    // Verifica si las coordenadas del mouse est�n dentro de los l�mites del enemigo
    return sprite.getGlobalBounds().contains(mousePosition);
}

void Enemigo::destroy() {
    // Marca el enemigo como destruido
    visible = false;
    despawnTimer.restart();
}

void Enemigo::update() {
    // Actualiza la l�gica del enemigo, controla la aparici�n y desaparici�n
    if (spawnTimer.getElapsedTime().asMilliseconds() > tiempoSpawn) {
        if (!visible) {
            visible = true;
            resetSpawnTimer();
        }
        if (despawnTimer.getElapsedTime().asMilliseconds() > tiempoDesaparicion) {
            visible = false;
            despawnTimer.restart();
        }
    }
}

void Enemigo::draw(sf::RenderWindow& window) {
    if (visible) {
        window.draw(sprite);
    }
}

void Enemigo::resetSpawnTimer() {
    spawnTimer.restart();
}
