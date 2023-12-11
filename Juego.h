#pragma once
#include <SFML/Graphics.hpp>
#include "EnemigoInocente.h"
#include "mira.h"

class Juego {
public:
    Juego();

    void iniciar();

private:
    sf::RenderWindow ventana;
    sf::Texture enemigoTexture, inocenteTexture, miraTexture, fondoTexture, perdisteTexture, ganasteTexture;
    sf::Sprite sprite, miraSprite, fondoSprite, perdisteSprite, ganasteSprite;
    EnemigoInocente enemigo;
    sf::Font fuente;
    int puntos, vidas, enemigosMuertos;
    float tiempoLimite;
    bool juegoTerminado;
    sf::Clock tiempoPantallaFinal, tiempoEnPantalla;

    void inicializarVentanaInicio();
    void esperarInicioJuego();
    void cargarTexturas();
    void configurarSprites();
    void inicializarJuego();
    void manejarEventos();
    void actualizarSprites();
    void dibujar();
};
