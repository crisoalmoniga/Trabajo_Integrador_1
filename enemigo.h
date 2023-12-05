#pragma once

#include <SFML/Graphics.hpp>

class Enemigo {
public:
    Enemigo(sf::Texture& texture, float scale, sf::Vector2f position, int tiempoSpawn, int tiempoDesaparicion);

    void setScale(float scaleX, float scaleY);
    void update();
    void draw(sf::RenderWindow& window);
    void resetSpawnTimer();
    bool isClicked(sf::Vector2f mousePosition) const;
    void destroy();

private:
    sf::Sprite sprite;
    sf::Clock spawnTimer;
    sf::Clock despawnTimer;
    int tiempoSpawn;         // Tiempo de spawn en milisegundos
    int tiempoDesaparicion;  // Tiempo de desaparición en milisegundos
    bool visible;            // Indica si el enemigo está visible
};