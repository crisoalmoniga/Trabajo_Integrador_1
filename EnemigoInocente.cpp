#include "EnemigoInocente.h"
#include <cstdlib>

// Constructor de la clase EnemigoInocente
EnemigoInocente::EnemigoInocente(sf::Texture& textureEnemigo, sf::Texture& textureInocente, sf::Vector2f posiciones[])
	: textureEnemigo(textureEnemigo), textureInocente(textureInocente), posiciones(posiciones) {
	// Configurar la textura del enemigo
	sprite.setTexture(textureEnemigo);
	// Establecer la posici�n inicial aleatoria entre las posiciones disponibles
	sprite.setPosition(this->posiciones[rand() % 6]);
}

// M�todo para cambiar la posici�n y la textura de manera aleatoria
void EnemigoInocente::cambiarPosicionYTexturaAleatoria() {
	// Cambiar a una nueva posici�n aleatoria
	sprite.setPosition(posiciones[rand() % 6]);

	// Cambiar a una nueva textura aleatoria (enemigo o inocente)
	sprite.setTexture((rand() % 2 == 0) ? textureEnemigo : textureInocente);
}

// M�todo para obtener el sprite del enemigo/inocente
sf::Sprite EnemigoInocente::getSprite() const {
	return sprite;
}