
/*
sprite 2
x: 50
y: 77
*/


/*
Cobra
x: 96
y: 72

*/

#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>

#include "./recursos/personagem.h"	
#include "./recursos/inimigo.h"
#include "./recursos/joystick.h"
#include "./recursos/background.h"
#include "./recursos/obj.h"
#include "./recursos/serpente.h"

#define BACKGROUND_FILE "./imagens/bg2.jpg"
#define PERSONAGEM_SPRITE "./imagens/ninja.png"

#define X_SCREEN 800
#define Y_SCREEN 600
#define X_FASE 1000000
#define X_MAPA 10
#define Y_MAPA 50
#define MAX_PULO 50
#define MAX_ENEMYS 0
#define GRAVIDADE 1
#define VELOCIDADE 20
#define BLOCK_SIZE 60
#define CHAO 60
#define OUT -512

background bg;
obj p = {4, 11, 500, 50, BLOCK_SIZE, BLOCK_SIZE}, bloco[X_MAPA][Y_MAPA];


void loadMap(const char *filename, int map [100][100], int max_x, int max_y){
    char buffer;
    
    FILE *arquivo = fopen(filename, "r+b");
    if(!arquivo){
        printf("Não\n");
        return ;
    }

    for(int i = 0; i<max_x; i++){
        for(int j = 0; j< max_y; j++){
            fread(&buffer, 1, 1, arquivo);
            if(buffer == '\n'){
                j--;
                continue;
            }
            map[i][j] = (int) buffer;
        }
    }

    for(int i = 0; i<max_x; i++){
        for(int j = 0; j< max_y; j++){
            if(map[i][j] == 49){

                bloco[i][j].y = i * BLOCK_SIZE;
                bloco[i][j].x = j * BLOCK_SIZE;
                bloco[i][j].w = BLOCK_SIZE;
                bloco[i][j].h = BLOCK_SIZE;
                bloco[i][j].wy = 0;
                bloco[i][j].dano = false;
                bloco[i][j].sprite = al_load_bitmap("./imagens/Pedaco_de_grama.png");
            } else if(map[i][j] == 51){
                bloco[i][j].y = i * BLOCK_SIZE;
                bloco[i][j].x = j * BLOCK_SIZE;
                bloco[i][j].w = BLOCK_SIZE;
                bloco[i][j].h = BLOCK_SIZE;
                bloco[i][j].wy = 0;
                bloco[i][j].dano = true;
                bloco[i][j].sprite = al_load_bitmap("./imagens/espinhos.png");

            } else {
                bloco[i][j].y = OUT;
                bloco[i][j].x = OUT;
                bloco[i][j].sprite = al_load_bitmap("./imagens/Pedaco_de_grama.png");;

            }
        }   
    }
}

void drawMap(int map [100][100], int max_x, int max_y, ALLEGRO_BITMAP *sprite){

    for(int i = 0; i< max_x; i++){
        for(int j = 0; j < max_y; j++){
            //al_draw_filled_rectangle(bloco[i][j].x - bloco[i][j].w/2, bloco[i][j].y - bloco[i][j].h/2, bloco[i][j].x + bloco[i][j].w/2, bloco[i][j].y + bloco[i][j].h/2, al_map_rgb(0, 255, 0));
            al_draw_bitmap(bloco[i][j].sprite, bloco[i][j].x - bloco[i][j].w/2,bloco[i][j].y - bloco[i][j].h/2, 0);
        }
    }
}

void animacao(const char *file, personagem *player_1, int tipo){


}

void atualizarCamera(float *cameraPosition, float x, float y, int width, int height){
        cameraPosition[0] = -( X_SCREEN / 2) + (x + width/2) ;
        // cameraPosition[1] = -( Y_SCREEN / 2) + (y + height/2);

        if(cameraPosition[0] < 0){
            cameraPosition[0] = 0;
        }
        if(cameraPosition[1] < 0){
            cameraPosition[1] = 0;
        }
}

int verificar_colisao(int n1_x, int n1_y, int n1_w, int n1_h,
    int n2_x, int n2_y, int n2_w, int n2_h){
    
    if(n1_x + n1_w > n2_x && n1_x < n2_x + n2_w && n1_y + n1_h > n2_y && n1_y < n2_y + n2_h)
        return 1;
    return 0;
}



void update_position(personagem *player_1 , inimigo **vetor_inimigos, serpente *vetor_serpentes[2]){
    
    bool jump = false;  
    int gravidade = GRAVIDADE;
    int jumpSpeed = 15;


    // movimenta para esquerda
    if (player_1->controle->left){
        personagem_move(player_1, 1, 0, X_FASE, Y_SCREEN);
        
        // for(int i = 0; i < X_MAPA; i++){
        //     for(int j = 0; j< Y_MAPA; j++){
        //         if(player_1->x - player_1->width/2 <= bloco[i][j].x + bloco[i][j].w/2 && player_1->y + player_1->height/2 >= bloco[i][j].y - bloco[i][j].h/2){
        //             printf("Entrou no if\n");
        //             personagem_move(player_1, -1, 0, X_FASE, Y_SCREEN - CHAO);
        //         }
        //     }
            // }

    }

    if (player_1->controle->right){

        personagem_move(player_1, 1, 1, X_FASE, Y_SCREEN);
        // for(int i = 0; i < X_MAPA; i++){
        //     for(int j = 0; j< Y_MAPA; j++){
        //         if(player_1->x + player_1->width/2 >= bloco[i][j].x - bloco[i][j].w/2 && player_1->y + player_1->height/2 >= bloco[i][j].y - bloco[i][j].h/2){
 
        //             personagem_move(player_1, -1, 1, X_FASE, Y_SCREEN - CHAO);
        //         }
        //     }
        // }
    }
    if (player_1->controle->up){
        personagem_move(player_1, 1, 2, X_FASE, Y_SCREEN);
    }

    if (player_1->controle->down){
        personagem_move(player_1, 1, 3, X_SCREEN, Y_SCREEN);
    }

    for(int i = 0; i < X_MAPA; i++){
        for(int j = 0; j< Y_MAPA; j++){
            if(verificar_colisao(player_1->x + 10, player_1->y+20, player_1->width, player_1->height,
                bloco[i][j].x, bloco[i][j].y, bloco[i][j].w, bloco[i][j].h)){
                // player_1->y = bloco[i][j].y - player_1->height;
                jump = true;
            }

            // Verifica a colisão da serpente
            for(int w =0; w<2; w++){
                if(verificar_colisao(vetor_serpentes[w]->x + 10, vetor_serpentes[w]->y+20, vetor_serpentes[w]->width, vetor_serpentes[w]->height,
                    bloco[i][j].x, bloco[i][j].y, bloco[i][j].w, bloco[i][j].h)){

                    vetor_serpentes[w]->jump = true;
                }
            }
        }
    }

    if (player_1->controle->jump && jump){
        player_1->vel_y = -jumpSpeed;
        jump = false;
    }

    player_1->y += player_1->vel_y;

    if(!jump)
        player_1->vel_y += gravidade;
    else 
        player_1->vel_y = 0;

    //gravidade para as serpentes
    for(int w = 0; w<2; w++){
        vetor_serpentes[w]->y += vetor_serpentes[w]->vel_y;

        if(!vetor_serpentes[w]->jump)
            vetor_serpentes[w]->vel_y += gravidade;
        else 
            vetor_serpentes[w]->vel_y = 0;
        
        
    }

}


int main(){


    // -----------------------------------
    // Iniciação componentes
    al_init();
    al_install_keyboard();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_acodec_addon();
    
    // -----------------------------------
    // Variáveis

    bool menu = true;
    float frame = 0.f, frame2 = 0.f,scale = 1.0f;
    int pos_x = 0, pos_y = 0;
    int current_frame_y = 0;


    float cameraPosition[2] = {0, 0};

    int loadCounterX = 0, loadCounterY = 0, mapSizeX = X_MAPA, mapSizeY = Y_MAPA;
    int map[100][100];


    
    inimigo *vetor_inimigos[MAX_ENEMYS];
    serpente *vetor_serpentes[2];



    ALLEGRO_TIMER *timer = al_create_timer(1.0/30.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_FONT *font = al_load_ttf_font("./imagens/Freedom-10eM.ttf", 36, 0);
    ALLEGRO_DISPLAY *disp = al_create_display(X_SCREEN, Y_SCREEN);

    ALLEGRO_TRANSFORM camera;

    // -----------------------------------
    // Iniciando a fila

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_set_window_title(disp, "Game");


    // -----------------------------------
    // Elementos

    personagem* player_1 = personagem_create(3, 77, 50, 25.0, Y_SCREEN/2, X_SCREEN, Y_SCREEN);
    // personagem* player_1 = personagem_create(3, 77, 50, X_SCREEN/2, Y_SCREEN/2, X_SCREEN, Y_SCREEN);
    if (!player_1) return 1;

    for(int i = 0; i<MAX_ENEMYS; i++){
        vetor_inimigos[i] = inimigo_create(77, 50, 1 + rand()%1280, Y_SCREEN - 60 - 25, X_SCREEN, Y_SCREEN);

    }

    // Vetor de serpentes

    vetor_serpentes[0] = serpente_create(72, 96, 350, Y_SCREEN/2, X_SCREEN, Y_SCREEN, al_load_bitmap("./imagens/snake.png"));
    vetor_serpentes[1] = serpente_create(72, 96, 720, Y_SCREEN/2, X_SCREEN, Y_SCREEN, al_load_bitmap("./imagens/snake.png"));

    ALLEGRO_BITMAP *skin = al_load_bitmap(PERSONAGEM_SPRITE);
    ALLEGRO_BITMAP *background = al_load_bitmap(BACKGROUND_FILE);
    
    

    // inicia o background
    initBackground(&bg, 0, 0, 10, 0, 1065, 600, -1, 1, background);
    loadMap("./mapas/fase1.txt", map, mapSizeX, mapSizeY);

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

                if(verificar_vida(player_1)){
                    // Atualiza a posicao;
                    update_position(player_1, vetor_inimigos, vetor_serpentes);
                
                    // Desenha o background e faz ele ir para trás
                    drawBackground(&bg);
                    // al_draw_bitmap(background,0,0, 0);
                    al_clear_to_color(al_map_rgb(39, 104, 88));

                    drawMap(map, mapSizeX, mapSizeY, NULL);

                    atualizarCamera(cameraPosition, player_1->x, player_1->y, player_1->width, player_1->height);
                
                    al_identity_transform(&camera);
                    al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
                    al_scale_transform(&camera, scale, scale);
                    al_use_transform(&camera);
                
                //al_draw_bitmap(background, 0, 0, 0);

                    //desenha o personagem;
                    al_draw_filled_rectangle(player_1->x-player_1->width/2, player_1->y-player_1->height/2, player_1->x+player_1->width/2, player_1->y+player_1->height/2, al_map_rgb(255, 0, 0));
                    // al_draw_filled_rectangle(0, Y_SCREEN-20, X_SCREEN, Y_SCREEN, al_map_rgb(0, 255, 0));
                    

                    // Desenha os inimigos
                    for(int i = 0; i<MAX_ENEMYS; i++){

                        al_draw_filled_rectangle(vetor_inimigos[i]->x-vetor_inimigos[i]->width/2, 
                            vetor_inimigos[i]->y-vetor_inimigos[i]->height/2, vetor_inimigos[i]->x+vetor_inimigos[i]->width/2, vetor_inimigos[i]->y+vetor_inimigos[i]->height/2, al_map_rgb(0, 0, 255));
                    }

                // Desenhar o sprite na tela
            
                    if(player_1->controle->right && !player_1->controle->jump){
                        frame +=0.8f;
                        if(frame > 8){
                            frame -= 8;
                        }
                        al_draw_bitmap_region(skin, 50 * (int) frame, 154, 50, 77, player_1->x - player_1->width / 2, player_1->y - player_1->height / 2 , 0);
                    } else if(player_1->controle->left && !player_1->controle->jump) {
                        frame +=0.8f;
                        if(frame > 8){
                            frame -= 8;
                        }
                        al_draw_bitmap_region(skin, 50 * (int) frame, 77, 50, 77, player_1->x - player_1->width / 2, player_1->y - player_1->height/2 , 0);
            
                    }else if(player_1->controle->up) {
                        frame += 0.4f;
                        if(frame > 4){
                            frame -= 4;
                        }
                        al_draw_bitmap_region(skin, 200 + 50 * (int) frame, 0, 50, 77, player_1->x - player_1->width / 2, player_1->y - player_1->height/2 , 0);
                    } else if(player_1->controle->jump && player_1->controle->right){
                        
                        frame += 0.4f;
                        if(frame > 4){
                            frame -= 4;
                        }

                        al_draw_bitmap_region(skin, 200 + 50 * (int) frame,  308, 50, 77, player_1->x - player_1->width/ 2, player_1->y - player_1->height /2, 0);
                    }
                    else if(player_1->controle->jump && player_1->controle->left){
                        
                        frame += 0.4f;
                        if(frame > 4){
                            frame -= 4;
                        }

                        al_draw_bitmap_region(skin, 50 * (int) frame,  308, 50, 77, player_1->x - player_1->width/ 2, player_1->y - player_1->height /2, 0);
                    }
                    else {

                        al_draw_bitmap_region(skin, 0,  0, 50, 77, player_1->x - player_1->width/ 2, player_1->y - player_1->height /2, 0);
                    }

                    frame2 += 0.03f;
                    if(frame2 > 3){
                        frame2 -= 3;
                    }
                    // Desenha o sprite da serpente;
                    for(int w =0; w<2; w++){
                        al_draw_filled_rectangle(vetor_serpentes[w]->x-vetor_serpentes[w]->width/2, 
                           vetor_serpentes[w]->y-vetor_serpentes[w]->height/2, vetor_serpentes[w]->x+vetor_serpentes[w]->width/2, vetor_serpentes[w]->y+vetor_serpentes[w]->height/2, al_map_rgb(0, 0, 255));
                        al_draw_bitmap_region(vetor_serpentes[w]->skin, 96 * (int) frame2, 0, 96, 72, vetor_serpentes[w]->x - vetor_serpentes[w]->width/ 2, vetor_serpentes[w]->y - vetor_serpentes[w]->height /2, 0);
                    }
                    al_flip_display();
                } else{
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_text(font, al_map_rgb(0, 0, 255), X_SCREEN/2, Y_SCREEN/2, 0, "GAME OVER");
                    al_flip_display();
                    al_rest(2.0);
                    break;

                }
            }
    
        }else if ((event.type == 10) || (event.type == 12)){

            if (event.keyboard.keycode == 82) joystick_left(player_1->controle);
            else if (event.keyboard.keycode == 83) joystick_right(player_1->controle);
            // else if (event.keyboard.keycode == 84) joystick_up(player_1->controle);
            // else if (event.keyboard.keycode == 85) joystick_down(player_1->controle);
            //else if (event.keyboard.keycode == ALLEGRO_KEY_LCTRL) joystick_agachar(player_1->controle);
            else if(event.keyboard.keycode == ALLEGRO_KEY_ENTER) menu = false;
            else if(event.keyboard.keycode == ALLEGRO_KEY_SPACE) joystick_jump(player_1->controle);
            else if(event.keyboard.keycode == ALLEGRO_KEY_PAD_MINUS) scale-=0.2f;
            else if(event.keyboard.keycode == ALLEGRO_KEY_PAD_PLUS) scale += 0.2f;

        }
        else if(player_1->hp <= 0){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 0, 0), X_SCREEN/2, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Game Over");
            al_flip_display();

        }

        else if(event.type == 42)
            break;
    }

    
    for(int i = 0; i<X_MAPA; i++){
        for(int j = 0; j< Y_MAPA; j++){
            al_destroy_bitmap(bloco[i][j].sprite);
        }
    }

    for(int i = 0; i<2; i++){
        serpente_destroy(vetor_serpentes[i]);
    }

    al_destroy_bitmap(skin);
    al_destroy_bitmap(background);

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}