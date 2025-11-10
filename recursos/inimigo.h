#ifndef __INIMIGO__
#define __INIMIGO__

#define ENEMY_STEPS 20

typedef struct {

    int height, width;
    int x;
    int y;

} inimigo;

inimigo* inimigo_create(int height, int width, int x, int y,
    int max_x, int max_y);
void inimigo_move(inimigo *elemento,  int steps, char trajectory, int max_x, int max_y);
void inimigo_destroy(inimigo *elemento);

#endif