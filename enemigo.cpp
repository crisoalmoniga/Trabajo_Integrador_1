#include "Enemigo.h"

Enemigo::Enemigo(sf::Texture& texture, float scale, const sf::Vector2f& position, int tiempoSpawn, int tiempoDesaparicion)
    : tiempoSpawn(tiempoSpawn), tiempoDesaparicion(tiempoDesaparicion), destruido(false) {
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setPosition(position);

    reset(); // Inicializar los relojes
}

void Enemigo::update() {
    if (!destruido) {
        // Verificar si ha pasado el tiempo de spawn
        if (spawnClock.getElapsedTime().asMilliseconds() >= tiempoSpawn) {
            // Aquí puedes agregar lógica específica del enemigo antes de mostrarlo
        }

        // Verificar si ha pasado el tiempo de desaparición
        if (desaparicionClock.getElapsedTime().asMilliseconds() >= tiempoDesaparicion) {
            destroy();
        }
    }
}

void Enemigo::draw(sf::RenderWindow& window) {
    if (!destruido) {
        window.draw(sprite);
    }
}

bool Enemigo::isClicked(const sf::Vector2f& clickPosition) {
    return sprite.getGlobalBounds().contains(clickPosition) && !destruido;
}

void Enemigo::destroy() {
    destruido = true;
    reset(); // Reiniciar los relojes y otras propiedades después de la destrucción
}

void Enemigo::reset() {
    spawnClock.restart();
    desaparicionClock.restart();
    destruido = false;
}
