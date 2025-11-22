#ifndef __JOYSTICK__
#define __JOYSTICK__

typedef struct {
    unsigned char right;
    unsigned char left;
    unsigned char up;
    unsigned char down;
    unsigned char jump;
}joystick;

joystick* joystick_create();
void joystick_destroy(joystick *controle);
void joystick_right(joystick *controle);
void joystick_left(joystick *controle);
void joystick_up(joystick *controle);
void joystick_down(joystick *controle);
void joystick_jump(joystick *controle);

#endif