#pragma once
#include "Layer.h"
#include "Constants.h"

//parallax background is created via this class
class BackGround
{
public:
	BackGround(SDL_Renderer* renderer)
	{
		//initializing all background layers
		layers[0] = new Layer(renderer, SKY, l5MoveSpeed);
		layers[1] = new Layer(renderer, DOWNLAYER, l4MoveSpeed);
		layers[2] = new Layer(renderer, MIDDLELAYER, l3MoveSpeed);
		layers[3] = new Layer(renderer, LIGHT, l2MoveSpeed);
		layers[4] = new Layer(renderer, TOPLAYER, l1MoveSpeed);
	}

	~BackGround()
	{
		//deleting layers
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
	//background consists of 5 layers
	Layer* layers[5];
};