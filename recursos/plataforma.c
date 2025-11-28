#include "plataforma.h"

plataforma *plataforma_create(int x, int y, int w, int h){

    plataforma *new_plataforma = (plataforma *) malloc(sizeof(plataforma));
    if(!new_plataforma) return NULL;

    new_plataforma->x = x;
    new_plataforma->y = y;
    new_plataforma->w = w;
    new_plataforma->h = h;
    new_plataforma->skin = NULL;
    new_plataforma->dir = 1;
    
    return new_plataforma;
}
void plataforma_move(plataforma *elemento, int steps,  char trajectory){
    if(!trajectory){
        elemento->x = elemento->x - steps*MOVIMENTO;
    } else if(trajectory == 1 ){
        elemento->x = elemento->x + steps*MOVIMENTO;
    }
}
void plataforma_destroy(plataforma *elemento){
    free(elemento);
}