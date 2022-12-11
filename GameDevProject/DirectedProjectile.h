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
	DirectedProjectile(SDL_Renderer* renderer, const char* tex, int x, int y, int w, int h, float angle, string tag, bool hasAnim, int damage, int direction, float scale, bool isHostile, int health) : Projectile(renderer, tex, x, y, w, h, angle, tag, hasAnim, damage, direction, scale, isHostile, health)
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
};
