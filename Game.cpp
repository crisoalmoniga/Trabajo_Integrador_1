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

	// Crear la ventana principal del juego
	sf::RenderWindow window(sf::VideoMode(1024, 768), "La mano en la lata");


	sf::Font Fuente;


	Fuente.loadFromFile("EncodeSans-VariableFont_wdth,wght.ttf");

	if (!enemigoTexture.loadFromFile("enemigo.png") || !inocenteTexture.loadFromFile("inocente.png") || !miraTexture.loadFromFile("mira.png")){
		std::cout << "Falta textura"; // Salir si hay un error al cargar alguna textura
	}

	// Configurar propiedades de un sprite
	sf::Sprite sprite;
	sprite.setScale(1.2f, 1.2f);

	// Instancia de la clase Mira
	Mira mira(miraTexture);

	sf::Clock tiempoEnPantalla;
	float tiempoLimite = 2.5f;

	srand(static_cast<unsigned int>(time(0)));

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
				if (event.type == sf::Event::MouseButtonPressed) {
					juegoIniciado = true;
				}

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

		sf::Text textoVidas("Vidas: " + std::to_string(vidas), Fuente, 30);
		textoVidas.setPosition(40, 710);


		sf::Text textoEnemigosMuertos("Corruptos muertos: " + std::to_string(enemigosMuertos), Fuente, 30);
		textoEnemigosMuertos.setPosition(730, 710);

		// Dibujar texto en la ventana
		sf::Text textoPuntaje("Puntaje: " + std::to_string(puntos), Fuente, 30);
		textoPuntaje.setPosition(460, 710);

		// Limpiar la ventana y dibujar elementos
		window.clear();
		if (juegoIniciado == false)
		{
			window.draw(pantalla.spriteInicio);
		}

		if (juegoIniciado) {
			window.draw(enemigo.getSprite());
			window.draw(pantalla.spriteFondo);
			mira.draw(window);


			// Configurar fuente para el texto

			window.draw(textoPuntaje);
			window.draw(textoVidas);
			window.draw(textoEnemigosMuertos);

			// Mostrar pantalla de victoria o derrota según condiciones
			if (enemigosMuertos >= 10) {
				window.draw(pantalla.spriteGanaste);
			}
			else if (vidas <= 0) {
				window.draw(pantalla.spritePerdiste);
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
				window.draw(pantalla.spriteGanaste);
			}
			else if (vidas <= 0) {
				window.draw(pantalla.spritePerdiste);
			}

			// Cerrar la ventana después de 10 segundos en la pantalla final
			if (tiempoPantallaFinal.getElapsedTime().asSeconds() > 10.0f) {
				window.close();
			}
		}
	}
}