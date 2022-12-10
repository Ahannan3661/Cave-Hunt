#pragma once
#include "Vector2D.h"
#include <iostream>
#include "TextureManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Layer.h"
#include "Constants.h"

class BackGround
{
public:
	BackGround(SDL_Renderer* renderer)
	{
		layers[0] = new Layer(renderer, "assets/BackGround/sky.png", 0);
		layers[1] = new Layer(renderer, "assets/BackGround/downLayer.png", 3);
		layers[2] = new Layer(renderer, "assets/BackGround/middleLayer.png", 5);
		layers[3] = new Layer(renderer, "assets/BackGround/light.png", 9);
		layers[4] = new Layer(renderer, "assets/BackGround/topLayer.png", 13);
	}

	~BackGround()
	{
		for (int i = 0; i < 5; i++)
		{
			delete layers[i];
			layers[i] = nullptr;
		}
	}

	void Update()
	{
		for (int i = 0; i < 5; i++)
		{
			layers[i]->Update();
		}
	}

	void Render(SDL_Renderer* renderer)
	{
		for (int i = 0; i < 5; i++)
		{
			layers[i]->Render(renderer);
		}
	}
private:
	Layer* layers[5];
};