#include <stdio.h>
#include <stdlib.h>

#include "inimigo.h"

inimigo* inimigo_create(int height, int width, int x, int y, int max_x, int max_y){
    //Verifica se a posição de "nascimeto" do inimigo é valida
    if ((x - width/2 < 0) || (x + width/2 > max_x) || (y - height/2 < 0) || (y + height/2 > max_y)) return NULL;

    inimigo *new_inimigo = (inimigo*) malloc(sizeof(inimigo));
    if(!new_inimigo){
        printf("Não foi possível alocar memória");
        return NULL;
    }

    new_inimigo->width = width;
    new_inimigo->height = height;
    new_inimigo->x = x;
    new_inimigo->y = y;

    return new_inimigo;

    
}