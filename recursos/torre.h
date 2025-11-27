#ifndef __TORRE__
#define __TORRE__

#include "pistol.h"
typedef struct {

    int height, width;
    int x;
    int y;
    pistol *gun;
    int dir;

} torre;

torre *torre_create(int x, int y, int height, int width, int dir);
void torre_shot(torre *elemento);
void torre_destroy(torre *elemento);
#endif