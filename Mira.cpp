#include "mira.h"

Mira::Mira(sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setScale(0.2f, 0.2f);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

Mira::~Mira() {}

void Mira::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Vector2f Mira::getPosition() const {
    return sprite.getPosition();
}

void Mira::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}