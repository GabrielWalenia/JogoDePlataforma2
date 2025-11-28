#include <stdio.h>
#include <stdlib.h>

#include "inimigo.h"

inimigo* inimigo_create(int x, int y, int width, int height, int max_x, int max_y){
    //Verifica se a posição de "nascimeto" do inimigo é valida
    if ((x - width/2 < 0) || (x + width/2 > max_x) || (y - height/2 < 0) || (y + height/2 > max_y)) return NULL;

    inimigo *new_inimigo = (inimigo*) malloc(sizeof(inimigo));
    if(!new_inimigo){
        printf("Não foi possível alocar memória\n");
        return NULL;
    }

    new_inimigo->width = width;
    new_inimigo->height = height;
    new_inimigo->x = x;
    new_inimigo->y = y;
    new_inimigo->sprite = al_load_bitmap("./imagens/samurai.png");
    new_inimigo->jump = false;
    new_inimigo->vel_y = 0;
    new_inimigo->dir = 0;
    
    return new_inimigo;

}

void inimigo_move(inimigo *elemento,  int steps, char trajectory, int max_x, int max_y){

    if(!trajectory){
        if ((elemento->x - steps*ENEMY_STEPS) - elemento->width/2 >= 0){
            
            elemento->x = elemento->x - steps*ENEMY_STEPS;
        }
    } else if(trajectory == 1 ){
        if((elemento->x + steps*ENEMY_STEPS) + elemento->width/2 <= max_x){
            elemento->x = elemento->x + steps*ENEMY_STEPS;
        }
    }
}

void inimigo_destroy(inimigo *elemento){
    free(elemento);
}

