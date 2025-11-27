#ifndef __BULLET__
#define __BULLET__

#define BULLET_MOVE 5

#include <stdlib.h>

typedef struct bullet{

    int x;
    int y;
    int dir;
    struct bullet *next;

} bullet;


bullet* bullet_create(int x, int y,
    int dir, bullet *next);
void bullet_move(bullet *elementos);
void bullet_destroy(bullet *elemento);

#endif