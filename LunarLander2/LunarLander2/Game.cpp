// This classes header
#include "Game.h"

// Includes
#include "Utility.h"
#include "Constants.h"

Game::Game()
{
	// Constructor
}

void Game::Initialise()
{
	// Set the console title
	SetConsoleTitle(L"Welcome to Lunar Lander");

	// Set screen buffer size
	SetConsoleScreenBufferSize(wHnd, bufferSize);

	// Set the window size
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
}

bool Game::Update(float deltaTime)
{
	static bool exit = false;

	switch (currentGameState)
	{
		case SPLASH:
		{
			// Create a new splash screen
			static Splash splash;
			
			// Calculate current splash duration
			splash.duration += deltaTime;

			if (splash.duration < 3.0f)
			{
				// Draw splash image
				WriteImageToBuffer(consoleBuffer, splash.CHARACTERS, nullptr, splash.HEIGHT, splash.WIDTH,
					(SCREEN_WIDTH / 2) - (splash.WIDTH / 2), (SCREEN_HEIGHT / 2) - (splash.HEIGHT / 2));
			}
			else
			{
				// Move to menu state
				splash.duration = 0.0f;
				currentGameState = MENU;
			}

			break;
		}
		case MENU:
		{
			// Clear any previous images
			ClearScreen(consoleBuffer);

			// Print out menu options
			WriteTextToBuffer(consoleBuffer, " ^    1. PLAY           ^",(SCREEN_WIDTH / 2)-14, (SCREEN_HEIGHT / 2) - 3);
			WriteTextToBuffer(consoleBuffer, "/ \\   2. INTRUCTIONS   / \\", (SCREEN_WIDTH / 2)-14, (SCREEN_HEIGHT / 2) - 2);
			WriteTextToBuffer(consoleBuffer, "|M|   3. SCOREBOARD    |M|", (SCREEN_WIDTH / 2)-14, (SCREEN_HEIGHT / 2) - 1);
			WriteTextToBuffer(consoleBuffer, "/-\\   4. QUIT          /-\\", (SCREEN_WIDTH / 2)-14, (SCREEN_HEIGHT / 2));

			if (GetAsyncKeyState(KEY_1))
			{
				currentGameState = PLAY;
			}
			if (GetAsyncKeyState(KEY_2))
			{
				currentGameState = INSTRUCTIONS;
			}
			if (GetAsyncKeyState(KEY_3))
			{
				currentGameState = SCOREBOARD;
			}
			if (GetAsyncKeyState(KEY_4))
			{
					exit = true;
			}

			break;
		}
		case PLAY:
		{
			// To exit game at any point
			if (GetAsyncKeyState(KEY_ESC))
			{
				exit = true;
			}
			
			if (!player.hasLanded && !player.hasCrashed)
			{
				// Creates a time based starting at launch
				// Counting up per frame means it stops when player lands or crashes
				player.stopwatch += STOPWATCH; 
				
				player.score = (100 - (100 - player.fuel) - player.stopwatch);

				// Take key input
				if (GetAsyncKeyState(KEY_ESC))
				{
					exit = true;
				}
				if (GetAsyncKeyState(KEY_W) && player.fuel > 0.0f)
				{
					player.isAccelerating = true;
					player.fuel -= FUEL_CONSUMPTION_RATE;
				}
				if (GetAsyncKeyState(KEY_A))
				{
					--player.xPos;
				}
				if (GetAsyncKeyState(KEY_D))
				{
					++player.xPos;
				}

				// Should we accelerate?
				if (player.isAccelerating)
				{
					player.acceleration += (ACCELERATION_RATE * deltaTime);
				}
				else
				{
					player.acceleration -= (DECELERATION_RATE * deltaTime);
				}

				// Reset acceleration flag
				player.isAccelerating = false;

				// Clamp the acceleration
				player.acceleration = ClampFloat(player.acceleration, 0.0f, 1.5f);

				if (player.acceleration >= 1.0f)
				{
					player.yPos--;
				}
				else if (player.acceleration <= 0.5f)
				{
					player.yPos++;
				}

				// Clamp the input
				player.xPos = ClampInt(player.xPos, 0, (SCREEN_WIDTH - player.WIDTH));
				player.yPos = ClampInt(player.yPos, 0, (SCREEN_HEIGHT - player.HEIGHT));

				// Get the three characters under landing gear (3rd added to prevent lander passing diagonally through mountains)
				char bottomLeftChar = background.CHARACTERS[player.xPos + SCREEN_WIDTH * (player.yPos + (player.HEIGHT - 1))];
				char bottomMidChar = background.CHARACTERS[(player.xPos + (player.WIDTH - 2)) + SCREEN_WIDTH * (player.yPos + (player.HEIGHT - 1))];
				char bottomRightChar = background.CHARACTERS[(player.xPos + (player.WIDTH - 1)) + SCREEN_WIDTH * (player.yPos + (player.HEIGHT - 1))];

				// Has landed?
				if (bottomLeftChar == '_' && bottomRightChar == '_')
				{
					player.hasLanded = true;
				}
				else if (bottomLeftChar != ' ' || bottomMidChar != ' ' || bottomRightChar != ' ')
				{
					player.hasCrashed = true;
				}
			}

			// Clear the previous frame before building the next one
			ClearScreen(consoleBuffer);

			// Draw the background image
			WriteImageToBuffer(consoleBuffer, background.CHARACTERS, nullptr, SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);

			if (player.hasCrashed)
			{
				static float explosionFlashTimer = 0.0f;

				explosionFlashTimer += deltaTime;

				if (explosionFlashTimer >= 0.5f)
				{
					// Draw explosion1
					WriteImageToBuffer(consoleBuffer, explosion.CHARACTERS1, explosion.COLOURS1, explosion.HEIGHT, explosion.WIDTH, player.xPos, player.yPos);
					explosionFlashTimer = 0.0f;
				}
				else
				{
					// Draw explosion2
					WriteImageToBuffer(consoleBuffer, explosion.CHARACTERS2, explosion.COLOURS2, explosion.HEIGHT, explosion.WIDTH, player.xPos, player.yPos);
				}

				WriteTextToBuffer(consoleBuffer, "In space, no one can hear you scream!", ((SCREEN_WIDTH / 2) - 14), SCREEN_HEIGHT / 5);
				WriteTextToBuffer(consoleBuffer, "(Press 'Enter' to continue...)", ((SCREEN_WIDTH / 2) - 14), (SCREEN_HEIGHT / 5) + 1);
				
				// Return to menu state
				if (GetAsyncKeyState(KEY_ENTER))
				{
					player.Reset();
					currentGameState = MENU;
				}
			}
			else if (player.hasLanded)
			{
				// Draw landing flag
				WriteImageToBuffer(consoleBuffer, flag.CHARACTERS, flag.COLOURS, flag.HEIGHT, flag.WIDTH, player.xPos, (player.yPos-1));

				WriteTextToBuffer(consoleBuffer, "You have claimed this planet for all humankind!", ((SCREEN_WIDTH / 2) - 20), SCREEN_HEIGHT / 5);
				WriteTextToBuffer(consoleBuffer, "(Press '3' to see your score or 'Enter' to continue...)", ((SCREEN_WIDTH / 2) - 20), (SCREEN_HEIGHT / 5) + 1);

				// Take input to from player
				if (GetAsyncKeyState(KEY_3))
				{
					currentGameState = SCOREBOARD;
				}
				if (GetAsyncKeyState(KEY_ENTER))
				{
					player.Reset();
					currentGameState = MENU;
				}
			}
			else
			{
				// Draw player image
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS, player.COLOURS, player.HEIGHT, player.WIDTH, player.xPos, player.yPos);
			}
			
			// Draw UI text
			WriteTextToBuffer(consoleBuffer, "SCORE: " + std::to_string(player.score), 1, 0); //100 - (100 - player.fuel) - player.stopwatch), 1, 0); //swap for player.score?
			WriteTextToBuffer(consoleBuffer, "TIME: " + std::to_string(player.stopwatch), 1, 1);  //stopwatch
			WriteTextToBuffer(consoleBuffer, "FUEL: " + std::to_string(player.fuel), 1, 2);

			break;
		}
		case INSTRUCTIONS:
		{
			// Clear any previous images
			ClearScreen(consoleBuffer);

			// Print out instructions
			WriteTextToBuffer(consoleBuffer, "INSTRUCTIONS:", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - 9);
			WriteTextToBuffer(consoleBuffer, "Move left:      'A'", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - 8);
			WriteTextToBuffer(consoleBuffer, "Move right:     'D'", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - 7);
			WriteTextToBuffer(consoleBuffer, "Fire thrusters: 'W'", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - 6);
			WriteTextToBuffer(consoleBuffer, "", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - 5);
			WriteTextToBuffer(consoleBuffer, "Get a higher score by landing as quickly as", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - 4);
			WriteTextToBuffer(consoleBuffer, "possible using the minimum amount of fuel", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - 3);
			WriteTextToBuffer(consoleBuffer, "", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - 2);
			WriteTextToBuffer(consoleBuffer, "Potential landing sites are marked by 'xxx'", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - 1);
			WriteTextToBuffer(consoleBuffer, "", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2));
			WriteTextToBuffer(consoleBuffer, "Good luck, astronaut!", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) + 1);
			WriteTextToBuffer(consoleBuffer, "(Press 'Enter' to continue...)", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) + 2);

			// Return to menu state
			if (GetAsyncKeyState(KEY_ENTER))
			{
				player.Reset();
				currentGameState = MENU;
			}

			break;
		}
		case SCOREBOARD:
		{
			// Clear any previous images
			ClearScreen(consoleBuffer);
			
			// Show players previous score if applicable
			if (player.score == 0)
			{
				WriteTextToBuffer(consoleBuffer, "You haven't successfully landed yet!", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - 3);
				WriteTextToBuffer(consoleBuffer, "", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - 2);
				WriteTextToBuffer(consoleBuffer, "(Press 'Enter' to continue...)", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - 1);;
			}
			else
			{
				WriteTextToBuffer(consoleBuffer, "Congratulations your score was: " + std::to_string(player.score), (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - 3);
				WriteTextToBuffer(consoleBuffer, "Have another try to see if you can improve", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - 2);
				WriteTextToBuffer(consoleBuffer, "(Press 'Enter' to continue...)", (SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - 1);
			}
			
			// Return to menu state
			if (GetAsyncKeyState(KEY_ENTER))
			{
				player.Reset();
				currentGameState = MENU;
			}

			break;
		}
	}

	return exit;
}

void Game::Draw()
{
	// Draw player position on the console
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}