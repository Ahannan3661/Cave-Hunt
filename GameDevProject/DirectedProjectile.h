#pragma once
#include<iostream>
#include <stdlib.h> 
#include "Projectile.h"

using namespace std;

class DirectedProjectile : public Projectile
{
private:
	Vector2D direction;
public:
	DirectedProjectile(SDL_Renderer* renderer, const char* tex, int x, int y, int w, int h, float angle, string tag, bool hasAnim, int damage, int direction, float scale, bool isHostile) : Projectile(renderer, tex, x, y, w, h, angle, tag, hasAnim, damage, direction, scale, isHostile)
	{
		Vector2D playerPos = Game::gameObjects[0]->position;
		playerPos.x += 150;
		playerPos.y += 150;
		setAngle(position.getAngle(playerPos));
		this->direction = position.unit(playerPos);
	}
	void Update(SDL_Renderer* renderer) override
	{
		Projectile::Update(renderer);
		position.x += direction.x * speed;
		position.y += direction.y * speed;
		if (position.x < 0 || position.x > SCREEN_WIDTH || position.y < 0 || position.y > SCREEN_HEIGHT)
			Destroy();
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
