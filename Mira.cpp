#include "mira.h"

// Constructor
Mira::Mira(sf::Texture& texture) {
    sprite.setTexture(texture);  // Establecer la textura de la mira
    sprite.setScale(0.2f, 0.2f);  // Tama�o de la mira, setear a gusto
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);  // Establecer el origen en el centro
}


Mira::~Mira() {
}

// Eestablecer la posici�n
void Mira::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

// Obtener la posici�n actual de la mira
sf::Vector2f Mira::getPosition() const {
    return sprite.getPosition();
}

// Dibujar la mira en la ventana
void Mira::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}