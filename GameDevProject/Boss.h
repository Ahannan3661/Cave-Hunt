#pragma once
#include<iostream>
#include <stdlib.h> 
#include "Enemy.h"
#include "StraightProjectile.h"
#include "Eye.h"
#include "Skeleton.h"
#include "Worm.h"

using namespace std;

//final necromancer boss is created via this class
class Boss : public Enemy
{
private:
	//3 enemies that the boss brings with him
	GameObject* eye = NULL;
	GameObject* skeleton = NULL;
	GameObject* worm = NULL;
	//sounds
	Mix_Chunk* youWin = NULL;
	Mix_Chunk* bossAttackSound = NULL;
public:
	Boss(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, int range, float scale, int health) : Enemy(renderer, path, x, y, w, h, angle, tag, hasAnimations, range, scale, health)
	{
		//initializing the 3 enemies with boss
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

		//creating a different rectangle for precise collission
		collissionBox.x += bossSpriteOffsetX;
		collissionBox.y += bossSpriteOffsetY;
		collissionBox.w = bossSpriteW * scale;
		collissionBox.h = bossSpriteH * scale;

		//place health bar on top of object
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

		//deleting all enemies if not already deleted
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
		//if the death animation has started
		if (deathTimer > 0)
		{
			//only call this once
			if (deathTimer < 2)
			{
				//kill eye
				eye->takeHit(eye->health);
				Mix_PlayChannel(-1, youWin, 0);
			}
			//kill skeleton if not already dead
			if (!canSummon()) skeleton->takeHit(skeleton->health);
		}

		Enemy::Update(renderer);

		//Reset attack time if a skeleton is already summoned
		if (!canSummon() && state == ATTACKING)
		{
			attackTime = bossAttackTime;
			setState(IDLE);
		}

		//summon a skeleton if none are there
		if (state == ATTACKING && srcRect.x == sheetWidth - srcRect.w && canSummon())
		{
			//play attacking sound
			Mix_PlayChannel(-1, bossAttackSound, 0);
			skeleton = new Skeleton(renderer, SKELETON, MONSTER_SPAWNX, MONSTER_SPAWNY, monsterSourceW, monsterSourceH, 0.0f, "Enemy", true, skeletonGuardRange, monsterScale, meeleMonsterDamage, monsterHealth);
			Game::gameObjects.push_back(skeleton);
			Game::skeletonKilled = false;
			attackTime = bossAttackTime;
			setState(IDLE);
		}
	}

	//returns true if a skeleton can be summoned else false
	bool canSummon()
	{
		return Game::skeletonKilled;
	}
};
