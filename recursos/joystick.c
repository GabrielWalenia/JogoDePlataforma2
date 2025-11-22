#include <stdio.h>
#include <stdlib.h>

#include "joystick.h"

// Cria o controle para o personagem
joystick* joystick_create(){
    joystick *controle = (joystick *) malloc(sizeof(joystick));
    if(!controle){
        printf("Não foi possível alocar memória!\n");
        return NULL;
    }
    controle->right = 0;
    controle->left = 0;
    controle->up = 0;
    controle->down = 0;
    controle->jump = 0;

    return controle;
}
void joystick_destroy(joystick *controle){
    free(controle);

}
void joystick_right(joystick *controle){

    controle->right = controle->right ^ 1;

}
void joystick_left(joystick *controle){
    controle->left = controle->left ^ 1;

}
void joystick_up(joystick *controle){
    controle->up = controle->up ^ 1;


}
void joystick_down(joystick *controle){
    controle->down = controle->down ^ 1;

}
void joystick_jump(joystick *controle){
    controle->jump = controle->jump ^1;
}