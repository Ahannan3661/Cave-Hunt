#pragma once
#include <stdlib.h> 
#include "GameObject.h"
#include <SDL_mixer.h>
#include "Constants.h"
#include "StraightProjectile.h"

using namespace std;

class Player : public GameObject
{
private:
	int spellCount;
	int castingCooldown;
	int reloadStart = totalSpellReloadTime;
public:
	int score = 0;
	Player(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, float scale);
	~Player() {}
	/*static GameObject* readPlayer(ifstream& file)
	{
		Player* temp = new Player();
		GameObject* readObject = temp->readFromFile(file);
		delete temp;
		temp = nullptr;
		return readObject;
	}
	GameObject* readFromFile(ifstream& file) override
	{
		GameObject* clone = GameObject::readGameObject(file);
		Player* readPlayer = new Player(clone->path, clone->position.x, clone->position.y, clone->width, clone->health, clone->scale, clone->sheetWidth);
		readPlayer->setHealth(clone->getHealth());
		readPlayer->velocity = clone->velocity;
		delete clone;
		clone = nullptr;
		file >> readPlayer->missileCount;
		file >> readPlayer->shootingCoolDown;
		file >> readPlayer->reloadStart;
		file >> readPlayer->score;
		return readPlayer;
	}
	void writeToFile(ofstream& file) override
	{
		file << "[Player]\n";
		GameObject::writeToFile(file);
		file << missileCount << "\n";
		file << shootingCoolDown << "\n";
		file << reloadStart << "\n";
		file << score << "\n";
	}*/
	void Update(SDL_Renderer*) override;
	bool OnCoolDown();
	int getSpells() { return spellCount; }
	GameObject* cast1(SDL_Renderer*);
	GameObject* cast2(SDL_Renderer*);
	bool hasSpell() { return spellCount > 0; }
};
