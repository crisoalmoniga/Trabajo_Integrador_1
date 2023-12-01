#pragma once

#include <SFML/Graphics.hpp>

class Enemigo {
public:
    // Constructor
    Enemigo(sf::Texture& texture, float scale);

    // Funciones miembro
    void actualizar();
    void morir();
    bool estaVivo() const;
    sf::Sprite& getSprite();

private:
    sf::Sprite sprite;
    bool vivo;
    sf::Clock temporizador;
};
