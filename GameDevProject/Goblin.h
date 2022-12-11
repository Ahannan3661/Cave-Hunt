#pragma once
#include<iostream>
#include <stdlib.h> 
#include "Enemy.h"

using namespace std;

//Goblin enemy is created via this class
class Goblin : public Enemy
{
private:
	Mix_Chunk* goblinAttackSound = NULL;
public:
	int damage;
	Goblin(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, int range, float scale, int damage, int health) : Enemy(renderer, path, x, y, w, h, angle, tag, hasAnimations, range, scale, health)
	{
		this->damage = damage;
		totalDeathTime = totalEnemyDeathTime;
		spriteOffsetX = monsterSpriteOffsetX;
		spriteOffsetY = monsterSpriteOffsetY;

		//creating a different rectangle for precise collission
		collissionBox.x += monsterSpriteOffsetX;
		collissionBox.y += monsterSpriteOffsetY;
		collissionBox.w = monsterSpriteW * scale;
		collissionBox.h = monsterSpriteH * scale;

		//place health bar on top of object
		healthBar->Update(collissionBox.x, collissionBox.y - 20);

		goblinAttackSound = Mix_LoadWAV(MEELEATTACKSOUND);
	}
	~Goblin()
	{
		Mix_FreeChunk(goblinAttackSound);
		goblinAttackSound = NULL;
	}
	
	void Update(SDL_Renderer* renderer) override
	{
		//perform a meele attack
		if (state == ATTACKING && srcRect.x == sheetWidth - srcRect.w)
		{
			Mix_PlayChannel(-1, goblinAttackSound, 0);
			//if the player is in range, they take damage else they don't
			if (isInRange(range))
			{
				Game::gameObjects[0]->takeHit(damage);
			}
			attackTime = totalEnemyAttackTime;
			setState(IDLE);
		}
		Enemy::Update(renderer);
	}

};
