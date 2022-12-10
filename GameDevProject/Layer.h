#pragma once
#include "SDL.h"
#include "TextureManager.h"

class Layer
{
private:
	SDL_Texture* texture;
	SDL_Rect destRect1;
	SDL_Rect destRect2;
	int moveSpeed;
public:
	Layer(SDL_Renderer* renderer, const char* path, int moveSpeed)
	{
		texStruct* temp = TextureManager::LoadTexture(renderer, path);
		texture = temp->tex;
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		destRect1.w = destRect2.w = temp->srcRect.w;
		destRect1.h = destRect2.h = temp->srcRect.h;
		destRect1.x = 0;
		destRect1.y = destRect2.y =  0;
		destRect2.x = temp->srcRect.w;
		this->moveSpeed = moveSpeed;
	}
	~Layer()
	{
		SDL_DestroyTexture(texture);
	}

	void Update()
	{
		destRect1.x -= moveSpeed;
		destRect2.x -= moveSpeed;
		if (destRect1.x <= -destRect1.w) 
		{
			destRect1.x = 0; destRect2.x = destRect2.w;
		}
	}

	void Render(SDL_Renderer* renderer)
	{
		TextureManager::DrawBG(renderer, texture, destRect1);
		TextureManager::DrawBG(renderer, texture, destRect2);
	}
};