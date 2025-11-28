#ifndef __INIMIGO__
#define __INIMIGO__

#define ENEMY_STEPS 10

#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>

typedef struct {

    int height, width;
    int x;
    int y;
    bool jump;
    int vel_y;
    int dir;
    ALLEGRO_BITMAP *sprite;
} inimigo;


inimigo* inimigo_create(int x, int y, int width, int height, int max_x, int max_y);
void inimigo_move(inimigo *elemento,  int steps, char trajectory, int max_x, int max_y);
void inimigo_destroy(inimigo *elemento);

#endif