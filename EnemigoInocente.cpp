#include "EnemigoInocente.h"
#include <cstdlib>

// Constructor de la clase EnemigoInocente
EnemigoInocente::EnemigoInocente(sf::Texture& textureEnemigo, sf::Texture& textureInocente, sf::Vector2f posiciones[])
	: textureEnemigo(textureEnemigo), textureInocente(textureInocente), posiciones(posiciones) {
	// Configurar la textura del enemigo
	sprite.setTexture(textureEnemigo);
	// Establecer la posición inicial aleatoria entre las posiciones disponibles
	sprite.setPosition(this->posiciones[rand() % 6]);
}

// Método para cambiar la posición y la textura de manera aleatoria
void EnemigoInocente::cambiarPosicionYTexturaAleatoria() {
	// Cambiar a una nueva posición aleatoria
	sprite.setPosition(posiciones[rand() % 6]);

	// Cambiar a una nueva textura aleatoria (enemigo o inocente)
	sprite.setTexture((rand() % 2 == 0) ? textureEnemigo : textureInocente);
}

// Método para obtener el sprite del enemigo/inocente
sf::Sprite EnemigoInocente::getSprite() const {
	return sprite;
}