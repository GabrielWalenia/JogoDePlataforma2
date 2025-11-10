#include <stdio.h>
#include <stdlib.h>

#include "inimigo.h"

inimigo* inimigo_create(unsigned int height, unsigned int width, unsigned int x, unsigned int y, unsigned int max_x, unsigned int max_y){
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