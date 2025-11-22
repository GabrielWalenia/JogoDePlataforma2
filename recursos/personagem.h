#ifndef __PERSONAGEM__
#define __PERSONAGEM__

#include <stdbool.h>
#include "joystick.h"


#define MAN_STEPS 10
#define GRAVITY 10

typedef struct {
    // Antigo
    
    int hp; 
    int height, width;
    int x;
    int y;
    joystick *controle;

    // Novo

    int vel_x, vel_y;
    bool caindo;

} personagem;

personagem* personagem_create(int hp, int height, int width, float x, float y,
    int max_x, int max_y);
void personagem_move(personagem *elemento,  int steps, char trajectory, int max_x, int max_y);
void personagem_destroy(personagem *elemento);

#endif