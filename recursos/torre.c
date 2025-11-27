#include <stdlib.h>
#include <stdio.h>
#include "torre.h"


torre *torre_create(int x, int y, int width, int height, int dir){
    torre *new_torre = (torre *) malloc(sizeof(torre));
    if(!new_torre) return NULL;
    new_torre->gun = pistol_create(); 
    if(!new_torre->gun){
        free(new_torre);
        return NULL;
    }

    new_torre->x = x;
    new_torre->y = y;
    new_torre->width = width;
    new_torre->height = height;
    new_torre->dir = dir;
}

void torre_shot(torre *elemento){
    bullet *shot;
    // 0 atira para a esquerda e 1 para a direita
    if(!elemento->dir) 
        shot = pistol_shot(elemento->x - elemento->width/2, elemento->y, elemento->dir, elemento->gun);
    else if (elemento->dir == 1) 
        shot = pistol_shot(elemento->x + elemento->width/2, elemento->y, elemento->dir, elemento->gun);

    if(shot) elemento->gun->shots = shot;

}
void torre_destroy(torre *elemento){
    pistol_destroy(elemento->gun);
    free(elemento);
}