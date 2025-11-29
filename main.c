


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
#include "./recursos/estalactite.h"

#define BACKGROUND_FILE "./imagens/bg2.jpg"
#define PERSONAGEM_SPRITE "./imagens/ninja.png"

#define X_SCREEN 800
#define Y_SCREEN 600
#define X_FASE 7000
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

void desenhar_barra_vida(int x, int y, int vida_atual, int vida_maxima){
    float largura = 100.0;
    float altura = 20.0;

    float proporcao = (float) vida_atual/vida_maxima;

    if (proporcao < 0)
        proporcao = 0;
    if (proporcao > 1)
        proporcao = 1;

    float largura_vida = largura * proporcao;

    al_draw_filled_rectangle(x, y, x + largura, y + altura, al_map_rgb(150, 0, 0));

    al_draw_filled_rectangle(x, y , x + largura_vida, y + altura,al_map_rgb(0, 0, 200));

}

void loadMap(const char *filename, int map [100][100], int max_x, int max_y){
    char buffer;
    
    FILE *arquivo = fopen(filename, "r+b");
    if(!arquivo){
        printf("Não abriu o arquivo\n");
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
                bloco[i][j].escalavel = false;
                bloco[i][j].sprite = al_load_bitmap("./imagens/Pedaco_de_grama.png");
            } else if(map[i][j] == 51){
                bloco[i][j].y = i * BLOCK_SIZE;
                bloco[i][j].x = j * BLOCK_SIZE;
                bloco[i][j].w = BLOCK_SIZE;
                bloco[i][j].h = BLOCK_SIZE;
                bloco[i][j].wy = 0;
                bloco[i][j].dano = true;
                bloco[i][j].fim = false;
                bloco[i][j].escalavel = false;
                bloco[i][j].sprite = al_load_bitmap("./imagens/espinhos.png");
            
            }else if(map[i][j] == 52){
                bloco[i][j].y = i * BLOCK_SIZE;
                bloco[i][j].x = j * BLOCK_SIZE;
                bloco[i][j].w = BLOCK_SIZE;
                bloco[i][j].h = BLOCK_SIZE;
                bloco[i][j].wy = 0;
                bloco[i][j].dano = true;
                bloco[i][j].fim = false;
                bloco[i][j].escalavel = false;
                bloco[i][j].sprite = al_load_bitmap("./imagens/water2.png");
            }else if(map[i][j] == 53){
                bloco[i][j].y = i * BLOCK_SIZE;
                bloco[i][j].x = j * BLOCK_SIZE;
                bloco[i][j].w = BLOCK_SIZE;
                bloco[i][j].h = 77;
                bloco[i][j].wy = 0;
                bloco[i][j].dano = false;
                bloco[i][j].fim = true;
                bloco[i][j].escalavel = true;
                bloco[i][j].sprite = al_load_bitmap("./imagens/banner.png");
            }
            else if(map[i][j] == 54){
                bloco[i][j].y = i * BLOCK_SIZE;
                bloco[i][j].x = j * BLOCK_SIZE;
                bloco[i][j].w = BLOCK_SIZE;
                bloco[i][j].h = 77;
                bloco[i][j].wy = 0;
                bloco[i][j].dano = false;
                bloco[i][j].fim = false;
                bloco[i][j].escalavel = true;
                bloco[i][j].sprite = al_load_bitmap("./imagens/escadas.png");
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
            al_draw_bitmap(bloco[i][j].sprite, bloco[i][j].x - bloco[i][j].w/2,bloco[i][j].y - bloco[i][j].h/2, 0);
        }
    }
}


void atualizarCamera(float *cameraPosition, float x, float y, int width, int height){
        cameraPosition[0] = -( X_SCREEN / 2) + (x + width/2) ;

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

	else return 0;																																		
}

void update_bullets(torre *tower){

    bullet *previous = NULL;
    for(bullet *index = tower->gun->shots; index!=NULL;){
        if(!index->dir)
            index->x -= BULLET_MOVE;
        else if(index->dir == 1)
            index->x += BULLET_MOVE;

        if(index->x < 750){

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

void update_position(personagem *player_1 , inimigo **vetor_inimigos, serpente *vetor_serpentes[2], 
    plataforma *plataform, torre *tower, estalactite *vetor_estalactites[2]){
    
    bool jump = false;  
    int gravidade = GRAVIDADE;
    int jumpSpeed = 15;


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
                (player_1->y - player_1->height/2 >= bloco[i][j].y - bloco[i][j].h/2)) && !bloco[i][j].escalavel){
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
                && (bloco[i][j].y - bloco[i][j].h/2 >= player_1->y - player_1->height/2)) && !bloco[i][j].escalavel){

                    personagem_move(player_1, -1, 1, X_FASE, Y_SCREEN);
                }
            }
        }


        for(int i = 0; i < 2; i++)
            if(verificar_colisao(player_1->x, player_1->y, player_1->width, player_1->height,
                vetor_serpentes[i]->x, vetor_serpentes[i]->y, vetor_serpentes[i]->width, vetor_serpentes[i]->height))
                personagem_move(player_1, -1, 1, X_FASE, Y_SCREEN - 20);

    }
    if (player_1->controle->up && player_1->escalar){
        personagem_move(player_1, 1, 2, X_FASE, Y_SCREEN);
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
            if(verificar_colisao(player_1->x , player_1->y + 10 , player_1->width, player_1->height,
                bloco[i][j].x, bloco[i][j].y, bloco[i][j].w, bloco[i][j].h)){
                
                // verifico se o player não está colidindo por baixo e o bloco não é escalavel
                if(!bloco[i][j].escalavel){
                    player_1->y = bloco[i][j].y - player_1->height;
                }
                jump = true;
               
                if(bloco[i][j].dano && !player_1->timer){
                    player_1->hp--;
                    player_1->timer = INVENCIBILIDADE;

                }
                if(bloco[i][j].fim){
                    player_1->venceu = true;
                }
                if(bloco[i][j].escalavel){
                    player_1->escalar = true;
                } else {
                    player_1->escalar = false;
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

    for(int a = 0; a < 2; a++){
        if(vetor_estalactites[a] != NULL){
            if(player_1->x + player_1->width/2 >= vetor_estalactites[a]->x - vetor_estalactites[a]->width/2){
                vetor_estalactites[a]->caindo = true;
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

            }
        }
    }

    // Colisão inimigo vs player
    for(int z =0; z<MAX_ENEMYS; z++){
        if(verificar_colisao(player_1->x, player_1->y, player_1->width, player_1->height,
          vetor_inimigos[z]->x, vetor_inimigos[z]->y, vetor_inimigos[z]->width, vetor_inimigos[z]->height)){
                        
            jump = true;
            if(!player_1->timer){
                player_1->hp--;
                player_1->timer = INVENCIBILIDADE;

            }
            if(player_1->controle->left){
                personagem_move(player_1, -1, 0, X_FASE, Y_SCREEN);
                
            } else if(player_1->controle->right)
                personagem_move(player_1, -1, 1, X_FASE, Y_SCREEN);


            if(!vetor_inimigos[z]->dir){
                inimigo_move(vetor_inimigos[z], -1, 0, X_FASE, Y_SCREEN);
            } else {
                inimigo_move(vetor_inimigos[z], -1, 1, X_FASE, Y_SCREEN);
            }
        }
    }


    // colisao player vs torre
    if(verificar_colisao(player_1->x, player_1->y, player_1->width, player_1->height,
        tower->x , tower->y, tower->width, tower->height)){
        
        jump = true;
        
        if(player_1->controle->left){
            personagem_move(player_1, -1, 0, X_FASE, Y_SCREEN);
                
        } else if(player_1->controle->right)
            personagem_move(player_1, -1, 1, X_FASE, Y_SCREEN);

    }
    
    // Colisao com a plataforma
    if(verificar_colisao(player_1->x , player_1->y + 20, player_1->width, player_1->height,
      plataform->x , plataform->y, plataform->w, plataform->h))
        jump = true;

    // Colisao player vs estalactite
    for(int a = 0; a<2; a++){
        if(vetor_estalactites[a] != NULL){
            if(verificar_colisao( player_1->x, player_1->y, player_1->width, player_1->height,
            vetor_estalactites[a]->x , vetor_estalactites[a]->y, vetor_estalactites[a]->width, vetor_estalactites[a]->height)){

                jump = true;
                if(!player_1->timer){
                    player_1->hp--;
                    player_1->timer = INVENCIBILIDADE;
                }
                
            }
        }
    }

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

    // gravidade para as estalactites
    for(int a = 0; a < 2 ; a++){
        if(vetor_estalactites[a] != NULL){
            vetor_estalactites[a]->y += vetor_estalactites[a]->vel_y;
            
            // Não quero que as estalactites caiam infinitamente
            if(vetor_estalactites[a]->caindo && (vetor_estalactites[a]->y - vetor_estalactites[a]->height/2 <= Y_SCREEN ))
                vetor_estalactites[a]->vel_y += gravidade;
            else 
                vetor_estalactites[a]->vel_y = 0;
        }
    }

}


int main(){


    // -----------------------------------
    // Iniciação componentes
    al_init();
    al_install_keyboard();
    al_install_audio();

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
    float volume = 1.0f;

    float cameraPosition[2] = {0, 0};

    int mapSizeX = X_MAPA, mapSizeY = Y_MAPA;
    int map[100][100];

    char barraVolume[5];
    
    inimigo *vetor_inimigos[MAX_ENEMYS];
    serpente *vetor_serpentes[2];
    torre *tower;

    estalactite *vetor_estalactites[2];

    ALLEGRO_TIMER *timer = al_create_timer(1.0/30.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_FONT *font = al_load_ttf_font("./imagens/Freedom-10eM.ttf", 36, 0);
    ALLEGRO_FONT *font2 = al_create_builtin_font();
    ALLEGRO_DISPLAY *disp = al_create_display(X_SCREEN, Y_SCREEN);

    ALLEGRO_TRANSFORM camera;
    al_reserve_samples(1); 
    ALLEGRO_SAMPLE *song = al_load_sample("./audio/GreatBoss.ogg");

    ALLEGRO_SAMPLE_INSTANCE *song_instance = al_create_sample_instance(song);
    if(!song || !song_instance){
        printf("Não foi possivel criar a musica\n");
        return 1;
    }
    // -----------------------------------
    // Iniciando a fila

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_set_window_title(disp, "Game");


    // -----------------------------------
    // Elementos

    al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());
    personagem* player_1 = personagem_create(5, 77, 50, 25.0, Y_SCREEN/2, X_SCREEN, Y_SCREEN);
    if (!player_1){
        printf("Não foi possivel criar o personagem");
        return 1;
    }
    vetor_inimigos[0] = inimigo_create(2730, Y_SCREEN/2, 60, 60, X_FASE, Y_SCREEN);

    if(!vetor_inimigos[0]){
        printf("Não foi possivel criar o inimigo\n");
        return 1;
    }
    tower = torre_create(1500 + 190, 440, 60, 120, 0);
    if(!tower){
        printf("Não foi possivel criar a torre\n");
        return 1;
    }
    // Vetor de serpentes
    vetor_serpentes[0] = serpente_create(72, 96, 350 + 65, Y_SCREEN/2, X_FASE, Y_SCREEN, al_load_bitmap("./imagens/snake.png"));
    vetor_serpentes[1] = serpente_create(72, 96, 720 + 145, Y_SCREEN/2, X_FASE, Y_SCREEN, al_load_bitmap("./imagens/snake.png"));
    
    if(!vetor_serpentes[0] || !vetor_serpentes[1]){
        printf("Não foi possivel criar as serpentes\n");
        return 1;
    }
    // Vetor de estalactites
    vetor_estalactites[0] = estalactite_create(2080, 20, 65, 40);
    vetor_estalactites[1] = estalactite_create(6240, 20, 65 , 40);

    if(!vetor_estalactites[0] || !vetor_estalactites[1]){
        printf("Não foi possivel criar as estalactites\n");
        return 1;
    }
    plataforma *plataform = plataforma_create(4420, Y_SCREEN - 65, 120, 30);
    if(!plataform){
        printf("Não foi possivel criar a plataformal\n");
        return 1;
    }
    ALLEGRO_BITMAP *background = al_load_bitmap(BACKGROUND_FILE);
    ALLEGRO_BITMAP *torre_skin = al_load_bitmap("./imagens/torre.png");

    ALLEGRO_BITMAP *sprite_inimigo = al_load_bitmap("./imagens/samurai.png");
    ALLEGRO_BITMAP *sprite_inimigo_invertido = al_load_bitmap("./imagens/samurai_invertido.png");

    if(!sprite_inimigo || !sprite_inimigo_invertido || !background || !torre_skin){
        printf("Não foi possivel carregar o bitmap\n");
        return 1;
    }

    // inicia o background
    initBackground(&bg, 0, 0, 1, 0, 1065, 600, -1, 1, background);
    loadMap("./mapas/fase1.txt", map, mapSizeX, mapSizeY);

    al_play_sample_instance(song_instance);

    ALLEGRO_EVENT event;

    al_start_timer(timer);
    
    //-----------------------------------
    // Jogo

    while(1){

        al_wait_for_event(queue, &event);

        if(menu){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 0, 0), X_SCREEN/2, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "TAKAKARANOMURO DOIS");
            al_draw_text(font, al_map_rgb(255, 0, 0), X_SCREEN/2, Y_SCREEN/2 + 40, ALLEGRO_ALIGN_CENTER, "PRESSIONE ENTER");

            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    volume += 0.2f;
                    if (volume > 1.0f) volume = 1.0f;
                        al_set_mixer_gain(al_get_default_mixer(), volume);
                }
                
                if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    volume -= 0.2f;
                    if (volume < 0.0f) volume = 0.0f;
                        al_set_mixer_gain(al_get_default_mixer(), volume);
                

                }
            }
                        
            int barras = (int)(volume * 5);

            for (int i = 0; i < barras; i++)
                barraVolume[i] = '-';

            barraVolume[barras] = '\0';

            al_draw_text(font2, al_map_rgb(255,0, 0), X_SCREEN/2, Y_SCREEN/2 + 80, ALLEGRO_ALIGN_CENTER, "Volume:");
            al_draw_text(font2, al_map_rgb(255,255,255), X_SCREEN/2 + 50, Y_SCREEN/2 + 80, 0, barraVolume);



            al_flip_display();  
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) menu = false;
            if (event.type == 42) break;

        } else {
            if(kill){
                al_identity_transform(&camera);
                al_use_transform(&camera);
                
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(0, 0, 255), X_SCREEN/2, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "GAME OVER");
                al_draw_text(font, al_map_rgb(0, 0, 255), X_SCREEN/2, Y_SCREEN/2 + 50, ALLEGRO_ALIGN_CENTER, "Pressione enter para sair");
                al_flip_display();
                if(event.keyboard.keycode == ALLEGRO_KEY_ENTER) break;
                if (event.type == 42) break;
                        
            } else {
                if(player_1->venceu){
                al_identity_transform(&camera);
                al_use_transform(&camera);
                
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(0, 0, 255), X_SCREEN/2, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "YOU WIN!");
                al_draw_text(font, al_map_rgb(0, 0, 255), X_SCREEN/2, Y_SCREEN/2 + 50, ALLEGRO_ALIGN_CENTER, "Pressione enter para sair");
                al_flip_display();
                if ((event.type == 10) || (event.type == 12) && event.keyboard.keycode == ALLEGRO_KEY_ENTER) break;
                }else{
                    if(event.type == 30){
                        
                        
                        al_identity_transform(&camera);
                        al_use_transform(&camera);

                        // Atualiza a posicao;
                        update_position(player_1, vetor_inimigos, vetor_serpentes, plataform, tower, vetor_estalactites);
                        kill = verificar_morte(player_1, tower);

                        // Desenha o background e faz ele ir para trás
                        drawBackground(&bg);
                        desenhar_barra_vida(80, 20, player_1->hp, 5);


                        atualizarCamera(cameraPosition, player_1->x, player_1->y, player_1->width, player_1->height);
                        
                        al_identity_transform(&camera);
                        al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
                        al_scale_transform(&camera, scale, scale);
                        al_use_transform(&camera);

                        
                        
                        drawMap(map, mapSizeX, mapSizeY, NULL);
                        
                        //desenha o personagem;
    
                        animacao(player_1, vetor_serpentes, &frame, &frame_serpente);

                        if(player_1->timer > 0){
                            player_1->timer--;
                        }
                        
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
                            al_draw_bitmap_region(vetor_serpentes[w]->skin, 96 * (int) frame_serpente, 0, 96, 72, vetor_serpentes[w]->x - vetor_serpentes[w]->width/ 2, vetor_serpentes[w]->y - vetor_serpentes[w]->height /2, 0);
                        }


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
                        
                        for(int a = 0; a<2; a++){
                            if(vetor_estalactites[a] != NULL)
                                al_draw_bitmap(vetor_estalactites[a]->skin, vetor_estalactites[a]->x - vetor_estalactites[a]->width/2, vetor_estalactites[a]->y - vetor_estalactites[a]->height/2, 0);
                        }
                        al_flip_display();
                    } else if ((event.type == 10) || (event.type == 12)){

                        if (event.keyboard.keycode == 82) joystick_left(player_1->controle);
                        else if (event.keyboard.keycode == 83) joystick_right(player_1->controle);
                        else if (event.keyboard.keycode == 84) joystick_up(player_1->controle);
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

    // Destroi os elementos no final do jogo
    
    for(int i = 0; i<X_MAPA; i++){
        for(int j = 0; j< Y_MAPA; j++){
            al_destroy_bitmap(bloco[i][j].sprite);
        }
    }

    for(int i = 0; i<2; i++){
        serpente_destroy(vetor_serpentes[i]);
    }

    for(int a = 0; a<2; a++){
        estalactite_destroy(vetor_estalactites[a]);
    }
    for(int i = 0; i<MAX_ENEMYS; i++){
        inimigo_destroy(vetor_inimigos[i]);
    }

    plataforma_destroy(plataform);
    personagem_destroy(player_1);
    torre_destroy(tower);

    al_destroy_bitmap(background);
    al_destroy_sample(song);
    al_destroy_sample_instance(song_instance);
    al_destroy_font(font);
    al_destroy_font(font2);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}