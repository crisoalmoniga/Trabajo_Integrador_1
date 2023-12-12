#pragma once
#include <SFML/Graphics.hpp>

class Game
{
public:

	// Variables de juego
	int puntos = 0;
	int vidas = 999;
	int enemigosMuertos = 0;

	// Posiciones iniciales de enemigos inocentes
	sf::Vector2f posiciones[6] = {
		sf::Vector2f(135.0f, 350.0f), //arriba izquierda
		sf::Vector2f(135.0f, 525.0f), //abajo izquierda
		sf::Vector2f(480.0f, 515.0f), //puerta principal
		sf::Vector2f(480.0f, 80.0f), //balcon
		sf::Vector2f(830.0f, 525.0f), //abajo derecha
		sf::Vector2f(830.0f, 350.0f) //arriba derecha
	};

	// Cargar texturas necesarias
	sf::Texture enemigoTexture;
	sf::Texture inocenteTexture;
	sf::Texture miraTexture;


	bool juegoIniciado = false;
	Game();
	~Game();

	void Go();
private:
	sf::RenderWindow App;
};

