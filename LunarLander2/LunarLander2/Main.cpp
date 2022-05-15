// Includes
#include <Windows.h>
#include <chrono>
#include "GameObjects.h"
#include "Game.h"

// Typedefs
typedef std::chrono::steady_clock::time_point Time;
typedef std::chrono::high_resolution_clock HiResClock;
typedef std::chrono::duration<float> TimeDiff;

int main()
{
	Game gameInstance;
	
	// Initialise console window
	gameInstance.Initialise();

	// Initialise variables
	float deltaTime = 0.0f;
	Time currentFrameTime = HiResClock::now();
	Time previousFrameTime = HiResClock::now();
	
	// Main game loop
	bool exitGame = false;
	while (!exitGame)
	{
		// Calculate delta time since last frame
		currentFrameTime = HiResClock::now();
		TimeDiff diff = currentFrameTime - previousFrameTime;
		deltaTime = diff.count();

		if (deltaTime >= (1.0f / FRAME_RATE))
		{
			// Update the application
			exitGame = gameInstance.Update(deltaTime);

			// Cache the timestamp of this frame
			previousFrameTime = currentFrameTime;
		}

		gameInstance.Draw();
	}

	return 0;
}