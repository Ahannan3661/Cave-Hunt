#pragma once
#include<iostream>
#include <stdlib.h> 
#include "Enemy.h"
#include "StraightProjectile.h"

using namespace std;

class Worm : public Enemy
{
private:
	Mix_Chunk* wormAttackSound = NULL;
public:
	Worm(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, int range, float scale, int health) : Enemy(renderer, path, x, y, w, h, angle, tag, hasAnimations, range, scale, health)
	{
		totalDeathTime = totalEnemyDeathTime;
		spriteOffsetX = wormSpriteOffsetX;
		spriteOffsetY = wormSpriteOffsetY;
		collissionBox.x += wormSpriteOffsetX;
		collissionBox.y += wormSpriteOffsetY;
		collissionBox.w = wormSpriteW * scale;
		collissionBox.h = wormSpriteH * scale;
		healthBar->Update(collissionBox.x, collissionBox.y - 20);
		wormAttackSound = Mix_LoadWAV(SPELLSOUND);
	}
	~Worm()
	{
		Mix_FreeChunk(wormAttackSound);
		wormAttackSound = NULL;
	}
	void Update(SDL_Renderer* renderer) override
	{
		Enemy::Update(renderer);
		if (state == ATTACKING && srcRect.x == sheetWidth - srcRect.w*4)
		{
			Mix_PlayChannel(-1, wormAttackSound, 0);
			Game::gameObjects.push_back(new StraightProjectile(renderer, FIREBALL, position.x + (wormSpriteOffsetX * scale * (flipStatus == SDL_FLIP_NONE ? scale : 1)), position.y + (wormSpriteOffsetY * scale) + 15, projW, projH, 0.0f, "Projectile", false, hostileProjDamage, (flipStatus == SDL_FLIP_NONE ? 1 : -1), projScale, true, projHealth));
			attackTime = totalEnemyAttackTime;
			setState(IDLE);
		}
	}
};
