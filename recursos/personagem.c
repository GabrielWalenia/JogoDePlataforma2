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
    
    new_personagem->controle = joystick_create();
    if(!new_personagem->controle){
        free(new_personagem);
        return NULL;
    }

    new_personagem->hp = hp;
    new_personagem->width = width;
    new_personagem->height = height;
    new_personagem->x = x;
    new_personagem->y = y;
    new_personagem->caindo = true;
    new_personagem->vel_x = 0;
    new_personagem->vel_y = 0;
    new_personagem->skin = al_load_bitmap("./imagens/ninja.png");
    if(!new_personagem->skin){
        printf("Não foi possivel alocar o bitmap\n");
        exit(1);
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
    al_destroy_bitmap(elemento->skin);
    joystick_destroy(elemento->controle);
    free(elemento);
}

bool verificar_morte(personagem *elemento){
    if(elemento->hp <= 0){
        return true;
    }
    if(elemento->y - elemento->height/2 > 650){
        return true;
    }
    return false;
}

void animacao(personagem *player_1, serpente *vetor_serpentes[2], float *frame, float *frame2){
    
    

    if(player_1->controle->right && !player_1->controle->jump){
        *frame +=0.8f;
        if(*frame > 8){
            *frame -= 8;
        }
        al_draw_bitmap_region(player_1->skin, 50 * (int) (*frame), 154, 50, 77, player_1->x - player_1->width / 2, player_1->y - player_1->height / 2 , 0);
    } else if(player_1->controle->left && !player_1->controle->jump) {
        
        *frame +=0.8f;
        if(*frame > 8){
            *frame -= 8;
        }
        al_draw_bitmap_region(player_1->skin, 50 * (int) (*frame), 77, 50, 77, player_1->x - player_1->width / 2, player_1->y - player_1->height/2 , 0);
            
    }else if(player_1->controle->up) {
        *frame += 0.4f;
        if(*frame > 4){
            *frame -= 4;
        }
        al_draw_bitmap_region(player_1->skin, 200 + 50 * (int) (*frame), 0, 50, 77, player_1->x - player_1->width / 2, player_1->y - player_1->height/2 , 0);
    } else if(player_1->controle->jump && player_1->controle->right){
                        
        *frame += 0.4f;
        if(*frame > 4){
            *frame -= 4;
        }
        al_draw_bitmap_region(player_1->skin, 200 + 50 * (int) (*frame),  308, 50, 77, player_1->x - player_1->width/ 2, player_1->y - player_1->height /2, 0);
    
    } else if(player_1->controle->jump && player_1->controle->left){
        *frame += 0.4f;
        if(*frame > 4){
            *frame -= 4;
        }

        al_draw_bitmap_region(player_1->skin, 50 * (int) (*frame),  308, 50, 77, player_1->x - player_1->width/ 2, player_1->y - player_1->height /2, 0);
    
    } else {
        al_draw_bitmap_region(player_1->skin, 0,  0, 50, 77, player_1->x - player_1->width/ 2, player_1->y - player_1->height /2, 0);
    }
}