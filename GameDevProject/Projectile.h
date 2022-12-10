#pragma once
#pragma once
#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class Projectile : public GameObject
{
private:
	Uint32 spriteStart = totalSpellSpriteTime;
	int damage = 1;
public:
	bool isHostile;
	Projectile(SDL_Renderer* renderer, const char* tex, int x, int y, int w, int h, float angle, string tag, bool hasAnim, int damage, int direction, float scale, bool isHostile) : GameObject(renderer, tex, x, y, w, h, angle, tag, hasAnim, scale)
	{
		setSpeed(6 * direction);
		spriteTime = totalSpellSpriteTime;
		this->damage = damage;
		this->isHostile = isHostile;
	}

	void Update(SDL_Renderer* renderer) override
	{
		for (int i = 0; i < Game::gameObjects.size(); i++)
		{
			GameObject* obj2 = Game::gameObjects.at(i);
			if (obj2 != this && obj2->Alive() && obj2->deathTimer == 0)
			{
				if (Game::checkCollission(this, obj2))
				{
					if ((obj2->hasTag("Player") && isHostile)
						|| (obj2->hasTag("Enemy") || obj2->hasTag("Boss")) && !isHostile)
					{
						takeHit(1);
						obj2->takeHit(damage);
						break;
					}
				}
			}
		}
		GameObject::Update(renderer);

		if (spriteTime > 0) spriteTime--;
		else
		{
			NextSprite(totalSpellSpriteTime);
		}

		//updating destRect values
		UpdateDestRect();
		UpdateCollissionBox();
	}
	/*void writeToFile(ofstream& file) override
	{
		file << "[Bullet]\n";
		GameObject::writeToFile(file);
		int temp;
		playerDirection.x == numeric_limits<float>::max() ? temp = 0 : temp = 1;
		file << temp << "\n";
		file << home ? 0 : 1;
		file << "\n";
		file << damage << "\n";
		file << spriteStart << "\n";
		file << smokeCoolDown << "\n";
	}
	static GameObject* readBullet(ifstream& file)
	{
		Bullet* temp = new Bullet();
		GameObject* readObject = temp->readFromFile(file);
		delete temp;
		temp = nullptr;
		return readObject;
	}
	GameObject* readFromFile(ifstream& file) override
	{
		GameObject* clone = GameObject::readGameObject(file);
		bool targeted;
		int temp; file >> temp; temp == 1 ? targeted = true : targeted = false;
		bool home;
		temp; file >> temp; temp == 1 ? home = true : home = false;
		int damage;
		file >> damage;
		Bullet* readBullet;
		if (targeted)
		{
			readBullet = new Bullet(clone->path, clone->position.x, clone->position.y, clone->width, clone->health, clone->scale, clone->sheetWidth, home, clone->hostile, clone->angle, Game::gameObjects.at(0)->position - 32, damage);
		}
		else
		{
			readBullet = new Bullet(clone->path, clone->position.x, clone->position.y, clone->width, clone->health, clone->scale, clone->sheetWidth, home, clone->hostile, clone->angle, damage);
		}
		readBullet->velocity = clone->velocity;
		delete clone;
		clone = nullptr;
		file >> readBullet->spriteStart;
		file >> readBullet->smokeCoolDown;
		return readBullet;
	}*/
};
