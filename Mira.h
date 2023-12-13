#pragma once
#include <SFML/Graphics.hpp>

class Mira {
public:

    Mira(sf::Texture& texture);
    ~Mira();

    // M�todo para establecer la posici�n de la mira
    void setPosition(float x, float y);

    // M�todo para obtener la posici�n actual de la mira
    sf::Vector2f getPosition() const;

    // M�todo para dibujar la mira en la ventana
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite;  // Objeto sprite para representar la mira en el juego
};