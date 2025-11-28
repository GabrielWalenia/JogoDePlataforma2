
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

// Não da para passar por baixo dos objetos


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
#include "./recursos/bullet.h"
#include "./recursos/torre.h"
#include "./recursos/pistol.h"
#include "./recursos/plataforma.h"

#define BACKGROUND_FILE "./imagens/bg2.jpg"
#define PERSONAGEM_SPRITE "./imagens/ninja.png"

#define X_SCREEN 800
#define Y_SCREEN 600
#define X_FASE 1000000
#define X_MAPA 10
#define Y_MAPA 100
#define MAX_PULO 50
#define MAX_ENEMYS 1
#define GRAVIDADE 1
#define VELOCIDADE 20
#define BLOCK_SIZE 65
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
                bloco[i][j].fim = false;
                bloco[i][j].sprite = al_load_bitmap("./imagens/Pedaco_de_grama.png");
            } else if(map[i][j] == 51){
                bloco[i][j].y = i * BLOCK_SIZE;
                bloco[i][j].x = j * BLOCK_SIZE;
                bloco[i][j].w = BLOCK_SIZE;
                bloco[i][j].h = BLOCK_SIZE;
                bloco[i][j].wy = 0;
                bloco[i][j].dano = true;
                bloco[i][j].fim = false;
                bloco[i][j].sprite = al_load_bitmap("./imagens/espinhos.png");
            
            }else if(map[i][j] == 52){
                bloco[i][j].y = i * BLOCK_SIZE;
                bloco[i][j].x = j * BLOCK_SIZE;
                bloco[i][j].w = BLOCK_SIZE;
                bloco[i][j].h = BLOCK_SIZE;
                bloco[i][j].wy = 0;
                bloco[i][j].dano = true;
                bloco[i][j].fim = false;
                bloco[i][j].sprite = al_load_bitmap("./imagens/water2.png");
            }else if(map[i][j] == 53){
                bloco[i][j].y = i * BLOCK_SIZE;
                bloco[i][j].x = j * BLOCK_SIZE;
                bloco[i][j].w = BLOCK_SIZE;
                bloco[i][j].h = 77;
                bloco[i][j].wy = 0;
                bloco[i][j].dano = false;
                bloco[i][j].fim = true;
                bloco[i][j].sprite = al_load_bitmap("./imagens/banner.png");
            } else {
                bloco[i][j].y = OUT;
                bloco[i][j].x = OUT;
                bloco[i][j].w = BLOCK_SIZE;
                bloco[i][j].h = BLOCK_SIZE;
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
    
    //if(n1_x + n1_w > n2_x && n1_x < n2_x + n2_w && n1_y + n1_h > n2_y && n1_y < n2_y + n2_h)
    //    return 1;

    if ((((n2_y-n2_h/2 >= n1_y-n1_y/2) && (n1_y+n1_h/2 >= n2_y-n2_h/2)) ||
		((n1_y-n1_h/2 >= n2_y-n2_h/2) && (n2_y+n2_h/2 >= n1_y-n1_h/2))) && 
		(((n2_x-n2_w/2 >= n1_x-n1_w/2) && (n1_x+n1_w/2 >= n2_x-n2_w/2)) || 	
		((n1_x-n1_w/2 >= n2_x-n2_w/2) && (n2_x+n2_w/2 >= n1_x-n1_w/2)))) return 1;
	else return 0;																																		
}

void update_bullets(torre *tower){

    bullet *previous = NULL;
    for(bullet *index = tower->gun->shots; index!=NULL;){
        if(!index->dir)
            index->x -= BULLET_MOVE;
        else if(index->dir == 1)
            index->x += BULLET_MOVE;

        if(index->x < 0){

            if(previous){
                previous->next = index->next;
                bullet_destroy(index);
                index = (bullet *) previous->next;
            } else {
                tower->gun->shots = (bullet *) index->next;
                bullet_destroy(index);
                index = tower->gun->shots;

            }
        } else{
            previous = index;
            index = (bullet *) index->next;
        }
    }
}

void update_position(personagem *player_1 , inimigo **vetor_inimigos, serpente *vetor_serpentes[2], plataforma *plataform){
    
    bool jump = false;  
    int gravidade = GRAVIDADE;
    int jumpSpeed = 15;

    if(player_1->timer > 0){
        player_1->timer--;
    }
    // movimenta para esquerda
    if (player_1->controle->left){
        updateBackground(&bg, 1);
        personagem_move(player_1, 1, 0, X_FASE, Y_SCREEN);
        
        // Verifica a colisao com blocos a esquerda
        for(int i = 0; i<X_MAPA; i++){
            for(int j = 0; j< Y_MAPA; j++){
                if(((bloco[i][j].x + bloco[i][j].w/2 >= player_1->x - player_1->width/2) &&
                (player_1->x - player_1->width/2 >= bloco[i][j].x - bloco[i][j].w/2)) && 
                ((bloco[i][j].y + bloco[i][j].h/2 >= player_1->y - player_1->height/2) &&
                (player_1->y - player_1->height/2 >= bloco[i][j].y - bloco[i][j].h/2))){
                    personagem_move(player_1, -1, 0, X_FASE, Y_SCREEN);
                }
            }
        }

        for(int i = 0; i < 2; i++)
            if(verificar_colisao(player_1->x, player_1->y, player_1->width, player_1->height,
                vetor_serpentes[i]->x, vetor_serpentes[i]->y, vetor_serpentes[i]->width, vetor_serpentes[i]->height))
                personagem_move(player_1, -1, 0, X_FASE, Y_SCREEN - 20);
    }

    if (player_1->controle->right){
        updateBackground(&bg, -1);

        personagem_move(player_1, 1, 1, X_FASE, Y_SCREEN);

        // verifica colisao a direita com os blocos
        for(int i = 0; i<X_MAPA; i++){
            for(int j = 0; j< Y_MAPA; j++){
                if(((player_1->x + player_1->width/2 >= bloco[i][j].x - bloco[i][j].w/2) && 
                (bloco[i][j].x - bloco[i][j].w/2 >= player_1->x - player_1->width/2)) && 
                ((player_1->y + player_1->height/2 >= bloco[i][j].y - bloco[i][j].h/2) 
                && (bloco[i][j].y - bloco[i][j].h/2 >= player_1->y - player_1->height/2))){

                    personagem_move(player_1, -1, 1, X_FASE, Y_SCREEN);
                }
            }
        }


        for(int i = 0; i < 2; i++)
            if(verificar_colisao(player_1->x, player_1->y, player_1->width, player_1->height,
                vetor_serpentes[i]->x, vetor_serpentes[i]->y, vetor_serpentes[i]->width, vetor_serpentes[i]->height))
                personagem_move(player_1, -1, 1, X_FASE, Y_SCREEN - 20);

    }
    if (player_1->controle->up){
        personagem_move(player_1, 1, 2, X_FASE, Y_SCREEN);
        for(int i = 0; i < 2; i++)
            if(verificar_colisao(player_1->x, player_1->y, player_1->width, player_1->height,
                vetor_serpentes[i]->x, vetor_serpentes[i]->y, vetor_serpentes[i]->width, vetor_serpentes[i]->height))
                personagem_move(player_1, -1, 2, X_FASE, Y_SCREEN - 20);
    }

    if (player_1->controle->down){
        personagem_move(player_1, 1, 3, X_SCREEN, Y_SCREEN);
        for(int i = 0; i < 2; i++)
            if(verificar_colisao(player_1->x, player_1->y, player_1->width, player_1->height,
                vetor_serpentes[i]->x, vetor_serpentes[i]->y, vetor_serpentes[i]->width, vetor_serpentes[i]->height))
                    personagem_move(player_1, -1, 3, X_FASE, Y_SCREEN - 20);
    }

    if (player_1->controle->agachar && !player_1->agachado){
        player_1->height = 50;
        player_1->y = player_1->y + player_1->height/2;
        player_1->agachado = true;
    } else if(!player_1->controle->agachar && player_1->agachado){
        player_1->y = player_1->y - player_1->height/2;
        player_1->height = 77;
        player_1->agachado= false;
    }

    // colisao dos blocos
    for(int i = 0; i < X_MAPA; i++){
        for(int j = 0; j< Y_MAPA; j++){
            if(verificar_colisao(player_1->x +10, player_1->y+20, player_1->width, player_1->height,
                bloco[i][j].x, bloco[i][j].y, bloco[i][j].w, bloco[i][j].h)){
                player_1->y = bloco[i][j].y - player_1->height;
                jump = true;
               
                if(bloco[i][j].dano && !player_1->timer){
                    player_1->hp--;
                    player_1->timer = INVENCIBILIDADE;
                    printf("Atingido\n");
                }
                if(bloco[i][j].fim){
                    player_1->venceu = true;
                }
            }

            // Verifica a colisão da serpente
            for(int w =0; w<2; w++){
                if(verificar_colisao(vetor_serpentes[w]->x , vetor_serpentes[w]->y +20, vetor_serpentes[w]->width, vetor_serpentes[w]->height,
                    bloco[i][j].x, bloco[i][j].y, bloco[i][j].w, bloco[i][j].h)){

                    vetor_serpentes[w]->jump = true;
                }

            }


            // verifica a colisao do inimigo
            for(int z =0; z<MAX_ENEMYS; z++){
                if(verificar_colisao(vetor_inimigos[z]->x , vetor_inimigos[z]->y+20, vetor_inimigos[z]->width, vetor_inimigos[z]->height,
                    bloco[i][j].x, bloco[i][j].y, bloco[i][j].w, bloco[i][j].h)){
                    vetor_inimigos[z]->jump = true;
                    
                }
            }
        }
    }

    // colisao serpente vs player
    for(int w = 0; w < 2; w ++){
        if(verificar_colisao( player_1->x, player_1->y, player_1->width, player_1->height,
          vetor_serpentes[w]->x , vetor_serpentes[w]->y, vetor_serpentes[w]->width, vetor_serpentes[w]->height)){

        jump = true;
        if(!player_1->timer){
                player_1->hp--;
                player_1->timer = INVENCIBILIDADE;
                printf("Atingido\n");
            }
        }
    }

    for(int z =0; z<MAX_ENEMYS; z++){
        if(verificar_colisao(player_1->x, player_1->y, player_1->width, player_1->height,
          vetor_inimigos[z]->x, vetor_inimigos[z]->y, vetor_inimigos[z]->width, vetor_inimigos[z]->height)){
                        
            jump = true;
            if(!player_1->timer){
                player_1->hp--;
                player_1->timer = INVENCIBILIDADE;
                printf("Atingido\n");
            }
        }
    }

    if(verificar_colisao(player_1->x , player_1->y + 20, player_1->width, player_1->height,
      plataform->x , plataform->y, plataform->w, plataform->h))
        jump = true;
    // faz o player pular
    if (player_1->controle->jump && jump){
        player_1->vel_y = -jumpSpeed;
        jump = false;
    }

    player_1->y += player_1->vel_y;
    // gravidade para o player
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

    // gravidade para os inimigos
    for(int z = 0; z<MAX_ENEMYS; z++){
        vetor_inimigos[z]->y += vetor_inimigos[z]->vel_y;

        if(!vetor_inimigos[z]->jump)
            vetor_inimigos[z]->vel_y += gravidade;
        else 
            vetor_inimigos[z]->vel_y = 0;
        
    }
    // mover o inimigo
    for(int z = 0; z<MAX_ENEMYS; z++){
        if(!vetor_inimigos[z]->dir){
            inimigo_move(vetor_inimigos[z], 1, 0, X_FASE, Y_SCREEN);
        } else {
            inimigo_move(vetor_inimigos[z], 1, 1, X_FASE, Y_SCREEN);
        }
        
        if(vetor_inimigos[z]->x <= 2300){
            vetor_inimigos[z]->dir = 1;
        } else if(vetor_inimigos[z]->x >= 2730){
            vetor_inimigos[z]->dir = 0;
        }
    }

    if(!plataform->dir){
        plataforma_move(plataform, 1, 0);
    } else {
        plataforma_move(plataform, 1, 1);
    }
        
    if(plataform->x <= 4300){
        plataform->dir = 1;
    } else if(plataform->x >= 4420 + 650){
        plataform->dir = 0;
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
    float scale = 1.0f;

    float frame = 0.0f, frame_serpente = 0.0f, frame_inimigo = 0.0f;
    int pos_x = 0, pos_y = 0;
    int current_frame_y = 0;
    int kill = 0;


    float cameraPosition[2] = {0, 0};

    int loadCounterX = 0, loadCounterY = 0, mapSizeX = X_MAPA, mapSizeY = Y_MAPA;
    int map[100][100];


    
    // inimigo *vetor_inimigos[MAX_ENEMYS];
    inimigo *vetor_inimigos[MAX_ENEMYS];
    serpente *vetor_serpentes[2];
    torre *tower;


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

    personagem* player_1 = personagem_create(5, 77, 50, 25.0, Y_SCREEN/2, X_SCREEN, Y_SCREEN);
    // personagem* player_1 = personagem_create(3, 77, 50, X_SCREEN/2, Y_SCREEN/2, X_SCREEN, Y_SCREEN);
    if (!player_1) return 1;

    // for(int i = 0; i<MAX_ENEMYS; i++){
    //     vetor_inimigos[i] = inimigo_create(77, 50, 1 + rand()%1280, Y_SCREEN - 60 - 25, X_SCREEN, Y_SCREEN);

    // }
    vetor_inimigos[0] = inimigo_create(2730, Y_SCREEN/2, 60, 60, X_FASE, Y_SCREEN);
    tower = torre_create(1500 + 190, 440, 60, 120, 0);
    //2500
    // Vetor de serpentes
    vetor_serpentes[0] = serpente_create(72, 96, 350 + 65, Y_SCREEN/2, X_FASE, Y_SCREEN, al_load_bitmap("./imagens/snake.png"));
    vetor_serpentes[1] = serpente_create(72, 96, 720 + 145, Y_SCREEN/2, X_FASE, Y_SCREEN, al_load_bitmap("./imagens/snake.png"));

    plataforma *plataform = plataforma_create(4420, Y_SCREEN - 65, 120, 30);
    if(!plataform){
        printf("Não foi possivel\n");
    }
    ALLEGRO_BITMAP *background = al_load_bitmap(BACKGROUND_FILE);
    ALLEGRO_BITMAP *torre_skin = al_load_bitmap("./imagens/torre.png");

    ALLEGRO_BITMAP *sprite_inimigo = al_load_bitmap("./imagens/samurai.png");
    ALLEGRO_BITMAP *sprite_inimigo_invertido = al_load_bitmap("./imagens/samurai_invertido.png");
    if(!sprite_inimigo || !sprite_inimigo_invertido){
        printf("Não foi possivel carregar o bitmap\n");
    }

    // inicia o background
    initBackground(&bg, 0, 0, 1, 0, 1065, 600, -1, 1, background);
    loadMap("./mapas/fase1.txt", map, mapSizeX, mapSizeY);

    ALLEGRO_EVENT event;

    al_start_timer(timer);
    
    //-----------------------------------
    // Jogo

    while(1){

        al_wait_for_event(queue, &event);

        if(menu){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 0, 0), X_SCREEN/2, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "TAKAKARANOMURO TWO");
            al_draw_text(font, al_map_rgb(255, 0, 0), X_SCREEN/2, Y_SCREEN/2 + 40, ALLEGRO_ALIGN_CENTER, "PRESSIONE ENTER");
            al_flip_display();  
            if ((event.type == 10) || (event.type == 12) && event.keyboard.keycode == ALLEGRO_KEY_ENTER) menu = false;
                  
        } else {
            if(kill){
                al_identity_transform(&camera);
                al_use_transform(&camera);
                
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(0, 0, 255), X_SCREEN/2, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "GAME OVER");
                al_draw_text(font, al_map_rgb(0, 0, 255), X_SCREEN/2, Y_SCREEN/2 + 50, ALLEGRO_ALIGN_CENTER, "Precione enter para sair");
                al_flip_display();
                if ((event.type == 10) || (event.type == 12) && event.keyboard.keycode == ALLEGRO_KEY_ENTER) break;
                        
            } else {
                if(player_1->venceu){
                al_identity_transform(&camera);
                al_use_transform(&camera);
                
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(0, 0, 255), X_SCREEN/2, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "YOU WIN!");
                al_draw_text(font, al_map_rgb(0, 0, 255), X_SCREEN/2, Y_SCREEN/2 + 50, ALLEGRO_ALIGN_CENTER, "Precione enter para sair");
                al_flip_display();
                if ((event.type == 10) || (event.type == 12) && event.keyboard.keycode == ALLEGRO_KEY_ENTER) break;
                }else{
                    if(event.type == 30){
                        
                        
                        al_identity_transform(&camera);
                        al_use_transform(&camera);

                        // Atualiza a posicao;
                        update_position(player_1, vetor_inimigos, vetor_serpentes, plataform);
                        kill = verificar_morte(player_1, tower);

                        // Desenha o background e faz ele ir para trás
                        drawBackground(&bg);
                        

                        atualizarCamera(cameraPosition, player_1->x, player_1->y, player_1->width, player_1->height);
                        
                        al_identity_transform(&camera);
                        al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
                        al_scale_transform(&camera, scale, scale);
                        al_use_transform(&camera);

                        
                        drawMap(map, mapSizeX, mapSizeY, NULL);

                        //desenha o personagem;
                        al_draw_filled_rectangle(player_1->x-player_1->width/2, player_1->y-player_1->height/2, player_1->x+player_1->width/2, player_1->y+player_1->height/2, al_map_rgb(255, 0, 0));
                            

                        // Desenha os inimigos
                        for(int i = 0; i<MAX_ENEMYS; i++){

                            al_draw_filled_rectangle(vetor_inimigos[i]->x-vetor_inimigos[i]->width/2, 
                                vetor_inimigos[i]->y-vetor_inimigos[i]->height/2, vetor_inimigos[i]->x+vetor_inimigos[i]->width/2, vetor_inimigos[i]->y+vetor_inimigos[i]->height/2, al_map_rgb(0, 0, 255));
                        }

                        // Desenhar o sprite na tela
                        
                        animacao(player_1, vetor_serpentes, &frame, &frame_serpente);

                        //al_draw_filled_rectangle(tower->x - tower->width/2, tower->y - tower->height/2, tower->x + tower->width/2, tower->y+tower->height/2, al_map_rgb(255, 0, 255));
                        al_draw_bitmap(torre_skin, tower->x - tower->width/2, tower->y - tower->height/2, 0);
                        if(!tower->gun->timer){
                            torre_shot(tower);
                            tower->gun->timer = PISTOL_COOLDOW;
                        }

                        
                        
                        update_bullets(tower);
                            
                        for(bullet *index = tower->gun->shots; index != NULL; index = (bullet *) index->next){
                                al_draw_filled_circle(index->x, index->y, 5, al_map_rgb(0,0,0));
                        }
                        if(tower->gun->timer)
                            tower->gun->timer--;


                        frame_serpente += 0.03f;
                        if(frame_serpente > 3){
                            frame_serpente -= 3;
                        }
                        // Desenha o sprite da serpente;
                        for(int w =0; w<2; w++){
                            al_draw_filled_rectangle(vetor_serpentes[w]->x-vetor_serpentes[w]->width/2, 
                            vetor_serpentes[w]->y-vetor_serpentes[w]->height/2, vetor_serpentes[w]->x+vetor_serpentes[w]->width/2, vetor_serpentes[w]->y+vetor_serpentes[w]->height/2, al_map_rgb(0, 0, 255));
                            al_draw_bitmap_region(vetor_serpentes[w]->skin, 96 * (int) frame_serpente, 0, 96, 72, vetor_serpentes[w]->x - vetor_serpentes[w]->width/ 2, vetor_serpentes[w]->y - vetor_serpentes[w]->height /2, 0);
                        }


                        al_draw_filled_rectangle(vetor_inimigos[0]->x - vetor_inimigos[0]->width/2, vetor_inimigos[0]->y - vetor_inimigos[0]->height/2, vetor_inimigos[0]->x + vetor_inimigos[0]->width/2, vetor_inimigos[0]->y+vetor_inimigos[0]->height/2, al_map_rgb(144, 8, 255));
                        frame_inimigo += 0.6f;
                        if(frame_inimigo > 6){
                            frame_inimigo -= 6;
                        }
                        // Desenha o sprite do inimigo;
                        if(!vetor_inimigos[0]->dir){
                            al_draw_bitmap_region(sprite_inimigo_invertido, 0, 60 * (int) frame_inimigo, 60, 60, vetor_inimigos[0]->x - vetor_inimigos[0]->width/2, vetor_inimigos[0]->y - vetor_inimigos[0]->height/2, 0);
                        } else {
                            al_draw_bitmap_region(sprite_inimigo, 60, 60 * (int) frame_inimigo, 60, 60, vetor_inimigos[0]->x - vetor_inimigos[0]->width/2, vetor_inimigos[0]->y - vetor_inimigos[0]->height/2, 0);
                        }

                        // Desenha a plataforma
                        al_draw_filled_rectangle(plataform->x-plataform->w/2, 
                            plataform->y-plataform->h/2, plataform->x+plataform->w/2, plataform->y+plataform->h/2, al_map_rgb(100, 100, 100));
                        
                        
                        al_flip_display();
                    } else if ((event.type == 10) || (event.type == 12)){

                        if (event.keyboard.keycode == 82) joystick_left(player_1->controle);
                        else if (event.keyboard.keycode == 83) joystick_right(player_1->controle);
                        // else if (event.keyboard.keycode == 84) joystick_up(player_1->controle);
                        // else if (event.keyboard.keycode == 85) joystick_down(player_1->controle);
                        else if (event.keyboard.keycode == ALLEGRO_KEY_LCTRL) joystick_agachar(player_1->controle);
                        else if(event.keyboard.keycode == ALLEGRO_KEY_SPACE) joystick_jump(player_1->controle);
                        else if(event.keyboard.keycode == ALLEGRO_KEY_PAD_MINUS) scale-=0.2f;
                        else if(event.keyboard.keycode == ALLEGRO_KEY_PAD_PLUS) scale += 0.2f;

                    } else if(player_1->hp <= 0){
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_text(font, al_map_rgb(255, 0, 0), X_SCREEN/2, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Game Over");
                        al_flip_display();

                    } else if(event.type == 42)
                        break;
                }
            }
        }
    }

    
    for(int i = 0; i<X_MAPA; i++){
        for(int j = 0; j< Y_MAPA; j++){
            al_destroy_bitmap(bloco[i][j].sprite);
        }
    }

    for(int i = 0; i<2; i++){
        serpente_destroy(vetor_serpentes[i]);
    }

    for(int i = 0; i<MAX_ENEMYS; i++){
        inimigo_destroy(vetor_inimigos[i]);
    }

    plataforma_destroy(plataform);
    personagem_destroy(player_1);
    al_destroy_bitmap(background);

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}