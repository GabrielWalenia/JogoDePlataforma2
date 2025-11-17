/*

Pos x
gaw24@h41:~$ echo $((419/7))
59

pos y
gaw24@h41:~$ echo $((718/12))
59

sprite 2
x: 50
y: 77
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
#define PERSONAGEM_SPRITE "./imagens/ninja.png"

#define X_SCREEN 1280
#define Y_SCREEN 720
#define MAX_PULO 50
#define MAX_ENEMYS 6
#define GRAVIDADE 10


void animacao(const char *file, personagem *player_1, int tipo){

    // float frame = 0.f;
    // int pos_x = 0, pos_y = 0;
    // int current_frame_y = 0;
    
    // ALLEGRO_BITMAP *skin = al_load_bitmap(file);

    // if(tipo == 0){
    //     frame += 0.04f;
    //     if(frame > 4){
    //         frame -= 4;
    //     }
    // al_draw_bitmap_region(skin, 0, 118 * (int) frame, 59, 59, player_1->x - player_1->width, player_1->y - player_1->height, 0);
    // }


}

int verificar_colisao(personagem *elemento_1, inimigo *elemento_2){
    
    if((elemento_1->y + elemento_1->height/2 >= elemento_2->y - elemento_2->height/2) && (elemento_2->y - elemento_2->height/2 >=elemento_1->y-elemento_1->height/2) ||
    ((elemento_2->y+elemento_2->height/2 >= elemento_1->y-elemento_1->height/2) && (elemento_1->y-elemento_1->height/2 >= elemento_2->y-elemento_2->height/2)) &&
    (((elemento_1->x+elemento_1->width/2 >= elemento_2->x-elemento_2->width/2) && (elemento_2->x-elemento_2->width/2 >= elemento_1->x-elemento_1->width/2)) ||
    ((elemento_2->x+elemento_2->width/2 >= elemento_1->x-elemento_1->width/2) && (elemento_1->x-elemento_1->width/2 >= elemento_2->x-elemento_2->width/2)))) return 1;

    else return 0;

}

void update_position(personagem *player_1){
    if (player_1->controle->left){
        personagem_move(player_1, 1, 0, X_SCREEN, Y_SCREEN - 20);
        animacao(PERSONAGEM_SPRITE, player_1, 0);
    }
    if (player_1->controle->right){
        personagem_move(player_1, 1, 1, X_SCREEN, Y_SCREEN  - 20);
    }
    if (player_1->controle->up){
        personagem_move(player_1, 1, 2, X_SCREEN, Y_SCREEN  - 20);
    }
        if (player_1->controle->down){
        personagem_move(player_1, 1, 3, X_SCREEN, Y_SCREEN  - 20);
    }
}

void cair(personagem *player){
    player->y += GRAVIDADE;
}
void pular(personagem *player){
    player->y -= GRAVIDADE;
}

int main(){


    // -----------------------------------
    // Iniciação componentes
    al_init();
    al_install_keyboard();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();

    // -----------------------------------
    // Variáveis

    bool menu = true, caindo = true;
    float frame = 0.f;
    int pos_x = 0, pos_y = 0;
    int current_frame_y = 0;

    inimigo *vetor_inimigos[MAX_ENEMYS];

    ALLEGRO_TIMER *timer = al_create_timer(1.0/30.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_FONT *font = al_load_ttf_font("./imagens/Freedom-10eM.ttf", 36, 0);
    ALLEGRO_DISPLAY *disp = al_create_display(1280, 720);


    // -----------------------------------
    // Iniciando a fila

    // Imagens:
    // ALLEGRO_BITMAP *background = al_load_bitmap(BACKGROUND_FILE);;
    // if(!background){
    //     printf("Falha em abrir o background!");
    //     return 1;
    // }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_set_window_title(disp, "Game");
    // -----------------------------------
    // Elementos

    personagem* player_1 = personagem_create(3, 77, 50, 25.0, Y_SCREEN/2, X_SCREEN, Y_SCREEN);
    if (!player_1) return 1;

    for(int i = 0; i<MAX_ENEMYS; i++){
        vetor_inimigos[i] = inimigo_create(20, 20, 1 + rand()%1280, 690, X_SCREEN, Y_SCREEN);

    }
    // inimigo *enemy = inimigo_create(20, 20, X_SCREEN - 10, Y_SCREEN/2, X_SCREEN, Y_SCREEN);

    ALLEGRO_BITMAP *skin = al_load_bitmap(PERSONAGEM_SPRITE);
    ALLEGRO_BITMAP *background = al_load_bitmap(BACKGROUND_FILE);
    
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    
    //-----------------------------------
    // Jogo
    while(1){
        al_wait_for_event(queue, &event);

        if(event.type == 30){
            // if(player_1->y + player_1->height/2 + GRAVIDADE< 690 - MAX_PULO );
            //     caindo = true;
            if(menu){
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(255, 0, 0), X_SCREEN/2, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Joguinho do ninja");
                al_draw_text(font, al_map_rgb(255, 0, 0), X_SCREEN/2, Y_SCREEN/2 + 40, ALLEGRO_ALIGN_CENTER, "PRESSIONE ENTER");
                al_flip_display();
            }else{
                update_position(player_1);
                // al_draw_bitmap(background,0,0,0);
                al_clear_to_color(al_map_rgb(39, 104, 88));

          
                //al_draw_bitmap(background, 0, 0, 0);

                al_draw_filled_rectangle(player_1->x-player_1->width/2, player_1->y-player_1->height/2, player_1->x+player_1->width/2, player_1->y+player_1->height/2, al_map_rgb(255, 0, 0));
                al_draw_filled_rectangle(0, Y_SCREEN-20, X_SCREEN, Y_SCREEN, al_map_rgb(0, 255, 0));
                for(int i = 0; i<MAX_ENEMYS; i++){
                    inimigo_move(vetor_inimigos[i], 1, 0, X_SCREEN, Y_SCREEN);
                    
                    al_draw_filled_rectangle(vetor_inimigos[i]->x-vetor_inimigos[i]->width/2, 
                        vetor_inimigos[i]->y-vetor_inimigos[i]->height/2, vetor_inimigos[i]->x+vetor_inimigos[i]->width/2, vetor_inimigos[i]->y+vetor_inimigos[i]->height/2, al_map_rgb(0, 0, 255));
                }

            // Desenhar o sprite na tela
            
            if(player_1->controle->right){
                frame +=0.8f;
                if(frame > 8){
                    frame -= 8;
                }
                al_draw_bitmap_region(skin, 50 * (int) frame, 154, 50, 77, player_1->x - player_1->width / 2, player_1->y - player_1->height / 2 , 0);
            } else if(player_1->controle->left) {
                frame +=0.8f;
                if(frame > 8){
                    frame -= 8;
                }
                al_draw_bitmap_region(skin, 50 * (int) frame, 77, 50, 77, player_1->x - player_1->width / 2, player_1->y - player_1->height/2 , 0);
            } else {

                al_draw_bitmap_region(skin, 0,  0, 50, 77, player_1->x - player_1->width/ 2, player_1->y - player_1->height /2, 0);
            }
                
                if(caindo){
                    cair(player_1);
                    if((player_1->y + GRAVIDADE) + player_1->height/2 >= 690){
                        caindo= false;
                    }
                }

                al_flip_display();
            }
    
        }else if ((event.type == 10) || (event.type == 12)){

            if (event.keyboard.keycode == 82) joystick_left(player_1->controle);
            else if (event.keyboard.keycode == 83) joystick_right(player_1->controle);
            else if (event.keyboard.keycode == 84) joystick_up(player_1->controle);
            else if (event.keyboard.keycode == 85) joystick_down(player_1->controle);
            else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE) pular(player_1);
            else if(event.keyboard.keycode == ALLEGRO_KEY_ENTER) menu = false;
        }
        else if(player_1->hp <= 0){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 0, 0), X_SCREEN/2, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Game Over");
            al_flip_display();

        }

        else if(event.type == 42)
            break;
    }



    al_destroy_bitmap(skin);
    al_destroy_bitmap(background);

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}