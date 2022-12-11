#pragma once
#include<iostream>
#include <stdlib.h> 
#include "Enemy.h"

using namespace std;

//Skeleton enemy is created via this class
class Skeleton : public Enemy
{
private:
	Mix_Chunk* skeletonAttackSound = NULL;
public:
	int damage;

	//shield animation
	texStruct* shield;

	//attack range which is different from shield range (range)
	int attackRange;

	//indicates whether attacking sprite is replaced with shielding sprite or not
	bool isGuarding = false;

	int guardDuration = totalGuardDuration;

	Skeleton(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, int range, float scale, int damage, int health) : Enemy(renderer, path, x, y, w, h, angle, tag, hasAnimations, range, scale, health)
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

		attackRange = skeletonAttackRange;
		shield = TextureManager::LoadTexture(renderer, SKELETON_SHIELD);

		//place health bar on top of object
		healthBar->Update(collissionBox.x, collissionBox.y - 20);

		skeletonAttackSound = Mix_LoadWAV(MEELEATTACKSOUND);
	}
	~Skeleton()
	{
		Mix_FreeChunk(skeletonAttackSound);
		skeletonAttackSound = NULL;
		delete shield;
		shield = nullptr;
	}
	void Update(SDL_Renderer* renderer) override
	{
		Enemy::Update(renderer);

		if (state == DEATH) Game::skeletonKilled = true;

		//while shielding, the skeleton becomes invinsible
		if (isGuarding && state == ATTACKING)
		{
			isInvinsible = true;
		}

		if (isGuarding)
		{
			guardDuration--;
		}

		//if in shielding range and not in attacking switch from attacking to shielding
		if (isInRange(range) && !isInRange(attackRange) && state == ATTACKING && !isGuarding)
		{
			isGuarding = true;
			guardDuration = totalGuardDuration;
			texStruct* temp = textures[ATTACKING];
			textures[ATTACKING] = shield;
			shield = temp;
		}
		//if in attacking range aswitch from shielding to attacking 
		if (isInRange(attackRange) && state == ATTACKING && isGuarding)
		{
			isGuarding = false;
			isInvinsible = false;
			texStruct* temp = textures[ATTACKING];
			textures[ATTACKING] = shield;
			shield = temp;
		}

		//if not attacking then player takes damage when in range
		if (state == ATTACKING && srcRect.x == sheetWidth - srcRect.w && !isGuarding)
		{
			Mix_PlayChannel(-1, skeletonAttackSound, 0);
			if (isInRange(attackRange))
			{
				Game::gameObjects[0]->takeHit(damage);
			}
			attackTime = totalEnemyAttackTime;
			setState(IDLE);
		}

		//if shield duration has ended then become vulnderable and set mode to attacking while set state to IDLE
		if (guardDuration <= 0)
		{
			isGuarding = false;
			texStruct* temp = textures[ATTACKING];
			textures[ATTACKING] = shield;
			shield = temp;
			isInvinsible = false;
			guardDuration = totalGuardDuration;
			attackTime = totalAttackTime;
			setState(IDLE);
		}
	}
};
