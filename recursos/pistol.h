#ifndef __PISTOL__
#define __PISTOL__

#define PISTOL_COOLDOW 100

#include <stdlib.h>
#include "bullet.h"

typedef struct {

    char timer;
    bullet *shots;

} pistol;


pistol* pistol_create();

bullet *pistol_shot(int x, int y, int dir, pistol *gun);
void pistol_destroy(pistol *elemento);

#endif