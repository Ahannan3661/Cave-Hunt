#pragma once
#include<iostream>
#include <stdlib.h> 
#include "Enemy.h"
#include "StraightProjectile.h"
#include "Eye.h"
#include "Skeleton.h"
#include "Worm.h"

using namespace std;

class Boss : public Enemy
{
private:
	GameObject* eye = NULL;
	GameObject* skeleton = NULL;
	GameObject* worm = NULL;
	Mix_Chunk* youWin = NULL;
	Mix_Chunk* bossAttackSound = NULL;
public:
	Boss(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, int range, float scale, int health) : Enemy(renderer, path, x, y, w, h, angle, tag, hasAnimations, range, scale, health)
	{
		eye = new Eye(renderer, EYE, EYE_SPAWNX, EYE_SPAWNY, monsterSourceW, monsterSourceH, 0, "Enemy", true, eyeAttackRange, monsterScale, monsterHealth);
		skeleton = new Skeleton(renderer, SKELETON, MONSTER_SPAWNX, MONSTER_SPAWNY, monsterSourceW, monsterSourceH, 0.0f, "Enemy", true, skeletonGuardRange, monsterScale, meeleMonsterDamage, monsterHealth);
		worm = new Worm(renderer, WORM, MONSTER_SPAWNX, WORM_SPAWNY, wormSourceW, wormSourceH, 0.0f, "Enemy", true, wormAttackRange, monsterScale, monsterHealth);
		Game::gameObjects.push_back(eye);
		Game::gameObjects.push_back(skeleton);
		Game::gameObjects.push_back(worm);
		attackTime = bossAttackTime;
		totalDeathTime = totalEnemyDeathTime;
		spriteOffsetX = bossSpriteOffsetX;
		spriteOffsetY = bossSpriteOffsetY;
		collissionBox.x += bossSpriteOffsetX;
		collissionBox.y += bossSpriteOffsetY;
		collissionBox.w = bossSpriteW * scale;
		collissionBox.h = bossSpriteH * scale;
		healthBar->Update(collissionBox.x, collissionBox.y - 20);
		youWin = Mix_LoadWAV(YOUWINSOUND);
		bossAttackSound = Mix_LoadWAV(BOSSATTACKSOUND);
	}
	~Boss()
	{
		Mix_FreeChunk(youWin);
		youWin = NULL;
		Mix_FreeChunk(bossAttackSound);
		bossAttackSound = NULL;
		if(eye!= NULL)
		delete eye;
		eye = NULL;
		if (skeleton != NULL)
		delete skeleton;
		skeleton = NULL;
		if (worm != NULL)
		delete worm;
		worm = NULL;
	}
	void Update(SDL_Renderer* renderer) override
	{
		if (deathTimer > 0)
		{
			if (deathTimer < 2)
			{
				eye->takeHit(eye->health);
				Mix_PlayChannel(-1, youWin, 0);
			}
			if (!canSummon()) skeleton->takeHit(skeleton->health);
		}
		Enemy::Update(renderer);
		if (!canSummon() && state == ATTACKING)
		{
			attackTime = bossAttackTime;
			setState(IDLE);
		}

		if(state == ATTACKING && srcRect.x == 0 && canSummon()) Mix_PlayChannel(-1, bossAttackSound, 0);

		if (state == ATTACKING && srcRect.x == sheetWidth - srcRect.w && canSummon())
		{
			
			skeleton = new Skeleton(renderer, SKELETON, MONSTER_SPAWNX, MONSTER_SPAWNY, monsterSourceW, monsterSourceH, 0.0f, "Enemy", true, skeletonGuardRange, monsterScale, meeleMonsterDamage, monsterHealth);
			Game::gameObjects.push_back(skeleton);
			Game::skeletonKilled = false;
			attackTime = bossAttackTime;
			setState(IDLE);
		}
	}
	bool canSummon()
	{
		return Game::skeletonKilled;
	}
};
