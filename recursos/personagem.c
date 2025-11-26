#include <stdio.h>
#include <stdlib.h>
#include "personagem.h"


personagem* personagem_create(int hp, int height, int width, float x, float y, int max_x, int max_y){

    //Verifica se o local de "nascimento" do personagem é valido
    if ((x - width/2 < 0) || (x + width/2 > max_x) || (y - height/2 < 0) || (y + height/2 > max_y)) return NULL;

    personagem *new_personagem = (personagem*) malloc(sizeof(personagem));
    if(!new_personagem){
        printf("Não foi possível alocar memória");
        return NULL;
    }
    
    new_personagem->hp = hp;
    new_personagem->width = width;
    new_personagem->height = height;
    new_personagem->x = x;
    new_personagem->y = y;
    new_personagem->controle = joystick_create();
    
    new_personagem->caindo = true;
    new_personagem->vel_x = 0;
    new_personagem->vel_y = 0;
    if(!new_personagem->controle){
        free(new_personagem);
        return NULL;
    }

    return new_personagem;
}
void personagem_move(personagem *elemento, int steps,  char trajectory,  int max_x, int max_y){
    
    // printf("posicao x = %d\n", elemento->x);
    // printf("posicao y = %d\n", elemento->y);

    //Movimentação a esquerda
    if(!trajectory){
        if ((elemento->x - steps*MAN_STEPS) - elemento->width/2 >= 0){
            
            elemento->x = elemento->x - steps*MAN_STEPS;
        }
    }
    //Direita
    else if(trajectory == 1){
        if((elemento->x + steps*MAN_STEPS) + elemento->width/2 <= max_x){
            elemento->x = elemento->x + steps*MAN_STEPS;
        }
    }
    //Cima
    else if(trajectory == 2){
        if((elemento->y - steps*MAN_STEPS) - elemento->height/2 >= 0){
            elemento->y = elemento->y - steps*MAN_STEPS;
        }
    }
    //Baixo
    else if(trajectory == 3){
        if((elemento->y+ steps*MAN_STEPS) + elemento->height/2 <= max_y){
            elemento->y = elemento->y + steps*MAN_STEPS;
        }
        // pular
    } else if(trajectory == 4){
            elemento->vel_y = elemento->vel_y + steps*40;
            elemento->y -= elemento->vel_y;
    }
}
void personagem_destroy(personagem *elemento){
    joystick_destroy(elemento->controle);
    free(elemento);
}

bool verificar_vida(personagem *elemento){
    if(elemento->hp <= 0){
        return false;
    }
    if(elemento->y - elemento->height/2 > 650){
        return false;
    }
    return true;
}