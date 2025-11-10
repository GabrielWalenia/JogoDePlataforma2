#include <stdio.h>
#include "personagem.h"


personagem* personagem_create(unsigned int height, unsigned int width, unsigned int x, unsigned int y, unsigned int max_x, unsigned int max_y){

    //Verifica se o local de "nascimento" do personagem é valido
    if ((x - width/2 < 0) || (x + width/2 > max_x) || (y - height/2 < 0) || (y + height/2 > max_y)) return NULL;

    personagem *new_personagem = (personagem*) malloc(sizeof(personagem));
    if(!new_personagem){
        printf("Não foi possível alocar memória");
        return NULL;
    }

    new_personagem->width = width;
    new_personagem->height = height;
    new_personagem->x = x;
    new_personagem->y = y;

    return new_personagem;
}
void personagem_move(personagem *elemento,  unsigned int steps, unsigned char trajectory, unsigned int max_x, unsigned int max_y){
    //Movimentação a esquerda
    if(!trajectory){
        if ((elemento->x - steps*MAN_STEPS) - elemento->width/2 >= 0)
            elemento->x = elemento->x - steps*MAN_STEPS;
    }
    //Direita
    else if(trajectory == 1){
        if((elemento->x + steps*MAN_STEPS) + elemento->width/2 <= max_x)
            elemento->x = elemento->x + steps*MAN_STEPS;
    }
    //Cima
    else if(trajectory == 2){
        if((elemento->y - steps*MAN_STEPS) - elemento->height/2 >= 0){
            elemento->y = elemento->y - steps*MAN_STEPS;
        }
    }
    //Baixo
    else{
        if((elemento->y+ steps*MAN_STEPS) + elemento->height <= max_y){
            elemento->y = elemento->y + steps*MAN_STEPS;
        }
    }
}
void personagem_destroy(personagem *elemento){
    free(elemento);
}