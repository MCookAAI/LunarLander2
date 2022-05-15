#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

// Headers
#include "Constants.h"

// STRUCTS
struct Player
{
	// Functions
	void Reset()
	{
		xPos = SCREEN_WIDTH / 2;
		yPos = 1;
		isAccelerating = false;
		acceleration = 0.0f;
		hasLanded = false;
		hasCrashed = false;
		stopwatch = 0;
		//score = 0;
	}
	
	// Constants
	static const int WIDTH = 3;
	static const int HEIGHT = 4;
	const char* CHARACTERS =
	{
		R"( ^ )"
		R"(/ \)"
		R"(|M|)"
		R"(/-\)"
	};
	const int COLOURS[WIDTH * HEIGHT] =
	{
		0xF,0xF,0xF,
		0xF,0xF,0xF,
		0xF,0x9,0xF,
		0xE,0xE,0xE,
	};
	
	// Variables
	int xPos = SCREEN_WIDTH / 2;
	int yPos = 1;
	bool isAccelerating = false;
	float acceleration = 0.0f;
	bool hasLanded = false;
	bool hasCrashed = false;
	float fuel = 100;
	float stopwatch = 0.0f;
	float score = 0.0f; //creating score as a variable so it can be used later
};

struct Explosion
{
	static const int WIDTH = 5;
	static const int HEIGHT = 5;
	const char* CHARACTERS1 = {
		R"(\\|//)"
		R"(=- -=)"
		R"(=- -=)"
		R"(=- -=)"
		R"(//|\\)"
	};
	const char* CHARACTERS2 = {
		R"(     )"
		R"( *** )"
		R"( *** )"
		R"( *** )"
		R"(     )"
	};
	const int COLOURS1[WIDTH * HEIGHT] = {
		0x4, 0x4, 0x4, 0x4, 0x4,
		0x4, 0x4, 0x4, 0x4, 0x4,
		0x4, 0x4, 0x4, 0x4, 0x4,
		0x4, 0x4, 0x4, 0x4, 0x4,
		0x4, 0x4, 0x4, 0x4, 0x4,
	};
	const int COLOURS2[WIDTH * HEIGHT] = {
		0x6, 0x6, 0x6, 0x6, 0x6,
		0x6, 0x6, 0x6, 0x6, 0x6,
		0x6, 0x6, 0x6, 0x6, 0x6,
		0x6, 0x6, 0x6, 0x6, 0x6,
		0x6, 0x6, 0x6, 0x6, 0x6,
	};
};

struct Background
{
	// Constants
	const char* CHARACTERS = // Must be 150 characters wide and 40 lines high
	{
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                            /\                                                                                                        )"
		R"(                                           /  \                                          /\                                                           )"
		R"(                                          /    \                                        /  \                                                          )"
		R"(                                         /      \                                      /    \                                                         )"
		R"(                                        /        \                                    /      \                                                        )"
		R"(                                       /          \                                  /        \___                                                    )"
		R"(                                      /            \                                /          xxx\                                                   )"
		R"(                                     /              |                              /               \              /\                                  )"
		R"(                                 ___/               |    _      /\                /                 \            /  \                                 )"
		R"(                                /xxx                |   | \    /  \              /                   \          /    \                                )"
		R"(                               /                    |___|  \  /    \            /                     \        /      \                               )"
		R"(                       /\     /                      xxx    \/      \          /                       \___/\_/        \                           ___)"
		R"(                      /  \   /                                       \        /                         xxx             \                         /xxx)"
		R"(                     /    \_/                                         \      /                                           \                       /    )"
		R"(                    /                                                  \    /                                             \                     /     )"
		R"(                    |                                                   \__/                                               \                   /      )"
		R"(                    |                                                                                                       \         ___     /       )"
		R"(                    |                                                                                                        \       /xxx\   /        )"
		R"(                    |                                                                                                         \     /     \_/         )"
		R"(                   /                                                                                                           \___/                  )"
		R"(                  /                                                                                                             xxx                   )"
		R"(                 /                                                                                                                                    )"
		R"(                /                                                                                                                                     )"
		R"(           /\  /                                                                                                                                      )"
		R"(          /  \/                                                                                                                                       )"
		R"(   ___   /                                                                                                                                            )"
		R"(  /xxx\_/                                                                                                                                             )"
		R"( /                                                                                                                                                    )"
		R"(/                                                                                                                                                     )"
		// 012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
	};

	// Variables

};

struct Splash
{
	// Constants
	static const int WIDTH = 60;
	static const int HEIGHT = 13;
	const char* CHARACTERS =
	{
		R"(*                    W E L C O M E  T O                   * )"
		R"(                                              *     *       )"
		R"(    *        LL     UU  UU NN  NN   AA   RRRRR              )"
		R"(             LL     UU  UU NNN NN  A  A  RR  RR             )"
		R"(             LL     UU  UU NN NNN  AAAA  RRRR            *  )"
		R"(             LL      U  U  NN  NN AA  AA RR RR         *    )"
		R"( *           LLLLLL  UUUU  NN  NN AA  AA RR  RR             )"
		R"(            *                                               )"
		R"(         LL       AA   NN  NN  DDDD   EEEEEE RRRRR        * )"
		R"(         LL      A  A  NNN NN  DD DD  EE     RR  RR         )"
		R"(         LL      AAAA  NN NNN  DD  DD EEEEEE RRRR           )"
		R"(  *      LL     AA  AA NN  NN  DD DD  EE     RR RR          )"
		R"(         LLLLLL AA  AA NN  NN  DDDD   EEEEEE RR  RR    *    )"
		// 012345678901234567890123456789012345678901234567890123456789
	};
	// Variables
	float duration = 0.0f;
};

struct Flag
{
	static const int WIDTH = 4;
	static const int HEIGHT = 5;
	const char* CHARACTERS = {
		R"(___ )"
		R"(|M |)"
		R"(|_M|)"
		R"(|   )"
		R"(|__ )"
	};
	const int COLOURS[WIDTH * HEIGHT] = {
		0xC, 0xC, 0xC, 0xC,
		0xF, 0xC, 0xC, 0xC,
		0xF, 0xC, 0xC, 0xC,
		0xF, 0xC, 0xC, 0xC,
		0xF, 0xF, 0xF, 0xF,
	};
};

#endif // GAME_OBJECTS_H