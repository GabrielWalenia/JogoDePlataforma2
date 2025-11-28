#ifndef __PLATAFORMA__
#define __PLATAFORMA__

#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>

#define MOVIMENTO 5

typedef struct{
    int x, y, h, w, dir;
    ALLEGRO_BITMAP *skin;
} plataforma;

plataforma *plataforma_create(int x, int y, int w, int h);
void plataforma_move(plataforma *elemento, int steps,  char trajectory);
void plataforma_destroy(plataforma *elemento);

#endif