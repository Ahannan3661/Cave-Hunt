#pragma once
#include<iostream>
#include <stdlib.h> 
#include "Enemy.h"
#include "DirectedProjectile.h"

using namespace std;

class Eye : public Enemy
{
private:
	Vector2D playerPos;
	Mix_Chunk* eyeAttackSound = NULL;
public:
	Eye(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, int range, float scale, int health) : Enemy(renderer, path, x, y, w, h, angle, tag, hasAnimations, range, scale, health)
	{
		playerPos = Game::gameObjects.at(0)->position;
		totalDeathTime = totalEnemyDeathTime;
		spriteOffsetX = monsterSpriteOffsetX;
		spriteOffsetY = monsterSpriteOffsetY;
		collissionBox.x += monsterSpriteOffsetX;
		collissionBox.y += monsterSpriteOffsetY;
		collissionBox.w = monsterSpriteW * scale;
		collissionBox.h = monsterSpriteH * scale;
		healthBar->Update(collissionBox.x, collissionBox.y - 20);
		eyeAttackSound = Mix_LoadWAV(SPELLSOUND);
	}
	~Eye()
	{
		Mix_FreeChunk(eyeAttackSound);
		eyeAttackSound = NULL;
	}
	
	void Update(SDL_Renderer* renderer) override
	{
		if (state == DEATH)
		{
			if(position.y < PLATFORM_HEIGHT - monsterSpriteOffsetY - monsterSpriteH)
			position.y += speed;
			UpdateDestRect();
		}
		else
		{
			playerPos = Game::gameObjects.at(0)->position;
			setAngle(position.getAngle(playerPos));
		}
		if (state == ATTACKING && srcRect.x == sheetWidth - srcRect.w)
		{
			Mix_PlayChannel(-1, eyeAttackSound, 0);
			Game::gameObjects.push_back(new DirectedProjectile(renderer, EYESPELL, position.x + (monsterSpriteOffsetX * scale * (flipStatus == SDL_FLIP_NONE ? scale : 1)), position.y + (monsterSpriteOffsetY * scale) + projH/2, projW, projH, 0.0f, "Projectile", false, hostileProjDamage, 1, projScale, true, projHealth));
			attackTime = totalEnemyAttackTime;
			setState(IDLE);
		}
		Enemy::Update(renderer);
	}
};
