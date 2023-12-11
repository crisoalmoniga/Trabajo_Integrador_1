#pragma once
#include <SFML/Graphics.hpp>

class Pantalla {
public:
    virtual void mostrar(sf::RenderWindow& window) = 0;
};

class PantallaInicio : public Pantalla {
private:
    sf::Texture texturaInicio;
    sf::Sprite spriteInicio;

public:
    PantallaInicio(const std::string& rutaTextura);
    void mostrar(sf::RenderWindow& window) override;
};

class PantallaFondo : public Pantalla {
private:
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;

public:
    PantallaFondo(const std::string& rutaTextura);
    void mostrar(sf::RenderWindow& window) override;
};

class PantallaPerdiste : public Pantalla {
private:
    sf::Texture texturaPerdiste;
    sf::Sprite spritePerdiste;

public:
    PantallaPerdiste(const std::string& rutaTextura);
    void mostrar(sf::RenderWindow& window) override;
};

class PantallaGanaste : public Pantalla {
private:
    sf::Texture texturaGanaste;
    sf::Sprite spriteGanaste;

public:
    PantallaGanaste(const std::string& rutaTextura);
    void mostrar(sf::RenderWindow& window) override;
};