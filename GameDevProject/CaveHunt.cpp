// CaveHunt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Game.h"

#undef main

//game object to control the game
Game* game = nullptr;

int main(int argc, const char* args[])
{
	//Frame control variables
	Uint32 frameStart;
	int frameTime;

	//Game object initialization
	game = new Game();
	game->init("Cave Hunt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Core game loop
	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}