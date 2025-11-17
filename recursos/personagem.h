#ifndef __PERSONAGEM__
#define __PERSONAGEM__

#include "joystick.h"

#define MAN_STEPS 10
#define GRAVITY 10

typedef struct {

    int height, width;
    float x;
    float y;
    joystick *controle;

} personagem;

personagem* personagem_create(int height, int width, float x, float y,
    int max_x, int max_y);
void personagem_move(personagem *elemento,  int steps, char trajectory, int max_x, int max_y);
void personagem_destroy(personagem *elemento);

#endif