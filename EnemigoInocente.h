#pragma once

#include <SFML/Graphics.hpp>

class EnemigoInocente {
public:
    EnemigoInocente(sf::Texture& textureEnemigo, sf::Texture& textureInocente, sf::Vector2f posiciones[]);
    void cambiarPosicionYTexturaAleatoria();
    sf::Sprite getSprite() const;

private:
    sf::Sprite sprite;
    sf::Vector2f* posiciones;
    sf::Texture& textureEnemigo;
    sf::Texture& textureInocente;
};