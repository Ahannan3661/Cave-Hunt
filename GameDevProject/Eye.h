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
public:
	Eye(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, int range, float scale) : Enemy(renderer, path, x, y, w, h, angle, tag, hasAnimations, range, scale)
	{
		playerPos = Game::gameObjects.at(0)->position;
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
			Game::gameObjects.push_back(new DirectedProjectile(renderer, "assets/monsters/eye/eyeSpell.png", position.x + (monsterSpriteOffsetX * scale * (flipStatus == SDL_FLIP_NONE ? scale : 1)), position.y + (monsterSpriteOffsetY * scale) + 15, 32, 32, 0.0f, "Projectile", false, 5, 1, 1, true));
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
