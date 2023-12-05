#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include "Enemigo.h"

int main() {
    srand(time(0));

    sf::Texture miraTextura;
    sf::Texture fondoTexture;
    sf::Texture enemigoTexture;

    miraTextura.loadFromFile("mira.png");
    fondoTexture.loadFromFile("fondo.png");
    enemigoTexture.loadFromFile("enemigo.png");

    // Configuración del sprite de la mira
    sf::Sprite miraSprite(miraTextura);
    miraSprite.setScale(0.2f, 0.2f);
    miraSprite.setOrigin(miraSprite.getGlobalBounds().width / 2, miraSprite.getGlobalBounds().height / 2);

    sf::RenderWindow App(sf::VideoMode(1024, 768), "La mano en la lata");

    sf::Sprite fondoSprite(fondoTexture);

    // Define la posición específica del enemigo (ajusta según sea necesario)
    sf::Vector2f enemigoPosition(500, 550);

    // Tiempo de spawn y tiempo de desaparición en milisegundos (ajusta según sea necesario)
    int tiempoSpawn = 600;
    int tiempoDesaparicion = 1000;

    Enemigo enemigo(enemigoTexture, 0.9f, enemigoPosition, tiempoSpawn, tiempoDesaparicion);

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
                // Verifica si el clic del mouse ocurre sobre el enemigo
                sf::Vector2i mousePosition = sf::Mouse::getPosition(App);
                sf::Vector2f worldPosition = App.mapPixelToCoords(mousePosition);

                if (enemigo.isClicked(worldPosition)) {
                    // Si se hizo clic en el enemigo, desaparece
                    enemigo.destroy();
                }
            }
        }

        enemigo.update();  // Actualiza la lógica del enemigo

        App.clear();

        // Escala el fondo para que ocupe toda la ventana
        fondoSprite.setScale(
            static_cast<float>(App.getSize().x) / fondoSprite.getTexture()->getSize().x,
            static_cast<float>(App.getSize().y) / fondoSprite.getTexture()->getSize().y
        );

        App.draw(fondoSprite);

        // Dibuja el enemigo
        enemigo.draw(App);

        App.draw(miraSprite);
        App.display();
    }

    return 0;
}