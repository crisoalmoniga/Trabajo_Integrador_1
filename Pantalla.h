#pragma once
#include <SFML/Graphics.hpp>

class Pantalla {

public:

    Pantalla();

    sf::Texture texturaInicio;
    sf::Sprite spriteInicio;
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
    sf::Texture texturaPerdiste;
    sf::Sprite spritePerdiste;
    sf::Texture texturaGanaste;
    sf::Sprite spriteGanaste;

    sf::RenderWindow* ventana;

};