/*

Pos x
gaw24@h41:~$ echo $((419/7))
59

pos y
gaw24@h41:~$ echo $((718/12))
59


*/


#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>

#include "./recursos/personagem.h"	
#include "./recursos/inimigo.h"
#include "./recursos/joystick.h"

#define BACKGROUND_FILE "./imagens/environment_forestbackground.png"
#define PERSONAGEM_SPRITE "./imagens/player_sprite.png"

#define X_SCREEN 1280
#define Y_SCREEN 720

void show_menu(ALLEGRO_DISPLAY *disp, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_EVENT event){
    while(1){
        if(event.type == 30){
            al_clear_to_color(al_map_rgb(39, 104, 88));
            al_draw_text(al_create_builtin_font(), al_map_rgb(0, 0, 0), X_SCREEN / 2, Y_SCREEN / 2, ALLEGRO_ALIGN_CENTRE, "Hello!" );
            al_flip_display();
        }else if(event.type == ALLEGRO_KEY_ENTER){
            break;
        }
        else if(event.type == 42)
            exit(1);
    }
}

void update_position(personagem *player_1){
    if (player_1->controle->left){
        personagem_move(player_1, 1, 0, X_SCREEN, Y_SCREEN);
    }
    if (player_1->controle->right){
        personagem_move(player_1, 1, 1, X_SCREEN, Y_SCREEN);
    }
    if (player_1->controle->up){
        personagem_move(player_1, 1, 2, X_SCREEN, Y_SCREEN);
    }
        if (player_1->controle->down){
        personagem_move(player_1, 1, 3, X_SCREEN, Y_SCREEN);
    }
}

int main(){
    al_init();
    al_install_keyboard();
    // al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();

    ALLEGRO_TIMER *timer = al_create_timer(1.0/30.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_FONT *font = al_create_builtin_font();
    ALLEGRO_DISPLAY *disp = al_create_display(1280, 720);


    
    // Imagens:
    // ALLEGRO_BITMAP *background = al_load_bitmap(BACKGROUND_FILE);;
    // if(!background){
    //     printf("Falha em abrir o background!");
    //     return 1;
    // }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    personagem* player_1 = personagem_create(20, 20, 10, Y_SCREEN/2, X_SCREEN, Y_SCREEN);
    if (!player_1) return 1;

    ALLEGRO_BITMAP *personagem = al_load_bitmap(PERSONAGEM_SPRITE);
    ALLEGRO_BITMAP *background = al_load_bitmap(BACKGROUND_FILE);
    
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    show_menu(disp, queue, event);
    
    while(1){
        al_wait_for_event(queue, &event);

        if(event.type == 30){
            update_position(player_1);
            // al_draw_bitmap(background,0,0,0);
            //al_clear_to_color(al_map_rgb(39, 104, 88));
            
            al_draw_bitmap(background, 0, 0, 0);
            al_draw_filled_rectangle(player_1->x-player_1->width/2, player_1->y-player_1->height/2, player_1->x+player_1->width/2, player_1->y+player_1->height/2, al_map_rgb(255, 0, 0));
            al_draw_bitmap_region(personagem, 0, 59, 59, 59, player_1->x - player_1->width/2, player_1->y - player_1->height/2, 0);
            al_flip_display();
        }
        else if ((event.type == 10) || (event.type == 12)){
            if (event.keyboard.keycode == 82) joystick_left(player_1->controle);
            else if (event.keyboard.keycode == 83) joystick_right(player_1->controle);
            else if (event.keyboard.keycode == 84) joystick_up(player_1->controle);
            else if (event.keyboard.keycode == 85) joystick_down(player_1->controle);
        }

        else if(event.type == 42)
            break;
    }
    


    al_destroy_bitmap(personagem);
    al_destroy_bitmap(background);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}