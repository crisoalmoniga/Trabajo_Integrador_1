#pragma once

#include <SFML/Graphics.hpp>

class Enemigo {
public:
    Enemigo(sf::Texture& texture, float scale, const sf::Vector2f& position, int tiempoSpawn, int tiempoDesaparicion);

    void update();
    void draw(sf::RenderWindow& window);
    bool isClicked(const sf::Vector2f& clickPosition);
    void destroy();

private:
    sf::Sprite sprite;
    int tiempoSpawn;
    int tiempoDesaparicion;
    sf::Clock spawnClock;
    sf::Clock desaparicionClock;
    bool destruido;

    void reset();
};