#include "juego.h"

Juego::Juego() {
    ventana.create(sf::VideoMode(1024, 768), "La mano en la lata");
    ventana.setFramerateLimit(60);

    puntos = 0;
    vidas = 3;
    enemigosMuertos = 0;
    tiempoLimite = 2.5f;
    juegoTerminado = false;

    // Inicializar con una posición y textura aleatoria
    enemigo.inicializar(enemigoTexture, inocenteTexture);
    enemigo.cambiarPosicionYTexturaAleatoria();
}

void Juego::iniciar() {
    inicializarVentanaInicio();
    esperarInicioJuego();
    ventana.close();
}

void Juego::inicializarVentanaInicio() {
    sf::RenderWindow inicioVentana(sf::VideoMode(1024, 768), "Inicio");
    inicioVentana.setFramerateLimit(60);

    // Cargar la textura de la pantalla de inicio
    sf::Texture inicioTexture;
    if (!inicioTexture.loadFromFile("inicio.png")) {
        exit(-1);
    }

    // Configurar el sprite de la pantalla de inicio
    sf::Sprite inicioSprite(inicioTexture);
    inicioSprite.setScale(inicioVentana.getSize().x / inicioSprite.getLocalBounds().width, inicioVentana.getSize().y / inicioSprite.getLocalBounds().height);

    // Mostrar la ventana de inicio
    inicioVentana.draw(inicioSprite);
    inicioVentana.display();

    // Esperar hasta que el jugador presione un botón
    bool juegoIniciado = false;
    while (inicioVentana.isOpen() && !juegoIniciado) {
        sf::Event event;
        while (inicioVentana.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                inicioVentana.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                // Iniciar el juego cuando se hace clic
                juegoIniciado = true;
            }
        }
    }

    // Cerrar la ventana de inicio
    inicioVentana.close();
}

void Juego::esperarInicioJuego() {
    cargarTexturas();
    configurarSprites();
    inicializarJuego();

    while (ventana.isOpen()) {
        manejarEventos();
        actualizarSprites();
        dibujar();
    }
}

void Juego::cargarTexturas() {
    // Cargar las texturas de los sprites
    if (!enemigoTexture.loadFromFile("enemigo.png") || !inocenteTexture.loadFromFile("inocente.png") || !miraTexture.loadFromFile("mira.png") || !fondoTexture.loadFromFile("fondo.png") || !perdisteTexture.loadFromFile("perdiste.png") || !ganasteTexture.loadFromFile("ganaste.png")) {
        exit(-1);
    }
}

void Juego::configurarSprites() {
    // Configurar el sprite principal
    sprite.setScale(1.2f, 1.2f);

    // Configurar el sprite de la mira del mouse
    miraSprite.setTexture(miraTexture);
    miraSprite.setScale(0.2f, 0.2f);
    miraSprite.setOrigin(miraSprite.getLocalBounds().width / 2, miraSprite.getLocalBounds().height / 2);  // Establecer el origen en el centro

    // Configurar el fondo
    fondoSprite.setTexture(fondoTexture);
    fondoSprite.setScale(ventana.getSize().x / fondoSprite.getLocalBounds().width, ventana.getSize().y / fondoSprite.getLocalBounds().height);

    // Configurar el sprite de la pantalla de derrota
    perdisteSprite.setTexture(perdisteTexture);
    perdisteSprite.setScale(ventana.getSize().x / perdisteSprite.getLocalBounds().width, ventana.getSize().y / perdisteSprite.getLocalBounds().height);

    // Configurar el sprite de la pantalla de victoria
    ganasteSprite.setTexture(ganasteTexture);
    ganasteSprite.setScale(ventana.getSize().x / ganasteSprite.getLocalBounds().width, ventana.getSize().y / ganasteSprite.getLocalBounds().height);
}

void Juego::inicializarJuego() {
    // Inicializar el temporizador
    tiempoEnPantalla.restart();

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
    enemigo.cambiarPosicionYTexturaAleatoria(posiciones);
}

void Juego::manejarEventos() {
    sf::Event event;
    while (ventana.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            ventana.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            // Obtener la posición del ratón en el mundo
            sf::Vector2i mousePosition = sf::Mouse::getPosition(ventana);
            sf::Vector2f worldPosition = ventana.mapPixelToCoords(mousePosition);

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
}

void Juego::actualizarSprites() {
    // Actualizar la posición de la mira para que siga al ratón
    sf::Vector2i mousePosition = sf::Mouse::getPosition(ventana);
    miraSprite.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}

void Juego::dibujar() {
    // Limpiar la ventana
    ventana.clear();

    // Dibujar el fondo
    ventana.draw(fondoSprite);

    // Dibujar los sprites en la ventana
    ventana.draw(enemigo.getSprite());
    ventana.draw(miraSprite);

    // Mostrar puntaje, vidas y enemigos muertos en la ventana
    if (fuente.loadFromFile("EncodeSans-VariableFont_wdth,wght.ttf")) {
        sf::Text textoPuntaje("Puntaje: " + std::to_string(puntos), fuente, 30);
        textoPuntaje.setPosition(460, 710);
        ventana.draw(textoPuntaje);

        sf::Text textoVidas("Vidas: " + std::to_string(vidas), fuente, 30);
        textoVidas.setPosition(40, 710);
        ventana.draw(textoVidas);

        sf::Text textoEnemigosMuertos("Corruptos muertos: " + std::to_string(enemigosMuertos), fuente, 30);
        textoEnemigosMuertos.setPosition(730, 710);
        ventana.draw(textoEnemigosMuertos);

        // Mostrar mensaje de victoria al alcanzar 10 enemigos eliminados
        if (enemigosMuertos >= 10) {
            ventana.draw(ganasteSprite);
        }
        // Mostrar mensaje de derrota si se quedan sin vidas
        else if (vidas <= 0) {
            ventana.draw(perdisteSprite);
        }
    }

    // Mostrar la ventana
    ventana.display();

    // Cerrar la ventana si se quedan sin vidas o se alcanzan 10 enemigos eliminados
    if (vidas <= 0 || enemigosMuertos >= 10) {
        if (!juegoTerminado) {
            tiempoPantallaFinal.restart();
            juegoTerminado = true;
        }

        // Mostrar la pantalla correspondiente
        if (enemigosMuertos >= 10) {
            ventana.draw(ganasteSprite);
        }
        else if (vidas <= 0) {
            ventana.draw(perdisteSprite);
        }

        // Mostrar la ventana durante 10 segundos después de la pantalla final
        if (tiempoPantallaFinal.getElapsedTime().asSeconds() > 10.0f) {
            ventana.close();
        }
    }
}
