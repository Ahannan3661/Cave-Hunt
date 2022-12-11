#pragma once
#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class Projectile : public GameObject
{
private:
	Uint32 spriteStart = totalSpellSpriteTime;
	int damage;
public:
	bool isHostile;
	Projectile(SDL_Renderer* renderer, const char* tex, int x, int y, int w, int h, float angle, string tag, bool hasAnim, int damage, int direction, float scale, bool isHostile, int health) : GameObject(renderer, tex, x, y, w, h, angle, tag, hasAnim, scale, health)
	{
		setSpeed(projMoveSpeed * direction);
		spriteTime = totalSpellSpriteTime;
		this->damage = damage;
		this->isHostile = isHostile;
	}

	void Update(SDL_Renderer* renderer) override
	{
		for (int i = 0; i < Game::gameObjects.size(); i++)
		{
			GameObject* obj2 = Game::gameObjects.at(i);
			if (obj2 != this && obj2->Alive() && obj2->deathTimer == 0)
			{
				if (Game::checkCollission(this, obj2))
				{
					if ((obj2->hasTag("Player") && isHostile)
						|| (obj2->hasTag("Enemy") || obj2->hasTag("Boss")) && !isHostile)
					{
						takeHit(1);
						obj2->takeHit(damage);
						break;
					}
				}
			}
		}
		GameObject::Update(renderer);

		if (spriteTime > 0) spriteTime--;
		else
		{
			NextSprite(totalSpellSpriteTime);
		}

		UpdateDestRect();
		UpdateCollissionBox();
	}
};
