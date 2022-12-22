#include "Game.h"
#include "TextureManager.h"
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Mushroom.h"
#include "Goblin.h"
#include "DarkWiz.h"
#include "Boss.h"

SDL_Event Game::event;
bool Game::skeletonKilled;
vector<GameObject*> Game::gameObjects;
GameObject* player;

Game::Game()
{
	isRunning = true;
	window = nullptr;
	scoreDest.x = warnPos.x = 0;
	scoreDest.y = warnPos.y = 0;
	scoreDest.w = warnPos.w = 0;
	scoreDest.h = warnPos.h = 0;
}

Game::~Game()
{

}

//draws menu onto the screen
int Game::showMenu(TTF_Font* font)
{
	Mix_PlayMusic(menuMusic, -1);

	const Uint32 frameDelay = FPS;
	Uint32 startTime, frameTime;

	//to save cursor position coordinates
	int x, y; 
	
	//array that contains all the items of our menu
	MenuItem menuItems[2];
	menuItems[0].label = "Play";
	menuItems[1].label = "Exit";

	SDL_Surface* tempSurface = NULL;

	//initializing menuItems array
	for (int i = 0; i < 2; i++)
	{
		tempSurface = TTF_RenderText_Solid(font, menuItems[i].label, menuItems[i].color);
		menuItems[i].texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		menuItems[i].pos.w = tempSurface->w;
		menuItems[i].pos.h = tempSurface->h;
		menuItems[i].pos.x = SCREEN_WIDTH / 2 - menuItems[i].pos.w / 2;
		menuItems[i].pos.y = SCREEN_HEIGHT / 2 + (menuItems[i].pos.h * i * 4);
		menuItems[i].rows = (menuItems[i].pos.h / 32) + 2;
		menuItems[i].cols = (menuItems[i].pos.w / 32) + 2;
		SDL_FreeSurface(tempSurface);
	}

	//3 textures that are used to create buttons
	SDL_Texture* buttonEdge = TextureManager::LoadTexture(renderer, BUTTONEDGE)->tex;
	SDL_Texture* buttonCorner = TextureManager::LoadTexture(renderer, BUTTONCORNER)->tex;
	SDL_Texture* buttonMiddle = TextureManager::LoadTexture(renderer, BUTTONMIDDLE)->tex;

	SDL_Event event;
	while (1)
	{
		startTime = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				for (int i = 0; i < 2; i++)
				{
					SDL_DestroyTexture(menuItems[i].texture);
				}
				SDL_DestroyTexture(buttonEdge);
				SDL_DestroyTexture(buttonCorner);
				SDL_DestroyTexture(buttonMiddle);
				Mix_HaltMusic();
				return 1;

			//track cursor to highlight button when cursor is on it
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				for (int i = 0; i < 2; i++)
				{
					if (x >= menuItems[i].pos.x && x <= menuItems[i].pos.x + (32 * menuItems[i].cols) && y >= menuItems[i].pos.y && y <= menuItems[i].pos.y + (32 * menuItems[i].rows))
					{
						if (!menuItems[i].isHighlighted)
							menuItems[i].HighLight(renderer, true, font);
					}
					else
						if (menuItems[i].isHighlighted)
							menuItems[i].HighLight(renderer, false, font);
				}
				break;
			//return the value corresponding the button that was pressed
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				for (int i = 0; i < 2; i++)
					if (x >= menuItems[i].pos.x && x <= menuItems[i].pos.x + (32 * menuItems[i].cols) && y >= menuItems[i].pos.y && y <= menuItems[i].pos.y + (32 * menuItems[i].rows))
					{
						Mix_PlayChannel(-1, buttonSound, 0);
						for (int i = 0; i < 2; i++)
						{
							SDL_DestroyTexture(menuItems[i].texture);
						}
						Mix_HaltMusic();
						SDL_DestroyTexture(buttonEdge);
						SDL_DestroyTexture(buttonCorner);
						SDL_DestroyTexture(buttonMiddle);
						return i;
					}
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					for (int i = 0; i < 2; i++)
					{
						SDL_DestroyTexture(menuItems[i].texture);
					}
					SDL_DestroyTexture(buttonEdge);
					SDL_DestroyTexture(buttonCorner);
					SDL_DestroyTexture(buttonMiddle);
					Mix_HaltMusic();
					return 1;
				}
			}
		}
		SDL_RenderClear(renderer);

		bg->Render(renderer);

		for (int i = 0; i < 2; i++)
		{
			menuItems[i].DrawMenuItem(renderer, buttonCorner, buttonEdge, buttonMiddle);
		}

		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks() - startTime;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
}

bool Game::checkCollission(GameObject* obj1, GameObject* obj2)
{
	if (obj1->collissionBox.x + obj1->collissionBox.w >= obj2->collissionBox.x &&
		obj1->collissionBox.x <= obj2->collissionBox.x + obj2->collissionBox.w &&
		obj1->collissionBox.y + obj1->collissionBox.h >= obj2->collissionBox.y &&
		obj1->collissionBox.y <= obj2->collissionBox.y + obj2->collissionBox.h)
		return true;
	return false;
}

void Game::init(const char* title, int xpos, int ypos, int width, int height)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}
	font = TTF_OpenFont(FONT, FONT_SIZE);
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	if (success)
	{
		menuMusic = Mix_LoadMUS(MENUMUSIC);
		buttonSound = Mix_LoadWAV(BUTTONSOUND);

		bg = new BackGround(renderer);

		userChoice = showMenu(font);

		gameMusic = Mix_LoadMUS(GAMEMUSIC);

		if (userChoice == 1) isRunning = false;
		else
		{
			isRunning = true;
			Mix_PlayMusic(gameMusic, -1);
			player = new Player(renderer, PLAYER, PLAYER_SPAWNX, PLAYER_SPAWNY, playerSourceW, playerSourceH, 0.0f, "Player", true, playerScale, playerHealth);
			gameObjects.push_back(player);
			skullTexture = TextureManager::LoadTexture(renderer, SKULL);
			bossArrivalSound = Mix_LoadWAV(BOSSARRIVALSOUND);
			playerJumpSound = Mix_LoadWAV(PLAYERJUMPSOUND);
		}
	}
	else isRunning = false;
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
			player->setState(IDLE);
			player->Translate(0, 0);
			break;
		case SDLK_d:
			player->setState(IDLE);
			player->Translate(0, 0);
			break;
		case SDLK_SPACE:
			break;
		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			if (!player->isJumping && player->state != DEATH) { player->Translate(player->velocity.x, jumpVel); player->isJumping = true; Mix_PlayChannel(-1, playerJumpSound, 0);}
			break;
		case SDLK_a:
			if (player->state != DEATH)
			{
				player->setState(RUNNING);
				player->Translate(-player->speed, 0);
				player->setFlip(SDL_FLIP_HORIZONTAL);
			}
			break;
		case SDLK_d:
			if (player->state != DEATH)
			{
				player->setState(RUNNING);
				player->Translate(player->speed, 0);
				player->setFlip(SDL_FLIP_NONE);
				bg->Update();
			}
			break;
		case SDLK_SPACE:
			player->Translate(0, 0);
			if (!((Player*)player)->OnCoolDown() && player->state != ATTACKING) { player->setState(ATTACKING); }
			break;
		default:
			break;
		}
	default:
		break;
	}
}

void Game::update()
{
	frameCount++;

	scoreSurface = TTF_RenderText_Solid(font, to_string(((Player*)gameObjects.at(0))->score).c_str(), { 0,0,0 });
	scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
	scoreDest.w = scoreSurface->clip_rect.w;
	scoreDest.h = scoreSurface->clip_rect.h;
	scoreDest.x = SCREEN_WIDTH - scoreDest.w;
	scoreDest.y = 0;
	SDL_FreeSurface(scoreSurface);
	scoreSurface = nullptr;

	if (warningTimer > -2) warningTimer--;
	if (warningTimer == -1) 
	{
		SDL_DestroyTexture(warnTexture);

		gameObjects.push_back(new Boss(renderer, BOSS, MONSTER_SPAWNX, BOSS_SPAWNY, bossSourceW, bossSourceH, 0.0f, "Boss", true, bossAttackRange, monsterScale ,bossHealth));

		bossArrived = true;
	} 
	if (bossWarning && !bossArrived && warningTimer == -2)
	{
		warningTimer = bossWarningTimer;
		SDL_Surface* warnSurface = TTF_RenderText_Solid(font, "!!!!!", { 255, 0, 0 });
		warnTexture = SDL_CreateTextureFromSurface(renderer, warnSurface);
		warnPos.w = warnSurface->w;
		warnPos.h = warnSurface->h;
		SDL_FreeSurface(warnSurface);
		warnPos.x = SCREEN_WIDTH / 2 - warnPos.w / 2;
		warnPos.y = SCREEN_HEIGHT / 2 - warnPos.h / 2;
		Mix_PlayChannel(-1, bossArrivalSound, 0);
	}

	if (((Player*)player)->score < BOSS_ARRIVAL_SCORE)
	{
		if (frameCount % 300 == 0)
		{
			int random = rand() % 3;
			if (random == 1)
			{
				gameObjects.push_back(new Mushroom(renderer, MUSHROOM, MONSTER_SPAWNX, MONSTER_SPAWNY, monsterSourceW, monsterSourceH, 0.0f, "Enemy", true, mushroomAttackRange, monsterScale, monsterHealth));
			}
			else if(random == 0)
			{
				gameObjects.push_back(new DarkWiz(renderer, GOBLIN, MONSTER_SPAWNX, DARKWIZ_SPAWNY, darkWizSourceW, darkWizSourceH, 0.0f, "Enemy", true, darWizAttackRange, monsterScale, monsterHealth));
			}
			else if (random == 2)
			{
				gameObjects.push_back(new Goblin(renderer, DARKWIZ, MONSTER_SPAWNX, MONSTER_SPAWNY, monsterSourceW, monsterSourceH, 0.0f, "Enemy", true, goblinAttackRange, monsterScale, meeleMonsterDamage, monsterHealth));
			}
		}
	}
	else
	{
		if (!bossArrived)
		{
			for (int i = 1; i < gameObjects.size(); i++)
			{
					delete gameObjects.at(i);
					gameObjects[i] = nullptr;
					gameObjects.erase(gameObjects.begin() + i);
					i--;
			}
		}
		bossWarning = true;
	}

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects.at(i)->Update(renderer);
	}

	for (int i = 0; i < gameObjects.size(); i++)
	{
		GameObject* obj = gameObjects.at(i);
		if (obj->Alive() == false)
		{
			if (obj->hasTag("Enemy")) ((Player*)player)->score++;
			if (obj->hasTag("Boss"))
			{
				Mix_HaltMusic();
				userChoice = showMenu(font);
				if (userChoice == 0)
				{
					for (int j = 0; j < gameObjects.size(); j++)
					{
						delete gameObjects.at(j);
						//gameObjects[j] = nullptr;
						gameObjects.erase(gameObjects.begin() + j);
						j--;
					}
					SDL_DestroyTexture(scoreTexture);
					scoreTexture = nullptr;
					isRunning = true;
					player = new Player(renderer, PLAYER, PLAYER_SPAWNX, PLAYER_SPAWNY, playerSourceW, playerSourceH, 0.0f, "Player", true, playerScale, playerHealth);
					gameObjects.push_back(player);
					bossWarning = false;
					bossArrived = false;
					frameCount = 0;
					Mix_PlayMusic(gameMusic, -1);
					break;
				}
				else isRunning = false;
			}
			if (i == 0) isRunning = false;
			delete gameObjects.at(i);
			//gameObjects[i] = nullptr;
			gameObjects.erase(gameObjects.begin() + i);
			i--;
		}
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	bg->Render(renderer);

	SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreDest);
	scoreDest.x -= skullTexture->srcRect.w;
	scoreDest.w = skullTexture->srcRect.w;
	SDL_RenderCopy(renderer, skullTexture->tex, NULL, &scoreDest);

	if (warningTimer > 0)
	{
		SDL_RenderCopy(renderer, warnTexture, NULL, &warnPos);
	}

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects.at(i)->Render(renderer);
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects.at(i);
		gameObjects.erase(gameObjects.begin() + i);
	}
	Mix_FreeMusic(menuMusic);
	menuMusic = NULL;
	Mix_FreeMusic(gameMusic);
	gameMusic = NULL;
	Mix_FreeChunk(buttonSound);
	buttonSound = NULL;
	Mix_FreeChunk(bossArrivalSound);
	bossArrivalSound = NULL;
	Mix_FreeChunk(playerJumpSound);
	playerJumpSound = NULL;
	TTF_CloseFont(font);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
