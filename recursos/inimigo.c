#include <stdio.h>
#include <stdlib.h>

#include "inimigo.h"

inimigo* inimigo_create(int height, int width, int x, int y, int max_x, int max_y){
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

    return new_inimigo;

}

void inimigo_move(inimigo *elemento,  int steps, char trajectory, int max_x, int max_y){

    if(!trajectory){
        if ((elemento->x - steps*ENEMY_STEPS) - elemento->width/2 >= 0){
            
            elemento->x = elemento->x - steps*ENEMY_STEPS;
        } else {
            elemento->x = 1280;
        }
    }
    //Direita
    else if(trajectory == 1){
        if((elemento->x + steps*ENEMY_STEPS) + elemento->width/2 <= max_x){
            elemento->x = elemento->x + steps*ENEMY_STEPS;
        }
    }
    //Cima
    else if(trajectory == 2){
        if((elemento->y - steps*ENEMY_STEPS) - elemento->height/2 >= 0){
            elemento->y = elemento->y - steps*ENEMY_STEPS;
        }
    }
    //Baixo
    else{
        if((elemento->y+ steps*ENEMY_STEPS) + elemento->height <= max_y){
            elemento->y = elemento->y + steps*ENEMY_STEPS;
        }
    }
}

void inimigo_destroy(inimigo *elemento){
    free(elemento);
}

