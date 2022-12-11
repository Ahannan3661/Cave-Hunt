#pragma once
#include <stdlib.h> 
#include "GameObject.h"
#include <SDL_mixer.h>
#include "StraightProjectile.h"

using namespace std;

//Player is created via this class
class Player : public GameObject
{
private:
	int castingCooldown;
	bool soundPlayed = false;
	Mix_Chunk* youLose = NULL;
	Mix_Chunk* spellSound = NULL;
public:
	int score = 0;
	Player(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, float scale, int health);
	~Player() 
	{
		Mix_FreeChunk(youLose);
		youLose = NULL;
		Mix_FreeChunk(spellSound);
		spellSound = NULL;
	}
	void Update(SDL_Renderer*) override;
	bool OnCoolDown();
	GameObject* cast1(SDL_Renderer*);
};
