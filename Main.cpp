#include <SFML/Graphics.hpp>
#include "Mira.h"

int main() {
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "La Rosada");

    sf::Texture textura;
    if (!textura.loadFromFile("D:\\Universidad - Cris\\Videojuegos\\Universidad del Litoral\\MAVI\\Trabajo_Integrador_1\\Assets\\mira.png"))
    {//Manejo de error
    }

    Mira mira = Mira(textura);

    
    mira.sprite.setPosition(400, 300);
    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }
        }


        ventana.clear();
        ventana.draw(mira.sprite);
        ventana.display();
    }

    return 0;
}