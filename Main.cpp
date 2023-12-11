#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "EnemigoInocente.h"
#include "Mira.h"

int main() {
    // Crear la ventana de inicio
    sf::RenderWindow App(sf::VideoMode(1024, 768), "Inicio");
    App.setFramerateLimit(60);

    // Cargar la textura de la pantalla de inicio
    sf::Texture inicioTexture;
    if (!inicioTexture.loadFromFile("inicio.png")) {
        return -1;
    }

    // Configurar el sprite de la pantalla de inicio
    sf::Sprite inicioSprite(inicioTexture);
    inicioSprite.setScale(App.getSize().x / inicioSprite.getLocalBounds().width, App.getSize().y / inicioSprite.getLocalBounds().height);

    // Mostrar la ventana de inicio
    App.draw(inicioSprite);
    App.display();

    // Esperar hasta que el jugador presione un botón
    bool juegoIniciado = false;
    while (App.isOpen() && !juegoIniciado) {
        sf::Event event;
        while (App.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                App.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                // Iniciar el juego cuando se hace clic
                juegoIniciado = true;
            }
        }
    }

    // Cerrar la ventana de inicio
    App.close();


    // Crear la ventana del juego
    sf::RenderWindow window(sf::VideoMode(1024, 768), "La mano en la lata");
    // Cargar las texturas de los sprites
    sf::Texture enemigoTexture;
    sf::Texture inocenteTexture;
    sf::Texture miraTexture;
    sf::Texture fondoTexture;
    sf::Texture perdisteTexture;
    sf::Texture ganasteTexture;

    // Manejar error si la carga de la textura falla
    if (!enemigoTexture.loadFromFile("enemigo.png") || !inocenteTexture.loadFromFile("inocente.png") || !miraTexture.loadFromFile("mira.png") || !fondoTexture.loadFromFile("fondo.png") || !perdisteTexture.loadFromFile("perdiste.png") || !ganasteTexture.loadFromFile("ganaste.png")) {
        return -1;
    }

    // Configurar el sprite principal
    sf::Sprite sprite;
    sprite.setScale(1.2f, 1.2f);

    // Configurar la mira del mouse
    Mira mira(miraTexture);

    // Configurar el fondo
    sf::Sprite fondoSprite(fondoTexture);
    fondoSprite.setScale(window.getSize().x / fondoSprite.getLocalBounds().width, window.getSize().y / fondoSprite.getLocalBounds().height);

    // Configurar el sprite de la pantalla de derrota
    sf::Sprite perdisteSprite(perdisteTexture);
    perdisteSprite.setScale(window.getSize().x / perdisteSprite.getLocalBounds().width, window.getSize().y / perdisteSprite.getLocalBounds().height);

    // Configurar el sprite de la pantalla de victoria
    sf::Sprite ganasteSprite(ganasteTexture);
    ganasteSprite.setScale(window.getSize().x / ganasteSprite.getLocalBounds().width, window.getSize().y / ganasteSprite.getLocalBounds().height);

    // Inicializar el puntaje, las vidas y el contador de enemigos muertos
    int puntos = 0;
    int vidas = 3;
    int enemigosMuertos = 0;

    // Configurar el temporizador
    sf::Clock tiempoEnPantalla;
    float tiempoLimite = 2.5f;

    // Semilla para la generación de números aleatorios
    srand(static_cast<unsigned int>(time(0)));

    // Definir posiciones predefinidas para los sprites
    sf::Vector2f posiciones[6] = {
        sf::Vector2f(135.0f, 300.0f),  // Sprite arriba izquierda
        sf::Vector2f(135.0f, 500.0f),  // Sprite abajo izquierda
        sf::Vector2f(480.0f, 515.0f),  // Sprite abajo al centro
        sf::Vector2f(480.0f, 80.0f),   // Sprite arriba al centro
        sf::Vector2f(830.0f, 500.0f),  // Sprite abajo derecha
        sf::Vector2f(830.0f, 300.0f)   // Sprite arriba derecha
    };

    // Inicializar con una posición y textura aleatoria
    EnemigoInocente enemigo(enemigoTexture, inocenteTexture, posiciones);

    // Bucle principal del juego
    bool juegoTerminado = false;
    sf::Clock tiempoPantallaFinal;

    while (window.isOpen()) {
        // Manejar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Obtener la posición del ratón en el mundo
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

                // Verificar si el clic ocurrió dentro del sprite
                if (enemigo.getSprite().getGlobalBounds().contains(worldPosition)) {
                    if (enemigo.getSprite().getTexture() == &enemigoTexture) {
                        // Sumar puntos por matar al enemigo
                        puntos += 10;

                        // Incrementar el contador de enemigos muertos
                        enemigosMuertos++;

                        // Cambiar a una nueva posición y textura aleatoria
                        enemigo.cambiarPosicionYTexturaAleatoria();

                        // Reiniciar el temporizador
                        tiempoEnPantalla.restart();
                    }
                    else if (enemigo.getSprite().getTexture() == &inocenteTexture) {
                        // Restar 1 vida por matar al inocente
                        vidas--;

                        // Cambiar a una nueva posición y textura aleatoria
                        enemigo.cambiarPosicionYTexturaAleatoria();

                        // Reiniciar el temporizador
                        tiempoEnPantalla.restart();
                    }
                }
            }
        }

        // Actualizar la posición de la mira para que siga al ratón
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        mira.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

        // Verificar el tiempo transcurrido
        if (tiempoEnPantalla.getElapsedTime().asSeconds() > tiempoLimite) {
            // Si el sprite es un enemigo, restar 1 vida
            if (enemigo.getSprite().getTexture() == &enemigoTexture) {
                vidas--;
            }

            // Cambiar a una nueva posición y textura aleatoria
            enemigo.cambiarPosicionYTexturaAleatoria();

            // Reiniciar el temporizador
            tiempoEnPantalla.restart();
        }

        // Limpiar la ventana
        window.clear();

        // Dibujar el fondo
        window.draw(fondoSprite);


        // Dibujar los sprites en la ventana
        window.draw(enemigo.getSprite());
        mira.draw(window);

        // Mostrar puntaje, vidas y enemigos muertos en la ventana
        sf::Font Fuente;
        if (Fuente.loadFromFile("EncodeSans-VariableFont_wdth,wght.ttf")) {
            sf::Text textoPuntaje("Puntaje: " + std::to_string(puntos), Fuente, 30);
            textoPuntaje.setPosition(460, 710);
            window.draw(textoPuntaje);

            sf::Text textoVidas("Vidas: " + std::to_string(vidas), Fuente, 30);
            textoVidas.setPosition(40, 710);
            window.draw(textoVidas);

            sf::Text textoEnemigosMuertos("Corruptos muertos: " + std::to_string(enemigosMuertos), Fuente, 30);
            textoEnemigosMuertos.setPosition(730, 710);
            window.draw(textoEnemigosMuertos);

            // Mostrar mensaje de victoria al alcanzar 10 enemigos eliminados
            if (enemigosMuertos >= 10) {
                window.draw(ganasteSprite);
            }
            // Mostrar mensaje de derrota si se quedan sin vidas
            else if (vidas <= 0) {
                window.draw(perdisteSprite);
            }
        }

        // Mostrar la ventana
        window.display();

        // Cerrar la ventana si se quedan sin vidas o se alcanzan 10 enemigos eliminados
        if (vidas <= 0 || enemigosMuertos >= 10) {
            if (!juegoTerminado) {
                tiempoPantallaFinal.restart();
                juegoTerminado = true;
            }

            // Mostrar la pantalla correspondiente
            if (enemigosMuertos >= 10) {
                window.draw(ganasteSprite);
            }
            else if (vidas <= 0) {
                window.draw(perdisteSprite);
            }

            // Mostrar la ventana durante 10 segundos después de la pantalla final
            if (tiempoPantallaFinal.getElapsedTime().asSeconds() > 10.0f) {
                window.close();
            }
        }
    }

    return 0;
}