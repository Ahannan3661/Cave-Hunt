#pragma once
#include<iostream>
#include <stdlib.h> 
#include "Enemy.h"

using namespace std;

class Skeleton : public Enemy
{
private:
	Mix_Chunk* skeletonAttackSound = NULL;
public:
	int damage;
	texStruct* shield;
	int attackRange;
	bool isGuarding = false;
	int guardDuration = totalGuardDuration;

	Skeleton(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, int range, float scale, int damage, int health) : Enemy(renderer, path, x, y, w, h, angle, tag, hasAnimations, range, scale, health)
	{
		this->damage = damage;
		totalDeathTime = totalEnemyDeathTime;
		spriteOffsetX = monsterSpriteOffsetX;
		spriteOffsetY = monsterSpriteOffsetY;
		collissionBox.x += monsterSpriteOffsetX;
		collissionBox.y += monsterSpriteOffsetY;
		collissionBox.w = monsterSpriteW * scale;
		collissionBox.h = monsterSpriteH * scale;
		attackRange = skeletonAttackRange;
		shield = TextureManager::LoadTexture(renderer, SKELETON_SHIELD);
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
		if (isGuarding && state == ATTACKING)
		{
			isInvinsible = true;
		}
		if (isGuarding)
		{
			guardDuration--;
		}
		if (isInRange(range) && !isInRange(attackRange) && state == ATTACKING && !isGuarding)
		{
			isGuarding = true;
			guardDuration = totalGuardDuration;
			texStruct* temp = textures[ATTACKING];
			textures[ATTACKING] = shield;
			shield = temp;
		}
		if (isInRange(attackRange) && state == ATTACKING && isGuarding)
		{
			isGuarding = false;
			isInvinsible = false;
			texStruct* temp = textures[ATTACKING];
			textures[ATTACKING] = shield;
			shield = temp;
		}
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
