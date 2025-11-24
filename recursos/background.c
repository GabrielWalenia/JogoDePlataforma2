#include <stdio.h>
#include "background.h"

void initBackground(background *bg, int x, int y, int vel_x, int vel_y,int whidth, int height, int dir_x, int dir_y, ALLEGRO_BITMAP *image){
    
    bg->x = x;
    bg->y = y;
    bg->vel_x = vel_x;
    bg->vel_y = vel_y;
    bg->whidth = whidth;
    bg->height = height;
    bg->dir_x = dir_x;
    bg->dir_y = dir_y;
    bg->bitmap = image;

}

void updateBackground(background *bg, int dir){
    if(bg->x <= 0){
        bg->x += bg->vel_x * dir;
        if(bg->x + bg->whidth <= 0){
            bg->x = 0;
        }
    }else bg->x = 0;

}
void drawBackground(background *bg){
    al_draw_bitmap(bg->bitmap, bg->x, bg->y, 0);

    if(bg->x + bg->whidth < 800){
        al_draw_bitmap(bg->bitmap, bg->x + bg->whidth, bg->y, 0);
    }
}