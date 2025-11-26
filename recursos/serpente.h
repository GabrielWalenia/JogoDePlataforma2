#ifndef __SERPENTE__
#define __SERPENTE__

#include <stdbool.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>

typedef struct {

    int height, width;
    int x;
    int y;
    bool jump;
    int vel_y;
    ALLEGRO_BITMAP*skin;

} serpente;

serpente* serpente_create(int height, int width, int x, int y,
    int max_x, int max_y, ALLEGRO_BITMAP *skin);

    void serpente_destroy(serpente *snake);
#endif