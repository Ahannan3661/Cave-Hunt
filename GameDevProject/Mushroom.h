#pragma once
#include<iostream>
#include <stdlib.h> 
#include "Enemy.h"
#include "StraightProjectile.h"

using namespace std;

class Mushroom : public Enemy
{
private:
	Mix_Chunk* shroomAttackSound = NULL;
public:
	Mushroom(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, int range, float scale, int health) : Enemy(renderer, path, x, y, w, h, angle, tag, hasAnimations, range, scale, health)
	{
		totalDeathTime = totalEnemyDeathTime;
		spriteOffsetX = monsterSpriteOffsetX;
		spriteOffsetY = monsterSpriteOffsetY;
		collissionBox.x += monsterSpriteOffsetX;
		collissionBox.y += monsterSpriteOffsetY;
		collissionBox.w = monsterSpriteW*scale;
		collissionBox.h = monsterSpriteH*scale;
		healthBar->Update(collissionBox.x, collissionBox.y - 20);
		shroomAttackSound = Mix_LoadWAV(SPELLSOUND);
	}
	~Mushroom()
	{
		Mix_FreeChunk(shroomAttackSound);
		shroomAttackSound = NULL;
	}
	void Update(SDL_Renderer* renderer) override
	{
		Enemy::Update(renderer);
		if (state == ATTACKING && srcRect.x == sheetWidth - srcRect.w)
		{
			Mix_PlayChannel(-1, shroomAttackSound, 0);
			Game::gameObjects.push_back(new StraightProjectile(renderer, POISONBALL, position.x + (monsterSpriteOffsetX * scale * (flipStatus == SDL_FLIP_NONE ? scale : 1)), position.y + (monsterSpriteOffsetY*scale) + projH/2, projW, projH, 0.0f, "Projectile", false, hostileProjDamage, (flipStatus == SDL_FLIP_NONE ? 1 : -1), projScale, true, projHealth));
			attackTime = totalEnemyAttackTime;
			setState(IDLE);
		}
	}
};
