#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

int main() {
    // Crear la ventana de inicio
    sf::RenderWindow startWindow(sf::VideoMode(1024, 768), "Inicio");

    // Cargar la textura de la pantalla de inicio
    sf::Texture inicioTexture;
    if (!inicioTexture.loadFromFile("inicio.png")) {
        return -1;
    }

    // Configurar el sprite de la pantalla de inicio
    sf::Sprite inicioSprite(inicioTexture);
    inicioSprite.setScale(startWindow.getSize().x / inicioSprite.getLocalBounds().width, startWindow.getSize().y / inicioSprite.getLocalBounds().height);

    // Mostrar la ventana de inicio
    startWindow.draw(inicioSprite);
    startWindow.display();

    // Esperar hasta que el jugador presione un botón
    bool juegoIniciado = false;
    while (startWindow.isOpen() && !juegoIniciado) {
        sf::Event event;
        while (startWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                startWindow.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                // Iniciar el juego cuando se hace clic
                juegoIniciado = true;
            }
        }
    }

    // Cerrar la ventana de inicio
    startWindow.close();

    // Crear la ventana del juego
    sf::RenderWindow window(sf::VideoMode(1024, 768), "La mano en la lata");

    // Cargar las texturas de los sprites
    sf::Texture enemigoTexture;
    sf::Texture inocenteTexture;
    sf::Texture miraTexture;
    sf::Texture fondoTexture;
    sf::Texture perdisteTexture;  // Nueva textura para la pantalla de derrota
    sf::Texture ganasteTexture;   // Nueva textura para la pantalla de victoria

    // Manejar error si la carga de la textura falla
    if (!enemigoTexture.loadFromFile("enemigo.png") || !inocenteTexture.loadFromFile("inocente.png") || !miraTexture.loadFromFile("mira.png") || !fondoTexture.loadFromFile("fondo.png") || !perdisteTexture.loadFromFile("perdiste.png") || !ganasteTexture.loadFromFile("ganaste.png")) {
        return -1;
    }

    // Configurar el sprite principal
    sf::Sprite sprite;
    sprite.setScale(1.2f, 1.2f);

    // Configurar el sprite de la mira del mouse
    sf::Sprite miraSprite(miraTexture);
    miraSprite.setScale(0.2f, 0.2f);
    miraSprite.setOrigin(miraSprite.getLocalBounds().width / 2, miraSprite.getLocalBounds().height / 2);  // Establecer el origen en el centro

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
    int vidas = 999;
    int enemigosMuertos = 0;

    // Configurar el temporizador
    sf::Clock tiempoEnPantalla;
    float tiempoLimite = 1.2f;

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
    sprite.setPosition(posiciones[rand() % 6]);
    sprite.setTexture((rand() % 2 == 0) ? enemigoTexture : inocenteTexture);

    // Bucle principal del juego
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
                if (sprite.getGlobalBounds().contains(worldPosition)) {
                    if (sprite.getTexture() == &enemigoTexture) {
                        // Sumar puntos por matar al enemigo
                        puntos += 10;

                        // Incrementar el contador de enemigos muertos
                        enemigosMuertos++;

                        // Cambiar a una nueva posición y textura aleatoria
                        sprite.setPosition(posiciones[rand() % 6]);
                        sprite.setTexture((rand() % 2 == 0) ? enemigoTexture : inocenteTexture);

                        // Reiniciar el temporizador
                        tiempoEnPantalla.restart();
                    }
                    else if (sprite.getTexture() == &inocenteTexture) {
                        // Restar 1 vida por matar al inocente
                        vidas--;

                        // Cambiar a una nueva posición y textura aleatoria
                        sprite.setPosition(posiciones[rand() % 6]);
                        sprite.setTexture((rand() % 2 == 0) ? enemigoTexture : inocenteTexture);

                        // Reiniciar el temporizador
                        tiempoEnPantalla.restart();
                    }
                }
            }
        }

        // Actualizar la posición de la mira para que siga al ratón
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        miraSprite.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

        // Verificar el tiempo transcurrido
        if (tiempoEnPantalla.getElapsedTime().asSeconds() > tiempoLimite) {
            // Si el sprite es un enemigo, restar 1 vida
            if (sprite.getTexture() == &enemigoTexture) {
                vidas--;
            }

            // Cambiar a una nueva posición y textura aleatoria
            sprite.setPosition(posiciones[rand() % 6]);
            sprite.setTexture((rand() % 2 == 0) ? enemigoTexture : inocenteTexture);

            // Reiniciar el temporizador
            tiempoEnPantalla.restart();
        }

        // Limpiar la ventana
        window.clear();

        // Dibujar el fondo
        window.draw(fondoSprite);

        // Dibujar los sprites en la ventana
        window.draw(sprite);
        window.draw(miraSprite);

        // Mostrar puntaje, vidas y enemigos muertos en la ventana
        sf::Font font;
        if (font.loadFromFile("EncodeSans-VariableFont_wdth,wght.ttf")) {
            sf::Text textoPuntaje("Puntaje: " + std::to_string(puntos), font, 30);
            textoPuntaje.setPosition(460, 710);
            window.draw(textoPuntaje);

            sf::Text textoVidas("Vidas: " + std::to_string(vidas), font, 30);
            textoVidas.setPosition(40, 710);
            window.draw(textoVidas);

            sf::Text textoEnemigosMuertos("Corruptos muertos: " + std::to_string(enemigosMuertos), font, 30);
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
            window.close();
        }
    }

    return 0;
}