#ifndef CONSTANTS_H
#define CONSTANTS_H

// Headers
#include <Windows.h>

// Defines
#define SCREEN_WIDTH 150
#define SCREEN_HEIGHT 40
#define FRAME_RATE 5 // adjust this to control the update speed of the lander

// Keys
const int KEY_ESC = VK_ESCAPE;
const int KEY_ENTER = VK_RETURN;
const int KEY_W = 'W';
const int KEY_A = 'A';
const int KEY_D = 'D';
const int KEY_1 = '1';
const int KEY_2 = '2';
const int KEY_3 = '3';
const int KEY_4 = '4';

// Player parameters
const float ACCELERATION_RATE = 0.5f;
const float DECELERATION_RATE = 0.2f;
const float FUEL_CONSUMPTION_RATE = 2.0f;
const float STOPWATCH = 0.2f; //Counting up in real time a 5fps update 

#endif //!CONSTANTS_H