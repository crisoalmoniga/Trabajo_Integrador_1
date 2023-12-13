#include "Game.h"

//Me tomé la licencia de hacer una versión del shooter, faltan muchas cosas como poder reiniciar el juego y agregar animaciones, las cuales no llego a armar.

// Tengo un gran bug, el contador de los sprites comienza a funcionar con la pantalla de inicio, 
// por lo que debería cambiar la lógica de ese contador pero no llego con el tiempo a modificarlo
//La solución que pensé momentáneamente es incrementar la cantidad de vidas para que mientras se leen las instrucciones no se pierdan

int main() {
   
    Game juego;
    juego.Go();

    return 0;
}