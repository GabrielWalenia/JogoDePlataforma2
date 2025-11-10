#ifndef __PERSONAGEM__
#define __PERSONAGEM__

#define MAN_STEPS 20

typedef struct {

    unsigned int height, width;
    unsigned int x;
    unsigned int y;

} personagem;

personagem* personagem_create(unsigned int height, unsigned int width, unsigned int x, unsigned int y,
    unsigned int max_x, unsigned int max_y);
void personagem_move(personagem *elemento,  unsigned int steps, unsigned char trajectory, unsigned int max_x, unsigned int max_y);
void personagem_destroy(personagem *elemento);

#endif