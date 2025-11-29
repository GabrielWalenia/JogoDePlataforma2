#ifndef __ESTALACTITE__
#define __ESTALACTITE__
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>

typedef struct {
    int x, y, width, height, vel_y;
    bool caindo;

    ALLEGRO_BITMAP *skin;
} estalactite;

estalactite *estalactite_create(int x, int y, int width, int heigth);
void estalactite_destroy(estalactite *elemento);

#endif