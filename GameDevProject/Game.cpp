#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <iostream>
#include <fstream>
#include "Constants.h"
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
}

Game::~Game()
{

}

/*
void Game::writeToFile()
{
	if (gameObjects.size() > 0)
	{
		ofstream file("data.txt");
		file << frameCount << "\n";
		file << bossWarning ? 1 : 0;
		file << "\n";
		file << bossArrived ? 1 : 0;
		file << "\n";
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->writeToFile(file);
		}
		file << "END";
	}
}
bool Game::is_empty(ifstream& file)
{
	return file.peek() == ifstream::traits_type::eof();
}
bool Game::readFromFile()
{
	ifstream file("data.txt");
	if (!is_empty(file))
	{
		file >> frameCount;
		int temp;
		file >> temp;
		temp == 1 ? bossWarning = true : bossWarning = false;
		file >> temp;
		temp == 1 ? bossArrived = true : bossArrived = false;
		string dataType;
		do
		{
			file >> dataType;
			if (strcmp(dataType.c_str(), "[Player]") == 0) { player = Player::readPlayer(file); gameObjects.push_back(player);}
			else if (strcmp(dataType.c_str(), "[Boss]") == 0)	gameObjects.push_back(Boss::readBoss(file));
			else if (strcmp(dataType.c_str(), "[Bullet]") == 0)	gameObjects.push_back(Bullet::readBullet(file));
			else if (strcmp(dataType.c_str(), "[Explosion]") == 0)	gameObjects.push_back(Explosion::readExplosion(file));
			else if (strcmp(dataType.c_str(), "[Nimble]") == 0)	gameObjects.push_back(Nimble::readNimble(file));
			else if (strcmp(dataType.c_str(), "[Ranger]") == 0)	gameObjects.push_back(Ranger::readRanger(file));
			else if (strcmp(dataType.c_str(), "[Smoke]") == 0)	gameObjects.push_back(Smoke::readSmoke(file));
		} while (strcmp(dataType.c_str(), "END") != 0);
		return true;
	}
	return false;
}
*/

struct MenuItem
{
	const char* label;
	SDL_Rect pos;
	SDL_Texture* texture;
	bool isSelected = false;
	SDL_Color color = { 0,0,0 };
	int rows;
	int cols;
};

int Game::showMenu(TTF_Font* font)
{
	Mix_PlayMusic(menuMusic, -1);

	const Uint32 frameDelay = 60;
	Uint32 startTime, frameTime;
	int x, y; //cursor position
	const int NUMMENU = 2;
	MenuItem menuItems[NUMMENU];
	menuItems[0].label = "Play";
	menuItems[1].label = "Exit";

	SDL_Surface* tempSurface = NULL;
	const SDL_Color colors[2] = { {0,0,0}, {0,255,0} };

	for (int i = 0; i < NUMMENU; i++)
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

	SDL_Texture* buttonEdge = TextureManager::LoadTexture(renderer, "assets/Button Edge.png")->tex;
	SDL_Texture* buttonCorner = TextureManager::LoadTexture(renderer, "assets/Button Corner.png")->tex;
	SDL_Texture* buttonMiddle = TextureManager::LoadTexture(renderer, "assets/Button Middle.png")->tex;
	SDL_Event event;
	while (1)
	{
		startTime = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				for (int i = 0; i < NUMMENU; i++)
				{
					SDL_DestroyTexture(menuItems[i].texture);
				}
				SDL_DestroyTexture(buttonEdge);
				SDL_DestroyTexture(buttonCorner);
				SDL_DestroyTexture(buttonMiddle);
				Mix_HaltMusic();
				return 1;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				for (int i = 0; i < NUMMENU; i++)
				{
					if (x >= menuItems[i].pos.x && x <= menuItems[i].pos.x + (32 * menuItems[i].cols) && y >= menuItems[i].pos.y && y <= menuItems[i].pos.y + (32 * menuItems[i].rows))
					{
						if (!menuItems[i].isSelected)
						{
							menuItems[i].isSelected = true;
							menuItems[i].color = colors[1];
							tempSurface = TTF_RenderText_Solid(font, menuItems[i].label, menuItems[i].color);
							SDL_DestroyTexture(menuItems[i].texture);
							menuItems[i].texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
							SDL_FreeSurface(tempSurface);
						}
					}
					else
					{
						if (menuItems[i].isSelected)
						{
							menuItems[i].isSelected = false;
							menuItems[i].color = colors[0];
							tempSurface = TTF_RenderText_Solid(font, menuItems[i].label, menuItems[i].color);
							SDL_DestroyTexture(menuItems[i].texture);
							menuItems[i].texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
							SDL_FreeSurface(tempSurface);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				for (int i = 0; i < NUMMENU; i++)
					if (x >= menuItems[i].pos.x && x <= menuItems[i].pos.x + (32 * menuItems[i].cols) && y >= menuItems[i].pos.y && y <= menuItems[i].pos.y + (32 * menuItems[i].rows))
					{
						Mix_PlayChannel(-1, buttonSound, 0);
						for (int i = 0; i < NUMMENU; i++)
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
					for (int i = 0; i < NUMMENU; i++)
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

		for (int i = 0; i < NUMMENU; i++)
		{
			for (int j = 0; j < menuItems[i].rows; j++)
			{
				for (int k = 0; k < menuItems[i].cols; k++)
				{
					SDL_Rect dest;
					if (j == 0 && k == 0)
					{
						dest.x = menuItems[i].pos.x;
						dest.y = menuItems[i].pos.y;
						dest.w = 32;
						dest.h = 32;
						SDL_RenderCopyEx(renderer, buttonCorner, NULL, &dest, 180.0f, NULL, SDL_FLIP_NONE);
					}
					else if (j == menuItems[i].rows - 1 && k == menuItems[i].cols - 1)
					{
						dest.x = menuItems[i].pos.x + 32 * j;
						dest.y = menuItems[i].pos.y + 32 * k;
						dest.w = 32;
						dest.h = 32;
						SDL_RenderCopyEx(renderer, buttonCorner, NULL, &dest, 0.0f, NULL, SDL_FLIP_NONE);
					}
					else if (j == menuItems[i].rows - 1 && k == 0)
					{
						dest.x = menuItems[i].pos.x;
						dest.y = menuItems[i].pos.y + 32 * j;
						dest.w = 32;
						dest.h = 32;
						SDL_RenderCopyEx(renderer, buttonCorner, NULL, &dest, 90.0f, NULL, SDL_FLIP_NONE);
					}
					else if (j == 0 && k == menuItems[i].cols - 1)
					{
						dest.x = menuItems[i].pos.x + 32 * k;
						dest.y = menuItems[i].pos.y;
						dest.w = 32;
						dest.h = 32;
						SDL_RenderCopyEx(renderer, buttonCorner, NULL, &dest, -90.0f, NULL, SDL_FLIP_NONE);
					}
					else if (j == 0 && k != 0 && k != menuItems[i].cols - 1)
					{
						dest.x = menuItems[i].pos.x + 32 * k;
						dest.y = menuItems[i].pos.y;
						dest.w = 32;
						dest.h = 32;
						SDL_RenderCopyEx(renderer, buttonEdge, NULL, &dest, 180.0f, NULL, SDL_FLIP_NONE);
					}
					else if (j == menuItems[i].rows - 1 && k != 0 && k != menuItems[i].cols - 1)
					{
						dest.x = menuItems[i].pos.x + 32 * k;
						dest.y = menuItems[i].pos.y + 32 * j;
						dest.w = 32;
						dest.h = 32;
						SDL_RenderCopyEx(renderer, buttonEdge, NULL, &dest, 0.0f, NULL, SDL_FLIP_NONE);
					}
					else if (j != 0 && j != menuItems[i].rows - 1 && k == 0)
					{
						dest.x = menuItems[i].pos.x;
						dest.y = menuItems[i].pos.y + 32 * j;
						dest.w = 32;
						dest.h = 32;
						SDL_RenderCopyEx(renderer, buttonEdge, NULL, &dest, 90.0f, NULL, SDL_FLIP_NONE);
					}
					else if (j != 0 && j != menuItems[i].rows - 1 && k == menuItems[i].cols - 1)
					{
						dest.x = menuItems[i].pos.x + 32 * k;
						dest.y = menuItems[i].pos.y + 32 * j;
						dest.w = 32;
						dest.h = 32;
						SDL_RenderCopyEx(renderer, buttonEdge, NULL, &dest, -90.0f, NULL, SDL_FLIP_NONE);
					}
					else
					{
						dest.x = menuItems[i].pos.x + 32 * k;
						dest.y = menuItems[i].pos.y + 32 * j;
						dest.w = 32;
						dest.h = 32;
						SDL_RenderCopyEx(renderer, buttonMiddle, NULL, &dest, 0.0f, NULL, SDL_FLIP_NONE);
					}

				}
			}

			SDL_Rect menuItemDest = menuItems[i].pos;

			menuItemDest.x += (menuItems[i].rows * 32 - menuItems[i].pos.w) / 2;
			menuItemDest.y += (menuItems[i].cols * 32 - menuItems[i].pos.h) / 2;
			SDL_RenderCopy(renderer, menuItems[i].texture, NULL, &menuItemDest);
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

/*
void Game::generateExplosion(Vector2D& pos)
{
	Mix_PlayChannel(-1, explosionSound, 0);
	for (int i = 0 ; i < 100 ; i++)
	{
		int speed = rand() % 5 + 1;
		int angle = rand() % 360;
		int scale = 1 / ((rand() % 5)+1);
		int life = (rand() % 60) + 1;
		gameObjects.push_back(new Explosion("assets/explosion.png", pos.x + 32, pos.y + 32, 16, 16, scale, 16, angle, speed, life));
	}
}*/

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
	font = TTF_OpenFont("assets/times new roman.ttf", 28);
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	if (success)
	{

		//if (!readFromFile())
		//{

		menuMusic = Mix_LoadMUS("sounds/Menu.mp3");
		buttonSound = Mix_LoadWAV("sounds/Button.wav");

		userChoice = showMenu(font);

		gameMusic = Mix_LoadMUS("sounds/Game.mp3");

		if (userChoice == 1) isRunning = false;
		else
		{
			isRunning = true;
			Mix_PlayMusic(gameMusic, -1);
			bg = new BackGround(renderer);
			player = new Player(renderer, "assets/player", 100, PLATFORM_HEIGHT - playerSpriteOffsetY - playerSpriteH, 231, 190, 0.0f, "Player", true, 1);
			gameObjects.push_back(player);
		}
		//}
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
			//player->setFlip(SDL_FLIP_NONE);
			break;
		case SDLK_d:
			player->setState(IDLE);
			player->Translate(0, 0);
			break;
		case SDLK_SPACE:
			//player->setState(IDLE);
			break;
		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			if (!player->isJumping && player->state != DEATH) { player->Translate(player->velocity.x, jumpVel); player->isJumping = true; };
			break;
		case SDLK_s:
			//((Player*)player)->Translate(0.0f, 6);
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
		case SDLK_b:
			//if (!((Player*)player)->OnCoolDown() && ((Player*)player)->hasMissile()) gameObjects.push_back(((Player*)player)->Shoot(true));
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
	if (warningTimer > -2) warningTimer--;
	if (warningTimer == -1) 
	{
		SDL_DestroyTexture(warntexture);

		gameObjects.push_back(new Boss(renderer, "assets/monsters/boss", SCREEN_WIDTH - 100, PLATFORM_HEIGHT - ((bossSpriteOffsetY + bossSpriteH) * 1.5), 160, 128, 0, "Boss", true, 380, 1.5));

		bossArrived = true;
	} 
	if (bossWarning && !bossArrived && warningTimer == -2)
	{
		warningTimer = bossWarningTimer;
		SDL_Surface* warnSurface = TTF_RenderText_Solid(font, "!!!!!", { 255, 0, 0 });
		warntexture = SDL_CreateTextureFromSurface(renderer, warnSurface);
		warnPos.w = warnSurface->w;
		warnPos.h = warnSurface->h;
		SDL_FreeSurface(warnSurface);
		warnPos.x = SCREEN_WIDTH / 2 - warnPos.w / 2;
		warnPos.y = SCREEN_HEIGHT / 2 - warnPos.h / 2;
	}

	if (((Player*)player)->score < BOSS_ARRIVAL_SCORE)
	{
		if (frameCount % 300 == 0)
		{
			int random = rand() % 3;
			if (random == 1)
			{
				gameObjects.push_back(new Mushroom(renderer, "assets/monsters/mushroom", SCREEN_WIDTH - 100, PLATFORM_HEIGHT - ((monsterSpriteOffsetY + monsterSpriteH) * 1.5), 150, 150, 0, "Enemy", true, 200, 1.5));
			}
			else if(random == 0)
			{
				gameObjects.push_back(new DarkWiz(renderer, "assets/monsters/darkWiz", SCREEN_WIDTH - 100, PLATFORM_HEIGHT - ((darkWizSpriteOffsetY + darkWizSpriteH) * 1.5), 250, 250, 0, "Enemy", true, 300, 1.5));
			}
			else if (random == 2)
			{
				gameObjects.push_back(new Goblin(renderer, "assets/monsters/goblin", SCREEN_WIDTH - 100, PLATFORM_HEIGHT - ((monsterSpriteOffsetY + monsterSpriteH) * 1.5), 150, 150, 0, "Enemy", true, 100, 1.5, 5));
			}
		}
	}
	else
	{
		if (!bossArrived)
		{
			for (int i = 1; i < gameObjects.size(); i++)
			{
				if (gameObjects.at(i)->Alive()) gameObjects.at(i)->Destroy();
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
					for (int i = 0; i < gameObjects.size(); i++)
					{
						if (gameObjects.at(i)->Alive()) gameObjects.at(i)->Destroy();
					}
					isRunning = true;
					player = new Player(renderer, "assets/player", 100, PLATFORM_HEIGHT - playerSpriteOffsetY - playerSpriteH, 231, 190, 0.0f, "Player", true, 1);
					gameObjects.push_back(player);
					bossWarning = false;
					bossArrived = false;
					frameCount = 0;
					Mix_PlayMusic(gameMusic, -1);
					continue;
				}
				else isRunning = false;
			}
			else if (i == 0) isRunning = false;
			delete gameObjects.at(i);
			gameObjects[i] = NULL;
			gameObjects.erase(gameObjects.begin() + i);
		}
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	bg->Render(renderer);

	if (warningTimer > 0)
	{
		SDL_RenderCopy(renderer, warntexture, NULL, &warnPos);
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
	TTF_CloseFont(font);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
