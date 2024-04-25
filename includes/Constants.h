#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "SDL.h"
typedef SDL_Color Color;

// Constants for screen
const int W = 720;
const int H = 1000;
const int s60FPS = 16;
const int GAME_IS_RUNNING = 1;

// math
const float PI = 3.14159;

// options

// mouse options WARNING: ENABLING MOUSE CAN MESS WITH GAMEPLAY IF USING KEYBOARD
const bool ALLOW_ALL_MOUSE = true;
const bool ALLOW_MOUSE_MOVEMENT = false || ALLOW_ALL_MOUSE;
const bool ALLOW_MOUSE_SELECTION = false || ALLOW_ALL_MOUSE;
const bool ALLOW_MOUSE_SHOOTING = false || ALLOW_ALL_MOUSE;

const bool START_MUTED = false;

// for user's lasers
const Color USER_LASER_COLOR = {255, 255, 0, 0};
const Color ENEMY_LASER_COLOR = {255, 0, 0, 0};
const int LASER_SPEED = 8;
const int AMOUNT_OF_SHOOTABLE_LASERS = 3;
const int LASER_WIDTH_FOR_USER = 2;
/* const int LASER_WIDTH_FOR_USER = 800; */
const int LASER_LENGTH_FOR_USER = 15;

// for debugging
const bool ENEMIES_CAN_ATTACK = true;
const bool SPAWN_BLUES = true;
const bool SPAWN_PURPLES = true;
const bool SPAWN_REDS = true;
const bool SPAWN_FLAGS = true;
const int STARTING_WAVE = 1;
const bool INVINCIBILITY_FOR_SHIP = false;
const bool INVINCIBILITY_FOR_ENEMIES = false;

// mutable global variables
extern int RANDOM_FOR_ENEMY;
extern int RANDOM_FOR_FLAG;

#endif

