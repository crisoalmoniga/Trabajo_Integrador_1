#include "EnemigoInocente.h"
#include <cstdlib>

EnemigoInocente::EnemigoInocente(sf::Texture& textureEnemigo, sf::Texture& textureInocente, sf::Vector2f posiciones[])
    : textureEnemigo(textureEnemigo), textureInocente(textureInocente), posiciones(posiciones) {
    sprite.setTexture(textureEnemigo);  // Establecer la textura del enemigo por defecto
    sprite.setPosition(this->posiciones[rand() % 6]);  // Posición inicial aleatoria
}

void EnemigoInocente::cambiarPosicionYTexturaAleatoria() {
    // Cambiar a una nueva posición aleatoria
    sprite.setPosition(posiciones[rand() % 6]);

    // Cambiar a una nueva textura aleatoria (enemigo o inocente)
    sprite.setTexture((rand() % 2 == 0) ? textureEnemigo : textureInocente);
}

sf::Sprite EnemigoInocente::getSprite() const {
    return sprite;
}