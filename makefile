TARGET = game
SOURCES = main.c ./recursos/personagem.c ./recursos/inimigo.c ./recursos/estalactite.c ./recursos/plataforma.c ./recursos/joystick.c ./recursos/background.c ./recursos/serpente.c ./recursos/pistol.c ./recursos/bullet.c ./recursos/torre.c 
ALLEGRO_FLAGS = $(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_acodec-5 --libs --cflags)

all:
	gcc $(SOURCES) -o $(TARGET) $(ALLEGRO_FLAGS)
clean:
	rm game

debug:
	gcc -g $(SOURCES) -o  $(TARGET) $(ALLEGRO_FLAGS)