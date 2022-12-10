#pragma once
#include "Game.h"
#include "Vector2D.h"
#include <iostream>
#include <fstream>
#include "TextureManager.h"
#include "Constants.h"



using namespace std;

class GameObject
{
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

	virtual void writeToFile(ofstream& file)
	{
		file << health << "\n";
		file << angle << "\n";
		file << alive ? 1 : 0;
		file << "\n";
		file << speed << "\n";
		file << velocity.x << "\n";
		file << velocity.y << "\n";
		file << position.x << "\n";
		file << position.y << "\n";
		file << tag << "\n";
		file << srcRect.x << "\n";
		file << srcRect.y << "\n";
		file << srcRect.w << "\n";
		file << srcRect.h << "\n";
	}
	/*static GameObject* readGameObject(ifstream& file)
	{
		GameObject* temp = new GameObject();
		GameObject* readObject(temp->readFromFile(file));
		delete temp;
		temp = nullptr;
		return readObject;
	}

	virtual GameObject* readFromFile(ifstream& file)
	{
		char* path = _strdup(" ");
		file >> path;
		int health;
		file >> health;
		float angle;
		file >> angle;
		bool alive;
		int temp; file >> temp; temp == 1 ? alive = true : alive = false;
		int scale;
		file >> scale;
		int sheetWidth;
		file >> sheetWidth;
		int speed;
		file >> speed;
		Vector2D velocity;
		file >> velocity.x;
		file >> velocity.y;
		Vector2D position;
		file >> position.x;
		file >> position.y;
		int width;
		file >> width;
		int height;
		file >> height;
		string tag;
		file >> tag;
		bool hostile;
		temp; file >> temp; temp == 1 ? hostile = true : hostile = false;
		SDL_Rect srcRect;
		file >> srcRect.x;
		file >> srcRect.y;
		GameObject* clone = new GameObject(path, position.x, position.y, width, height, scale, sheetWidth, angle, tag);
		clone->velocity = velocity;
		clone->health = health;
		clone->alive = alive;
		clone->speed = speed;
		clone->hostile = hostile;
		clone->srcRect.x = srcRect.x;
		clone->srcRect.y = srcRect.y;
		return clone;
	}*/

	GameObject(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, float scale);
	~GameObject();

	//void nextSprite();

	void setAlpha(int a) { SDL_SetTextureAlphaMod(textures[state]->tex, a); }

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
			if (health > damage)
			{
				health -= damage;
				setState(HIT);
			}
			else { deathTimer++; if (!hasTag("Projectile")) setState(DEATH); }
		}
	}

	int getHealth() { return health; }

	void setHealth(int h) { health = h; }

	void setAngle(float a) { angle = a; }

	virtual void Update(SDL_Renderer* renderer) 
	{
		if (deathTimer > 0)
		{
			deathTimer++;
		}
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

	void setTex(SDL_Texture* tex) { textures[state]->tex = tex; }

	void UpdateDestRect();

	void Translate(float a, float b) { velocity.x = a; velocity.y = b; }

	void NextSprite(int);
};

