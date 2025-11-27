#ifndef __PERSONAGEM__
#define __PERSONAGEM__

#include <stdbool.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>

#include "joystick.h"
#include "inimigo.h"
#include "serpente.h"
#include "bullet.h"

#define MAN_STEPS 10
#define GRAVITY 10

typedef struct {
    // Antigo
    
    int hp; 
    int height, width;
    int x;
    int y;
    joystick *controle;

    ALLEGRO_BITMAP *skin;
    // Novo

    int vel_x, vel_y;
    bool caindo;

} personagem;

personagem* personagem_create(int hp, int height, int width, float x, float y,
    int max_x, int max_y);
void personagem_move(personagem *elemento,  int steps, char trajectory, int max_x, int max_y);
void personagem_destroy(personagem *elemento);
bool verificar_vida(personagem *elemento);
void animacao(personagem *player_1, serpente *vetor_serpentes[2], float *frame, float *frame2);

#endif