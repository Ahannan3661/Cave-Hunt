#pragma once
#include<iostream>
#include <stdlib.h> 
#include "Enemy.h"
#include "ThunderCloud.h"
#include "ThunderBolt.h"

using namespace std;

class DarkWiz : public Enemy
{
private:
	GameObject* thunderCloud;
	Mix_Chunk* wizAttackSound = NULL;
public:
	DarkWiz(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, int range, float scale, int health) : Enemy(renderer, path, x, y, w, h, angle, tag, hasAnimations, range, scale, health)
	{
		totalDeathTime = totalEnemyDeathTime;
		spriteOffsetX = darkWizSpriteOffsetX;
		spriteOffsetY = darkWizSpriteOffsetY;
		collissionBox.x += darkWizSpriteOffsetX;
		collissionBox.y += darkWizSpriteOffsetY;
		collissionBox.w = darkWizSpriteW * scale;
		collissionBox.h = darkWizSpriteH * scale;
		healthBar->Update(collissionBox.x, collissionBox.y - 20);
		thunderCloud = new ThunderCloud(renderer, TUNDERCLOUD, x, CLOUD_SPAWNY, cloudW, cloudH, 0.0f, "Cloud", false, cloudScale, 1);
		wizAttackSound = Mix_LoadWAV(SPELLSOUND);
	}
	~DarkWiz()
	{
		Mix_FreeChunk(wizAttackSound);
		delete wizAttackSound;
		delete thunderCloud;
		thunderCloud = nullptr;
	}
	void Update(SDL_Renderer* renderer) override
	{
		if(state != DEATH)
			thunderCloud->Update(renderer);
		Enemy::Update(renderer);
		if (state == ATTACKING && srcRect.x == sheetWidth - srcRect.w)
		{
			Mix_PlayChannel(-1, wizAttackSound, 0);
			Game::gameObjects.push_back(new ThunderBolt(renderer, THUNDERBOLT, thunderCloud->position.x + thunderCloud->destRect.w/2 - boltW/2, thunderCloud->position.y + thunderCloud->destRect.h/2, boltW, boltH, boltAngle, "Projectile", false, hostileProjDamage, 1, boltScale, true, projHealth));
			attackTime = totalEnemyAttackTime;
			setState(IDLE);
		}
	}
	void Render(SDL_Renderer* renderer) override
	{
		thunderCloud->Render(renderer);
		GameObject::Render(renderer);
	}
};
