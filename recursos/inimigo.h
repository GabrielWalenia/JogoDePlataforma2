#ifndef __INIMIGO__
#define __INIMIGO__

#define ENEMY_STEPS 20

typedef struct {

    unsigned int height, width;
    unsigned int x;
    unsigned int y;

} inimigo;

inimigo* inimigo_create(unsigned int height, unsigned int width, unsigned int x, unsigned int y,
    unsigned int max_x, unsigned int max_y);
void inimigo_move(inimigo *elemento,  unsigned int steps, unsigned char trajectory, unsigned int max_x, unsigned int max_y);
void inimigo_destroy(inimigo *elemento);

#endif