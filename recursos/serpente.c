#include <stdlib.h>

#include <stdio.h>

#include "serpente.h"

serpente *serpente_create(int height, int width, int x, int y,
    int max_x, int max_y, ALLEGRO_BITMAP *skin){

    if ((x - width/2 < 0) || (x + width/2 > max_x) || (y - height/2 < 0) || (y + height/2 > max_y)) return NULL;

    serpente *new_serpente = (serpente*) malloc(sizeof(serpente));
    if(!new_serpente){
        printf("Não foi possível alocar memória\n");
        return NULL;
    }

    new_serpente->width = width;
    new_serpente->height = height;
    new_serpente->x = x;
    new_serpente->y = y;
    new_serpente->vel_y = 0;
    new_serpente->jump = false;
    new_serpente->skin = skin;
    return new_serpente;

}

void serpente_destroy(serpente *snake){
    al_destroy_bitmap(snake->skin);
    free(snake);
}