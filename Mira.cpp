#include "Mira.h"

// Constructor
Mira::Mira() {}

// Función para cargar la textura desde un archivo
void Mira::cargarTextura(const std::string& nombreArchivo) {
    std::string rutaCompleta = "D:\\Universidad - Cris\\Videojuegos\\Universidad del Litoral\\MAVI\\Trabajo_Integrador_1\\Assets\\" + nombreArchivo + ".png";

    if (!textura.loadFromFile(rutaCompleta))
        throw std::runtime_error("Error al cargar la textura desde " + rutaCompleta);

    sprite.setTexture(textura);
}

// Función para centrar el sprite en la ventana
void Mira::centrarEnVentana(const sf::RenderWindow& ventana) {
    sprite.setPosition(
        (ventana.getSize().x - sprite.getGlobalBounds().width) / 2,
        (ventana.getSize().y - sprite.getGlobalBounds().height) / 2
    );
}

// Función para dibujar el sprite en una ventana
void Mira::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
}

