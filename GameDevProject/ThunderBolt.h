#pragma once
#include<iostream>
#include <stdlib.h> 
#include "Projectile.h"

using namespace std;

class ThunderBolt : public Projectile
{
public:
	ThunderBolt(SDL_Renderer* renderer, const char* tex, int x, int y, int w, int h, float angle, string tag, bool hasAnim, int damage, int direction, float scale, bool isHostile, int health) : Projectile(renderer, tex, x, y, w, h, angle, tag, hasAnim, damage, direction, scale, isHostile, health)
	{

	}
	void Update(SDL_Renderer* renderer) override
	{
		Projectile::Update(renderer);
		if (position.y <= PLATFORM_HEIGHT - srcRect.w && position.y >= 0)
		{
			position.y += speed;
		}
		else
			Destroy();
	}
};
