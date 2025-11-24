#ifndef __BACKGROUND__
#define __BACKGROUND__

#include <allegro5/allegro5.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>

typedef struct{
    int x, y, vel_x, vel_y;
    int dir_x, dir_y;
    int whidth, height;

    ALLEGRO_BITMAP *bitmap;

} background;

void initBackground(background *bg, int x, int y, int vel_x, int vel_y,
    int whidth, int height, int dir_x, int dir_y, ALLEGRO_BITMAP *image);
void updateBackground(background *bg, int dir);
void drawBackground(background *bg);

#endif