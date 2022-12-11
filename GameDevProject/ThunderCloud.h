#pragma once
#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class ThunderCloud : public GameObject
{
public:

	ThunderCloud(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, float scale, int health) : GameObject(renderer, path, x, y, w, h, angle, tag, hasAnimations, scale, health)
	{

	}

	void Update(SDL_Renderer* renderer) override
	{
		GameObject::Update(renderer);
		if (state != DEATH)
		{
			if (Game::gameObjects[0]->collissionBox.x > position.x) position.x += speed;
			if (Game::gameObjects[0]->collissionBox.x < position.x) position.x -= speed;

			UpdateDestRect();
			UpdateCollissionBox();
		}
	}
};
