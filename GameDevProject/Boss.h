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
public:
	Boss(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, int range, float scale) : Enemy(renderer, path, x, y, w, h, angle, tag, hasAnimations, range, scale)
	{
		eye = new Eye(renderer, "assets/monsters/eye", -50, -50, 150, 150, 0, "Enemy", true, 500, 1.5);
		skeleton = new Skeleton(renderer, "assets/monsters/skeleton", SCREEN_WIDTH - 100, PLATFORM_HEIGHT - ((monsterSpriteOffsetY + monsterSpriteH) * 1.5), 150, 150, 0, "Enemy", true, 200, 1.5, 5);
		worm = new Worm(renderer, "assets/monsters/worm", SCREEN_WIDTH - 100, PLATFORM_HEIGHT - ((wormSpriteOffsetY + wormSpriteH) * 1.5) + 15, 90, 90, 0, "Enemy", true, 350, 1.5);
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
		setHealth(40);
		setSpeed(2);
	}
	~Boss()
	{
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
	/*
	static GameObject* readNimble(ifstream& file)
	{
		Nimble* temp = new Nimble();
		GameObject* readObject = temp->readFromFile(file);
		delete temp;
		temp = nullptr;
		return readObject;
	}
	GameObject* readFromFile(ifstream& file) override
	{
		GameObject* clone = GameObject::readGameObject(file);
		Nimble* readNimble = new Nimble(clone->path, clone->position.x, clone->position.y, clone->width, clone->health, clone->scale, clone->sheetWidth);
		readNimble->velocity = clone->velocity;
		delete clone;
		clone = nullptr;
		file >> readNimble->shootingCooldown;
		file >> readNimble->dodgingCoolDown;
		return readNimble;
	}
	void writeToFile(ofstream& file) override
	{
		file << "[Nimble]\n";
		GameObject::writeToFile(file);
		file << shootingCooldown << "\n";
		file << dodgingCoolDown << "\n";
	}*/
	void Update(SDL_Renderer* renderer) override
	{
		if (deathTimer > 0)
		{
			if (deathTimer < 2 ) eye->takeHit(eye->health);
			if (!canSummon()) skeleton->takeHit(skeleton->health);
		}
		Enemy::Update(renderer);
		if (!canSummon() && state == ATTACKING)
		{
			attackTime = bossAttackTime;
			setState(IDLE);
		}
		if (state == ATTACKING && srcRect.x == sheetWidth - srcRect.w && canSummon())
		{
			skeleton = new Skeleton(renderer, "assets/monsters/skeleton", SCREEN_WIDTH - 100, PLATFORM_HEIGHT - ((monsterSpriteOffsetY + monsterSpriteH) * 1.5), 150, 150, 0, "Enemy", true, 250, 1.5, 5);
			Game::gameObjects.push_back(skeleton);
			Game::skeletonKilled = false;
			attackTime = bossAttackTime;
			setState(IDLE);
		}
		//if (eye != nullptr) eye->Update(renderer);
		//if (skeleton != nullptr) skeleton->Update(renderer);
		//if (worm != nullptr) worm->Update(renderer);
	}
	bool canSummon()
	{
		return Game::skeletonKilled;
	}
	/*void Attack(SDL_Renderer* renderer) override
	{
		if (state == ATTACKING && srcRect.x == sheetWidth - srcRect.w)
		{
			Game::gameObjects.push_back(new PoisonBall(renderer, "assets/monsters/mushroom/poisonBall.png", position.x - monsterSpriteOffsetX - monsterSpriteW, position.y + monsterSpriteOffsetY, 32, 32, 0.0f, "PoisonBall", false, 5, -1));
			spriteTime = 0;
			attackTime = totalAttackTime;
		}
	}*/
};
