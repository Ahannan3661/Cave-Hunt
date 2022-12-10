#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <vector>
#include "GameObject.h"
#include "Vector2D.h"
#include <SDL_ttf.h>
#include <string>
#include <SDL_mixer.h>
#include <iostream>
#include <fstream>
#include "BackGround.h"

class GameObject;

using namespace std;

class Game
{
public:
	Game();
	~Game();

	void init(const char*, int, int, int, int);
	void update();
	void render();
	void clean();
	void handleEvents();

	bool running() { return isRunning; }

	static bool checkCollission(GameObject*, GameObject*);
	int showMenu(TTF_Font*);
	static SDL_Event event;
	static vector<GameObject*> gameObjects;
	static bool skeletonKilled;

private:
	SDL_Texture* warntexture = nullptr;
	SDL_Rect warnPos;
	int warningTimer = -2;
	BackGround* bg = nullptr;
	bool bossArrived = false;
	bool bossWarning = false;
	SDL_Renderer* renderer = nullptr;
	Mix_Music* menuMusic = NULL;
	Mix_Music* gameMusic = NULL;
	Mix_Chunk* buttonSound = NULL;
	int userChoice = -1;
	Uint32 frameCount = 0;
	bool isRunning;
	SDL_Window* window = NULL;
	TTF_Font* font = NULL;
};