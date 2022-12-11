#pragma once
#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

//base class for all enemies
class Enemy : public GameObject
{
public:
	int attackTime;

	//this is how close the enemy will get to the player
	int range;

	Enemy(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, int range, float scale, int health) : GameObject(renderer, path, x, y, w, h, angle, tag, hasAnimations, scale, health)
	{
		this->range = range;
		spriteTime = totalSpriteTime;
		attackTime = totalEnemyAttackTime;
		velocity.Zero();
		setFlip(SDL_FLIP_HORIZONTAL);
		setSpeed(enemyMoveSpeed);
	}
	void Update(SDL_Renderer* renderer) override 
	{
		GameObject::Update(renderer);

		if (spriteTime > 0) spriteTime--;
		else NextSprite(totalSpriteTime);

		if (state != DEATH)
		{
			if (!isInRange(range))
			{
				if (state != ATTACKING)
				{
					Translate(speed * (flipStatus == SDL_FLIP_NONE ? 1 : -1), 0);
					setState(RUNNING);
				}
			}
			else { Translate(0, 0); if (attackTime > 0) setState(IDLE); }

			position.x += static_cast<int> (velocity.x);
			position.y += static_cast<int> (velocity.y);

			if (attackTime > 0) attackTime--;
			else
			{
				setState(ATTACKING);
			}
			UpdateDestRect();
			UpdateCollissionBox();
		}
	}

	//check if enemy is in range of the player
	bool isInRange(int range)
	{
		Vector2D playerPos = Game::gameObjects[0]->position;
		if (playerPos.x >= position.x) setFlip(SDL_FLIP_NONE);
		else if (playerPos.x < position.x) setFlip(SDL_FLIP_HORIZONTAL);
		playerPos.x -= position.x;
		playerPos.y -= position.y;
		return playerPos.magnitude() <= range;
	}
};
