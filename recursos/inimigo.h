#ifndef __INIMIGO__
#define __INIMIGO__

#define ENEMY_STEPS 10

#include <stdbool.h>

typedef struct {

    int height, width;
    int x;
    int y;

} inimigo;

typedef struct {

    int height, width;
    int x;
    int y;

} espinho;

typedef struct {

    int height, width;
    int x;
    int y;

} flecha;


typedef struct {

    int height, width;
    int x;
    int y;

} tronco;


inimigo* inimigo_create(int height, int width, int x, int y,
    int max_x, int max_y);
void inimigo_move(inimigo *elemento,  int steps, char trajectory, int max_x, int max_y);
void inimigo_destroy(inimigo *elemento);

espinho* espinho_create(int height, int width, int x, int y,
    int max_x, int max_y);


flecha* flecha_create(int height, int width, int x, int y,
    int max_x, int max_y);
void flecha_move(inimigo *elemento,  int steps, char trajectory, int max_x, int max_y);
void flecha_destroy(inimigo *elemento);

tronco* tronco_create(int height, int width, int x, int y,
    int max_x, int max_y);
void tronco_move(inimigo *elemento,  int steps, char trajectory, int max_x, int max_y);
void tronco_destroy(inimigo *elemento);

#endif