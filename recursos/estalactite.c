#include <stdlib.h>
#include <stdio.h>

#include "estalactite.h"

estalactite *estalactite_create(int x, int y, int width, int heigth){
    estalactite * est = (estalactite *) malloc(sizeof(estalactite));
    if(!est) return NULL;

    est->x = x;
    est->y = y;
    est->width = width;
    est->height = heigth;
    est->vel_y = 0;
    est->caindo = false;
    est->skin = al_load_bitmap("./imagens/estalactite.png");
    if(!est->skin){
        printf("Não foi possivel carregar a skin\n");
    }

    return est;
}
void estalactite_destroy(estalactite *elemento){

    al_destroy_bitmap(elemento->skin);
    free(elemento);

}