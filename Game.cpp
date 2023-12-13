#include "Game.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "EnemigoInocente.h"
#include "Mira.h"
#include "Pantalla.h"
#include <iostream>

Game::Game() {
}

Game::~Game() {
}

void Game::Go() {

	Pantalla pantalla;

	// Creacion de ventana principal del juego
	sf::RenderWindow window(sf::VideoMode(1024, 768), "La mano en la lata");

	sf::Font Fuente;

	Fuente.loadFromFile("EncodeSans-VariableFont_wdth,wght.ttf");

	//Carga de texturas
	if (!enemigoTexture.loadFromFile("enemigo.png") || !inocenteTexture.loadFromFile("inocente.png") || !miraTexture.loadFromFile("mira.png")){
		std::cout << "Falta textura"; // Salir si hay un error al cargar alguna textura
	}

	sf::Sprite sprite;
	sprite.setScale(1.2f, 1.2f);

	Mira mira(miraTexture);

	//Tiempo de spawneo de los sprites - Setear a gusto
	sf::Clock tiempoEnPantalla;
	float tiempoLimite = 2.5f;

	srand(static_cast<unsigned int>(time(0)));


	EnemigoInocente enemigo(enemigoTexture, inocenteTexture, posiciones);

	bool juegoTerminado = false;
	sf::Clock tiempoPantallaFinal;

	// Bucle principal del juego
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			// Eventos de la ventana principal
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				// Click izquierdo del mouse
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
				if (event.type == sf::Event::MouseButtonPressed) {
					juegoIniciado = true;
				}

				// Verifica si el click es en un enemigo o inocente
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

		// Posición de la mira según la posición del mouse
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		mira.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

		// Tiempo de exposición del enemigo en pantalla
		if (tiempoEnPantalla.getElapsedTime().asSeconds() > tiempoLimite) {
			if (enemigo.getSprite().getTexture() == &enemigoTexture) {
				vidas--;
			}

			enemigo.cambiarPosicionYTexturaAleatoria();
			tiempoEnPantalla.restart();
		}

		// Objetos de texto para mostrar en ventana
		sf::Text textoVidas("Vidas: " + std::to_string(vidas), Fuente, 30);
		textoVidas.setPosition(40, 710);

		sf::Text textoEnemigosMuertos("Corruptos muertos: " + std::to_string(enemigosMuertos), Fuente, 30);
		textoEnemigosMuertos.setPosition(730, 710);

		sf::Text textoPuntaje("Puntaje: " + std::to_string(puntos), Fuente, 30);
		textoPuntaje.setPosition(460, 710);

		window.clear();
		if (juegoIniciado == false)
		{
			window.draw(pantalla.spriteInicio);
		}

		if (juegoIniciado) {
			window.draw(enemigo.getSprite());
			window.draw(pantalla.spriteFondo);
			mira.draw(window);

			window.draw(textoPuntaje);
			window.draw(textoVidas);
			window.draw(textoEnemigosMuertos);

			// Muestra pantalla de ganaste o perdiste
			if (enemigosMuertos >= 10) {
				window.draw(pantalla.spriteGanaste);
			}
			else if (vidas <= 0) {
				window.draw(pantalla.spritePerdiste);
			}
		}

		window.display();

		// Verificacion de condiciones de fin del juego y mostrar pantalla final
		if (vidas <= 0 || enemigosMuertos >= 10) {
			if (!juegoTerminado) {
				tiempoPantallaFinal.restart();
				juegoTerminado = true;
			}

			if (enemigosMuertos >= 10) {
				window.draw(pantalla.spriteGanaste);
			}
			else if (vidas <= 0) {
				window.draw(pantalla.spritePerdiste);
			}

			// Cierra final la ventana después de 10 segundos en la pantalla final
			if (tiempoPantallaFinal.getElapsedTime().asSeconds() > 10.0f) {
				window.close();
			}
		}
	}
}