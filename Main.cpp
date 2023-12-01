#include "Enemigo.h"
#include <iostream>
#include "Mira.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
    // Inicializaci�n
    srand(time(0));

    // Carga de texturas
    Texture enemigoTexture;
    Texture miraTexture;
    Texture fondoTexture;

    enemigoTexture.loadFromFile("enemigo.png");
    miraTexture.loadFromFile("mira.png");
    fondoTexture.loadFromFile("fondo.png");

    // Configuraci�n del cursor
    Sprite miraSprite(miraTexture);
    miraSprite.setScale(0.2f, 0.2f);
    miraSprite.setOrigin(miraSprite.getGlobalBounds().width / 2, miraSprite.getGlobalBounds().height / 2);

    // Configuraci�n de la ventana
    RenderWindow app(VideoMode(900, 900), "Clickale");

    // Elementos del juego
    std::vector<Enemigo> enemigos;
    int enemigosDerrotados = 0;

    Clock aparecerEnemigoTimer;
    Time tiempoEntreApariciones = seconds(0.9);

    // Sprite de fondo
    Sprite fondoSprite(fondoTexture);

    // Bucle principal
    while (app.isOpen()) {
        // Manejo de eventos
        Event event;
        while (app.pollEvent(event)) {
            if (event.type == Event::Closed) {
                app.close();
            }
            else if (event.type == Event::MouseMoved) {
                miraSprite.setPosition(event.mouseMove.x, event.mouseMove.y);
            }
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                // Comprobaci�n de clic en un enemigo
                for (Enemigo& enemigo : enemigos) {
                    if (enemigo.estaVivo() && enemigo.getSprite().getGlobalBounds().contains(miraSprite.getPosition())) {
                        enemigo.morir();
                        enemigosDerrotados++;
                    }
                }
            }
        }

        // Control de aparici�n de enemigos
        if (aparecerEnemigoTimer.getElapsedTime() >= tiempoEntreApariciones) {
            enemigos.emplace_back(enemigoTexture, 0.4f);
            aparecerEnemigoTimer.restart();
        }

        // Renderizado
        app.clear();

        // Dibuja el fondo
        app.draw(fondoSprite);

        // Dibuja enemigos vivos
        for (Enemigo& enemigo : enemigos) {
            if (enemigo.estaVivo()) {
                enemigo.actualizar();
                enemigo.getSprite().setScale(0.1f, 0.1f);
                app.draw(enemigo.getSprite());
            }
        }

        // Dibuja el cursor
        app.draw(miraSprite);

        app.display();

        // Condici�n de salida
        if (enemigosDerrotados >= 10) {
            app.close();
        }
    }

    return 0;
}
