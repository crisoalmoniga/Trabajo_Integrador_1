#pragma once

#include <SFML/Graphics.hpp>

class Mira {
public:
    // Constructor
    Mira();

    // Funciones
    void cargarTextura(const std::string& ruta);
    void centrarEnVentana(const sf::RenderWindow& ventana);
    void dibujar(sf::RenderWindow& ventana);

private:
    // Sprite con la textura
    sf::Sprite sprite;

};

