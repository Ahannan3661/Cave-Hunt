#pragma once
#include<iostream>
#include <stdlib.h> 
#include "Enemy.h"

using namespace std;

class Goblin : public Enemy
{
public:
	//bool hitRegistered = false;
	int damage;
	Goblin(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, int range, float scale, int damage) : Enemy(renderer, path, x, y, w, h, angle, tag, hasAnimations, range, scale)
	{
		this->damage = damage;
		totalDeathTime = totalEnemyDeathTime;
		spriteOffsetX = monsterSpriteOffsetX;
		spriteOffsetY = monsterSpriteOffsetY;
		collissionBox.x += monsterSpriteOffsetX;
		collissionBox.y += monsterSpriteOffsetY;
		collissionBox.w = monsterSpriteW * scale;
		collissionBox.h = monsterSpriteH * scale;
		setHealth(20);
		setSpeed(2);
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
		if (state == ATTACKING && srcRect.x == sheetWidth - srcRect.w)
		{
			if (isInRange(range))
			{
				Game::gameObjects[0]->takeHit(damage);
			}
			attackTime = totalEnemyAttackTime;
			setState(IDLE);
		}
		Enemy::Update(renderer);
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
	bool OnCoolDown();
};
