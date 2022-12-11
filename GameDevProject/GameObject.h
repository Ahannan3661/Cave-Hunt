#pragma once
#include "Game.h"
#include "Vector2D.h"
#include <iostream>
#include <fstream>
#include "TextureManager.h"
#include "HealthBar.h"
#include <SDL_mixer.h>

using namespace std;

//base class for all gameObjects
class GameObject
{
private:
	Mix_Chunk* hitSound = NULL;
public:
	bool isInvinsible = false;
	SDL_RendererFlip flipStatus;
	int spriteOffsetX = 0;
	int spriteOffsetY = 0;
	int health;
	int state;
	float angle = 0.0f;
	vector<texStruct*> textures;;
	SDL_Rect srcRect, destRect, collissionBox;
	bool hasAnimations;
	bool alive = true;
	int speed = 1;
	Vector2D velocity;
	Vector2D position;
	string tag;
	int sheetWidth;
	int sheetHeight;
	int spriteTime;
	int deathTimer = 0;
	float scale;
	bool isJumping = false;
	int totalDeathTime = 0;
	HealthBar* healthBar = nullptr;

	GameObject(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, float scale, int health);
	~GameObject();

	void setState(int s);
	void setSpeed(int s) { speed = s; }

	bool hasTag(const char* tag)
	{
		return strcmp(this->tag.c_str(), tag) == 0;
	}

	float getAngle() { return angle; }

	virtual void takeHit(int damage)
	{
		if (!isInvinsible)
		{
			if (hasAnimations)
			{
				healthBar->shrinkBar(damage);
				Mix_PlayChannel(-1, hitSound, 0);
			}
			if (health > damage)
			{
				health -= damage;
				setState(HIT);
			}
			else 
			{
				deathTimer++; if (!hasTag("Projectile")) setState(DEATH); 
			}
		}
	}

	int getHealth() { return health; }

	void setHealth(int h) { health = h; }

	void setAngle(float a) { angle = a; }

	virtual void Update(SDL_Renderer* renderer) 
	{
		//update object's healthBar
		if (hasAnimations) healthBar->Update(collissionBox.x, collissionBox.y - 20);

		//if deathtimer has begun... Increment it
		if (deathTimer > 0)
		{
			deathTimer++;
		}
		//if death timer finished set alive to false
		if (deathTimer > totalDeathTime) 
		{
			Destroy();
		}
	}

	virtual void Render(SDL_Renderer* renderer);

	void UpdateCollissionBox();

	void setFlip(SDL_RendererFlip flip) { flipStatus = flip; }

	bool Alive() { return alive; }

	void Destroy() { alive = false; }

	void UpdateDestRect();

	void Translate(float a, float b) { velocity.x = a; velocity.y = b; }

	void NextSprite(int);
};

