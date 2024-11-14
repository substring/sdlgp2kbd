#include <stdint.h>
#include <linux/input-event-codes.h>
#include <SDL_joystick.h>

#ifndef GAMEPAD_H
#define GAMEPAD_H
#define GAMEPAD_MAP_SIZE 64

/* This is an absolute copy of SDL3's SDL_GamepadMapping */
typedef struct GPmapping {
    uint16_t a;
    uint16_t b;
    uint16_t x;
    uint16_t y;
    uint16_t back;
    uint16_t guide;
    uint16_t start;
    uint16_t leftstick;
    uint16_t rightstick;
    uint16_t leftshoulder;
    uint16_t rightshoulder;
    uint16_t dpup;
    uint16_t dpdown;
    uint16_t dpleft;
    uint16_t dpright;
    uint16_t misc1;
    uint16_t misc2;
    uint16_t misc3;
    uint16_t misc4;
    uint16_t misc5;
    uint16_t misc6;
    uint16_t right_paddle1;
    uint16_t left_paddle1;
    uint16_t right_paddle2;
    uint16_t left_paddle2;
    uint16_t leftx;
    uint16_t lefty;
    uint16_t rightx;
    uint16_t righty;
    uint16_t lefttrigger;
    uint16_t righttrigger;
    uint16_t touchpad;
} GPmapping;


typedef struct GPdata {
    char gamepad_name[256];
    SDL_JoystickGUID guid;
    uint16_t vid;
    uint16_t pid;
    GPmapping mapping;
} GPdata;


int gamepad_assign_key(GPmapping* mapping, const char* event_name, const int event_value);
void print_gamepad(GPdata* gp);

#endif