#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <ctime>
#include "Enemigo.h"

enum GameState {
    MainMenu,
    InGame,
    GameOver
};

int main() {
    srand(static_cast<unsigned int>(time(0)));

    sf::Texture miraTextura;
    sf::Texture fondoTexture;
    sf::Texture enemigoTexture;
    sf::Texture inocenteTexture;
    sf::Texture inicioTexture;

    miraTextura.loadFromFile("mira.png");
    fondoTexture.loadFromFile("fondo.png");
    enemigoTexture.loadFromFile("enemigo.png");
    inocenteTexture.loadFromFile("inocente.png");  // Cambia la textura del inocente según sea necesario
    inicioTexture.loadFromFile("inicio.png");

    sf::Sprite miraSprite(miraTextura);
    miraSprite.setScale(0.2f, 0.2f);
    miraSprite.setOrigin(miraSprite.getGlobalBounds().width / 2, miraSprite.getGlobalBounds().height / 2);

    sf::RenderWindow App(sf::VideoMode(1024, 768), "La mano en la lata");

    sf::Sprite fondoSprite(fondoTexture);
    sf::Sprite inicioSprite(inicioTexture);

    int tiempoSpawn = 5000;
    int tiempoDesaparicion = 10000;
    int tiempoEspera = 8000;  // Tiempo de espera entre desaparición y aparición de enemigos

    Enemigo enemigo(enemigoTexture, 1.1f, sf::Vector2f(450, 450), tiempoSpawn, tiempoDesaparicion);
    Enemigo inocente(inocenteTexture, 1.1f, sf::Vector2f(450, 450), tiempoSpawn, tiempoDesaparicion);

    sf::Clock esperaClock;  // Reloj para gestionar el tiempo de espera
    GameState gameState = GameState::MainMenu;

    while (App.isOpen()) {
        sf::Event event;
        while (App.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                App.close();
            }
            else if (event.type == sf::Event::MouseMoved) {
                miraSprite.setPosition(event.mouseMove.x, event.mouseMove.y);
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (gameState == GameState::MainMenu) {
                    gameState = GameState::InGame;
                }
                else {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(App);
                    sf::Vector2f worldPosition = App.mapPixelToCoords(mousePosition);

                    if (enemigo.isClicked(worldPosition)) {
                        enemigo.destroy();
                        esperaClock.restart();  // Reinicia el temporizador después de destruir un enemigo
                    }
                    else if (inocente.isClicked(worldPosition)) {
                        inocente.destroy();
                        esperaClock.restart();  // Reinicia el temporizador después de destruir el "inocente"
                    }
                }
            }
        }

        App.clear();

        if (gameState == GameState::MainMenu) {
            // Escalar la textura de inicio para ajustarla al tamaño de la ventana
            inicioSprite.setScale(static_cast<float>(App.getSize().x) / inicioSprite.getTexture()->getSize().x,
                static_cast<float>(App.getSize().y) / inicioSprite.getTexture()->getSize().y);
            App.draw(inicioSprite);
        }
        else if (gameState == GameState::InGame) {
            fondoSprite.setScale(static_cast<float>(App.getSize().x) / fondoSprite.getTexture()->getSize().x,
                static_cast<float>(App.getSize().y) / fondoSprite.getTexture()->getSize().y);
            App.draw(fondoSprite);

            // Decidir aleatoriamente qué enemigo mostrar en esta iteración
            bool mostrarEnemigo = rand() % 2 == 0;

            if (mostrarEnemigo) {
                enemigo.update();
                enemigo.draw(App);
            }
            else {
                inocente.update();
                inocente.draw(App);
            }

            App.draw(miraSprite);
        }

        App.display();
    }

    return 0;
}