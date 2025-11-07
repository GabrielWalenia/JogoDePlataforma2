all:
	gcc main.c -o game $(pkg-config allegro-5 allegro_main-5 allegro_font-5 --libs --cflags)