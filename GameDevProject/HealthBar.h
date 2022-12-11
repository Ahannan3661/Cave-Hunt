#pragma once
#include<iostream>
#include <stdlib.h> 
#include "TextureManager.h"
#include "Constants.h"

using namespace std;

class HealthBar
{
private:
	texStruct* healthFill;
	texStruct* healthBar;
	SDL_Rect fillDest;
	SDL_Rect barDest;
public:

	HealthBar(SDL_Renderer* renderer, const char* path, int x, int y, int objectHealth)
	{
		barDest.x = x;
		barDest.y = y;
		healthBar = TextureManager::LoadTexture(renderer, HEALTHBAR);
		healthFill = TextureManager::LoadTexture(renderer, HEALTHFILL);
		fillDest.x = x + (objectHealth * barToFillRatio);
		fillDest.y = y;
		barDest.w =  objectHealth + (objectHealth * barToFillRatio);
		fillDest.w = objectHealth;
		fillDest.h = healthFill->srcRect.h;
		barDest.h = healthBar->srcRect.h;
	}
	~HealthBar()
	{
		SDL_DestroyTexture(healthFill->tex);
		delete healthFill;
		healthFill = nullptr;
	}
	void Update(int x, int y)
	{
		barDest.x = x;
		barDest.y = y;
		fillDest.x = x + (fillDest.w * barToFillRatio);
		fillDest.y = y;
	}
	void Render(SDL_Renderer* renderer)
	{
		TextureManager::Draw(renderer, healthBar->tex, healthBar->srcRect, barDest, 0.0f, SDL_FLIP_NONE);
		TextureManager::Draw(renderer, healthFill->tex, healthFill->srcRect, fillDest, 0.0f, SDL_FLIP_NONE);
	}
	void shrinkBar(int val)
	{
		fillDest.w -= val;
		if (fillDest.w < 0) fillDest.w = 0;
	}
};
