#include "Game.h"

//Me tom� la licencia de hacer una versi�n del shooter, faltan muchas cosas como poder reiniciar el juego y agregar animaciones, las cuales no llego a armar.

// Los assets fueron creados con photoshop, la fuente utilizada es de la familia "EncodeSans-VariableFont_wdth,wght", la cual es propia de la marca "Argentina" y se puede
// descargar libremente de la p�gina de Nacion.
// 
// Con respecto a la ayuda recibida, en la l�gica de Spawneo tuve que ayudarme con videos de youtube y chat gpt ya que es lo que no podia hacer que funcione bien.
// 
// Tengo un gran bug, el contador de los sprites comienza a funcionar con la pantalla de inicio, 
// por lo que deber�a cambiar la l�gica de ese contador pero no llego con el tiempo a modificarlo
//La soluci�n que pens� moment�neamente es incrementar la cantidad de vidas para que mientras se leen las instrucciones no se pierdan vidas

int main() {
   
    Game juego;
    juego.Go();

    return 0;
}