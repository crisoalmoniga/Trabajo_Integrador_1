#pragma once
#include <SFML/Graphics.hpp>

class EnemigoInocente {
public:
    // Constructor de la clase
    EnemigoInocente(sf::Texture& textureEnemigo, sf::Texture& textureInocente, sf::Vector2f posiciones[]);

    // M�todo para cambiar la posici�n y la textura de manera aleatoria
    void cambiarPosicionYTexturaAleatoria();

    // M�todo para obtener el sprite del enemigo/inocente
    sf::Sprite getSprite() const;

private:
    sf::Sprite sprite;
    sf::Vector2f* posiciones;
    sf::Texture& textureEnemigo;
    sf::Texture& textureInocente;
};