#include "bullet.h"


bullet* bullet_create(int x, int y,  int dir, bullet *next){
    bullet *new_bullet = malloc(sizeof(bullet));
    
    if(!new_bullet) return NULL;
    new_bullet->x = x;
    new_bullet->y = y;
    new_bullet->dir = dir;
    new_bullet->next = (bullet *) next;

    return new_bullet;
}
void bullet_move(bullet *elemento){
    for(bullet *index = (bullet *) elemento; index != NULL; elemento = (bullet *)elemento->next){
        if(!index->dir) index->x -= BULLET_MOVE;
        else index->x += BULLET_MOVE;
    }
}
void bullet_destroy(bullet *elemento){
    free(elemento);
}
