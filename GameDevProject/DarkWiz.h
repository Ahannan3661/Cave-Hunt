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
public:
	DarkWiz(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, int range, float scale) : Enemy(renderer, path, x, y, w, h, angle, tag, hasAnimations, range, scale)
	{
		totalDeathTime = totalEnemyDeathTime;
		spriteOffsetX = darkWizSpriteOffsetX;
		spriteOffsetY = darkWizSpriteOffsetY;
		collissionBox.x += darkWizSpriteOffsetX;
		collissionBox.y += darkWizSpriteOffsetY;
		collissionBox.w = darkWizSpriteW * scale;
		collissionBox.h = darkWizSpriteH * scale;
		setHealth(20);
		setSpeed(2);
		char temp[200];
		memset(temp, 0, sizeof temp);
		strcpy_s(temp, sizeof temp, path);
		strcat_s(temp, sizeof temp, "/thunderCloud.png");;
		thunderCloud = new ThunderCloud(renderer, temp, x, 50, 32, 32, 0.0f, "Cloud", false, 3);
	}
	~DarkWiz()
	{
		delete thunderCloud;
		thunderCloud = nullptr;
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
		if(state != DEATH)
			thunderCloud->Update(renderer);
		Enemy::Update(renderer);
		if (state == ATTACKING && srcRect.x == sheetWidth - srcRect.w)
		{
			Game::gameObjects.push_back(new ThunderBolt(renderer, "assets/monsters/darkWiz/bolt.png", thunderCloud->position.x + thunderCloud->destRect.w/2 - 16, thunderCloud->position.y + thunderCloud->destRect.h/2, 32, 32, 90.0f, "Projectile", false, 10, 1, 1, true));
			attackTime = totalEnemyAttackTime;
			setState(IDLE);
		}
	}
	void Render(SDL_Renderer* renderer) override
	{
		thunderCloud->Render(renderer);
		GameObject::Render(renderer);
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
