#pragma once

#include <SFML/Graphics.hpp>

class Mira {
public:
    Mira(sf::Texture& texture);
    ~Mira();

    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite;
};