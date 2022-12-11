#pragma once
#include<iostream>
#include <stdlib.h> 
#include "Projectile.h"

using namespace std;

class StraightProjectile : public Projectile
{
public:
	StraightProjectile(SDL_Renderer* renderer, const char* tex, int x, int y, int w, int h, float angle, string tag, bool hasAnim, int damage, int direction, float scale, bool isHostile, int health) : Projectile(renderer, tex, x, y, w, h, angle, tag, hasAnim, damage, direction, scale, isHostile, health)
	{

	}
	void Update(SDL_Renderer* renderer) override
	{
		Projectile::Update(renderer);
		if (speed < 0) setFlip(SDL_FLIP_HORIZONTAL);
		if (speed > 0) setFlip(SDL_FLIP_NONE);
		if (position.x <= SCREEN_WIDTH && position.x >= 0)
		{
			position.x += speed;
		}
		else
			Destroy();
	}
};
