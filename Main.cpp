#include "Game.h"

//Me tom� la licencia de hacer una versi�n del shooter, faltan muchas cosas como poder reiniciar el juego y agregar animaciones, las cuales no llego a armar.

// Tengo un gran bug, el contador de los sprites comienza a funcionar con la pantalla de inicio, 
// por lo que deber�a cambiar la l�gica de ese contador pero no llego con el tiempo a modificarlo
//La soluci�n que pens� moment�neamente es incrementar la cantidad de vidas para que mientras se leen las instrucciones no se pierdan

int main() {
   
    Game juego;
    juego.Go();

    return 0;
}