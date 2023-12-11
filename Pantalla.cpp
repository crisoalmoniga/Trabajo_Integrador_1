#include "Pantalla.h"

// Implementaci�n de PantallaInicio
PantallaInicio::PantallaInicio(const std::string& rutaTextura) {
    texturaInicio.loadFromFile(rutaTextura);
    spriteInicio.setTexture(texturaInicio);
}

void PantallaInicio::mostrar(sf::RenderWindow& window) {
    window.draw(spriteInicio);
    window.display();
}

// Implementaci�n de PantallaFondo
PantallaFondo::PantallaFondo(const std::string& rutaTextura) {
    texturaFondo.loadFromFile(rutaTextura);
    spriteFondo.setTexture(texturaFondo);
}

void PantallaFondo::mostrar(sf::RenderWindow& window) {
    window.draw(spriteFondo);
    // Aqu� puedes agregar m�s l�gica espec�fica de la pantalla de fondo si es necesario
}

// Implementaci�n de PantallaPerdiste
PantallaPerdiste::PantallaPerdiste(const std::string& rutaTextura) {
    texturaPerdiste.loadFromFile(rutaTextura);
    spritePerdiste.setTexture(texturaPerdiste);
}

void PantallaPerdiste::mostrar(sf::RenderWindow& window) {
    window.draw(spritePerdiste);
    // Aqu� puedes agregar m�s l�gica espec�fica de la pantalla de derrota si es necesario
}

// Implementaci�n de PantallaGanaste
PantallaGanaste::PantallaGanaste(const std::string& rutaTextura) {
    texturaGanaste.loadFromFile(rutaTextura);
    spriteGanaste.setTexture(texturaGanaste);
}

void PantallaGanaste::mostrar(sf::RenderWindow& window) {
    window.draw(spriteGanaste);
    // Aqu� puedes agregar m�s l�gica espec�fica de la pantalla de victoria si es necesario
}