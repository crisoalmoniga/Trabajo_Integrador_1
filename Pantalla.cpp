#include "Pantalla.h"

Pantalla::Pantalla() {

    //Carga de las texturas y configuracion de los sprites para las pantallas
    texturaInicio.loadFromFile("inicio.png");
    spriteInicio.setTexture(texturaInicio);

    texturaFondo.loadFromFile("fondo.png");
    spriteFondo.setTexture(texturaFondo);

    texturaPerdiste.loadFromFile("perdiste.png");
    spritePerdiste.setTexture(texturaPerdiste);

    texturaGanaste.loadFromFile("ganaste.png");
    spriteGanaste.setTexture(texturaGanaste);
}