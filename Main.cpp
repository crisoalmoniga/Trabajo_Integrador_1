#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "EnemigoInocente.h"
#include "Mira.h"
#include "Pantalla.h"

int main() {
    // Crear la ventana de inicio
    sf::RenderWindow App(sf::VideoMode(1024, 768), "Inicio");
    App.setFramerateLimit(60);

    // Instancias de clases para manejar pantallas del juego
    PantallaInicio pantallaInicio("inicio.png");
    PantallaFondo pantallaFondo("fondo.png");
    PantallaPerdiste pantallaPerdiste("perdiste.png");
    PantallaGanaste pantallaGanaste("ganaste.png");

    // Mostrar la pantalla de inicio
    pantallaInicio.mostrar(App);

    bool juegoIniciado = false;
    while (App.isOpen() && !juegoIniciado) {
        sf::Event event;
        while (App.pollEvent(event)) {
            // Manejar eventos de la ventana de inicio
            if (event.type == sf::Event::Closed) {
                App.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                juegoIniciado = true;
            }
        }
    }

    App.close();

    // Crear la ventana principal del juego
    sf::RenderWindow window(sf::VideoMode(1024, 768), "La mano en la lata");

    // Cargar texturas necesarias
    sf::Texture enemigoTexture;
    sf::Texture inocenteTexture;
    sf::Texture miraTexture;
    sf::Texture fondoTexture;
    sf::Texture perdisteTexture;
    sf::Texture ganasteTexture;

    if (!enemigoTexture.loadFromFile("enemigo.png") || !inocenteTexture.loadFromFile("inocente.png") || !miraTexture.loadFromFile("mira.png") || !fondoTexture.loadFromFile("fondo.png") || !perdisteTexture.loadFromFile("perdiste.png") || !ganasteTexture.loadFromFile("ganaste.png")) {
        return -1; // Salir si hay un error al cargar alguna textura
    }

    // Configurar propiedades de un sprite
    sf::Sprite sprite;
    sprite.setScale(1.2f, 1.2f);

    // Instancia de la clase Mira
    Mira mira(miraTexture);

    // Configurar sprites para el fondo, pantalla de derrota y pantalla de victoria
    sf::Sprite fondoSprite(fondoTexture);
    fondoSprite.setScale(window.getSize().x / fondoSprite.getLocalBounds().width, window.getSize().y / fondoSprite.getLocalBounds().height);

    sf::Sprite perdisteSprite(perdisteTexture);
    perdisteSprite.setScale(window.getSize().x / perdisteSprite.getLocalBounds().width, window.getSize().y / perdisteSprite.getLocalBounds().height);

    sf::Sprite ganasteSprite(ganasteTexture);
    ganasteSprite.setScale(window.getSize().x / ganasteSprite.getLocalBounds().width, window.getSize().y / ganasteSprite.getLocalBounds().height);

    // Variables de juego
    int puntos = 0;
    int vidas = 3;
    int enemigosMuertos = 0;

    sf::Clock tiempoEnPantalla;
    float tiempoLimite = 2.5f;

    srand(static_cast<unsigned int>(time(0)));

    // Posiciones iniciales de enemigos inocentes
    sf::Vector2f posiciones[6] = {
        sf::Vector2f(135.0f, 300.0f),
        sf::Vector2f(135.0f, 500.0f),
        sf::Vector2f(480.0f, 515.0f),
        sf::Vector2f(480.0f, 80.0f),
        sf::Vector2f(830.0f, 500.0f),
        sf::Vector2f(830.0f, 300.0f)
    };

    // Instancia de la clase EnemigoInocente
    EnemigoInocente enemigo(enemigoTexture, inocenteTexture, posiciones);

    bool juegoTerminado = false;
    sf::Clock tiempoPantallaFinal;

    // Bucle principal del juego
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Manejar eventos de la ventana principal
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Manejar clic izquierdo del mouse
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

                // Verificar si el clic ocurrió en un enemigo o inocente
                if (enemigo.getSprite().getGlobalBounds().contains(worldPosition)) {
                    if (enemigo.getSprite().getTexture() == &enemigoTexture) {
                        puntos += 10;
                        enemigosMuertos++;
                        enemigo.cambiarPosicionYTexturaAleatoria();
                        tiempoEnPantalla.restart();
                    }
                    else if (enemigo.getSprite().getTexture() == &inocenteTexture) {
                        vidas--;
                        enemigo.cambiarPosicionYTexturaAleatoria();
                        tiempoEnPantalla.restart();
                    }
                }
            }
        }

        // Actualizar posición de la mira según la posición del mouse
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        mira.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

        // Verificar tiempo de exposición del enemigo en pantalla
        if (tiempoEnPantalla.getElapsedTime().asSeconds() > tiempoLimite) {
            if (enemigo.getSprite().getTexture() == &enemigoTexture) {
                vidas--;
            }

            enemigo.cambiarPosicionYTexturaAleatoria();
            tiempoEnPantalla.restart();
        }

        // Limpiar la ventana y dibujar elementos
        window.clear();
        window.draw(fondoSprite);
        window.draw(enemigo.getSprite());
        mira.draw(window);

        // Configurar fuente para el texto
        sf::Font Fuente;
        if (Fuente.loadFromFile("EncodeSans-VariableFont_wdth,wght.ttf")) {
            // Dibujar texto en la ventana
            sf::Text textoPuntaje("Puntaje: " + std::to_string(puntos), Fuente, 30);
            textoPuntaje.setPosition(460, 710);
            window.draw(textoPuntaje);

            sf::Text textoVidas("Vidas: " + std::to_string(vidas), Fuente, 30);
            textoVidas.setPosition(40, 710);
            window.draw(textoVidas);

            sf::Text textoEnemigosMuertos("Corruptos muertos: " + std::to_string(enemigosMuertos), Fuente, 30);
            textoEnemigosMuertos.setPosition(730, 710);
            window.draw(textoEnemigosMuertos);

            // Mostrar pantalla de victoria o derrota según condiciones
            if (enemigosMuertos >= 10) {
                window.draw(ganasteSprite);
            }
            else if (vidas <= 0) {
                window.draw(perdisteSprite);
            }
        }

        // Mostrar la ventana
        window.display();

        // Verificar condiciones de fin de juego y mostrar pantalla final
        if (vidas <= 0 || enemigosMuertos >= 10) {
            if (!juegoTerminado) {
                tiempoPantallaFinal.restart();
                juegoTerminado = true;
            }

            if (enemigosMuertos >= 10) {
                window.draw(ganasteSprite);
            }
            else if (vidas <= 0) {
                window.draw(perdisteSprite);
            }

            // Cerrar la ventana después de 10 segundos en la pantalla final
            if (tiempoPantallaFinal.getElapsedTime().asSeconds() > 10.0f) {
                window.close();
            }
        }
    }

    return 0;
}