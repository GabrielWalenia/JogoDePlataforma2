#ifndef __OBJ__
#define __OBJ__

#include <stdbool.h>

typedef struct{
    int wx, wy, x, y, w, h;
    bool dano;
    bool fim;
    bool escalavel;
    ALLEGRO_BITMAP *sprite;
} obj;

#endif