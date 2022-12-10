#pragma once
#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class Enemy : public GameObject
{
public:
	int attackTime;
	int range;
	Enemy(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, int range, float scale) : GameObject(renderer, path, x, y, w, h, angle, tag, hasAnimations, scale)
	{
		this->range = range;
		spriteTime = totalSpriteTime;
		attackTime = totalEnemyAttackTime;
		velocity.Zero();
		setFlip(SDL_FLIP_HORIZONTAL);
	}
	/*static GameObject* readNimble(ifstream& file)
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
		GameObject::Update(renderer);
		if (spriteTime > 0) spriteTime--;
		else NextSprite(totalSpriteTime);
		if (state != DEATH)
		{
			if (!isInRange(range))
			{
				if (state != ATTACKING)
				{
				Translate(speed * (flipStatus == SDL_FLIP_NONE ? 1 : -1), 0);
				setState(RUNNING);
				}
			}
			else { Translate(0, 0); if (attackTime > 0) setState(IDLE); }

			position.x += static_cast<int> (velocity.x);
			position.y += static_cast<int> (velocity.y);

			if (attackTime > 0) attackTime--;
			else
			{
				//attackTime = totalAttackTime;
				setState(ATTACKING);
				//Attack(renderer);
			}
			UpdateDestRect();
			UpdateCollissionBox();
		}
	}

	virtual void Attack(SDL_Renderer* renderer) {}
	bool isInRange(int range)
	{
		Vector2D playerPos = Game::gameObjects[0]->position;
		if (playerPos.x >= position.x) setFlip(SDL_FLIP_NONE);
		else if (playerPos.x < position.x) setFlip(SDL_FLIP_HORIZONTAL);
		playerPos.x -= position.x;
		playerPos.y -= position.y;
		return playerPos.magnitude() <= range;
	}
};
