#include "Player.h"

Player::Player(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, float scale) : GameObject(renderer, path, x, y, w, h, angle, tag, hasAnimations, scale)
{
	totalDeathTime = totalPlayerDeathTime;
	spriteOffsetX = playerSpriteOffsetX;
	spriteOffsetY = playerSpriteOffsetY;
	collissionBox.x += playerSpriteOffsetX;
	collissionBox.y += playerSpriteOffsetY;
	collissionBox.w = playerSpriteW* scale;
	collissionBox.h = playerSpriteH* scale;
	setHealth(50);
	setSpeed(5);
	spriteTime = totalSpriteTime;
	score = 0;
	spellCount = totalSpellCount;
	castingCooldown = totalCastingCooldown;
	velocity.Zero();
}

GameObject* Player::cast1(SDL_Renderer* renderer)
{
	castingCooldown = totalCastingCooldown;
	return new StraightProjectile(renderer, "assets/player/playerSpell1.png", position.x + (playerSpriteOffsetX + playerSpriteW * (flipStatus == SDL_FLIP_NONE ? 1 : -1)), position.y + playerSpriteOffsetY + 20, 32, 32, 0.0f, "Projectile", false, 10, (flipStatus == SDL_FLIP_HORIZONTAL ? -1 : 1), 1, false);
}

void Player::Update(SDL_Renderer* renderer)
{
	GameObject::Update(renderer);
	if (spriteTime > 0) spriteTime--;
	else
	{
		NextSprite(totalSpriteTime);
	}

	if (state != DEATH)
	{
		if (state == ATTACKING && srcRect.x == sheetWidth - srcRect.w)
		{
			Game::gameObjects.push_back(cast1(renderer));
			spriteTime = 0;
		}

		if (position.y < PLATFORM_HEIGHT - playerSpriteOffsetY - playerSpriteH)
		{
			velocity.y += 2;
		}


		if (position.y > PLATFORM_HEIGHT - playerSpriteOffsetY - playerSpriteH) { isJumping = false; position.y = PLATFORM_HEIGHT - playerSpriteOffsetY - playerSpriteH; velocity.y = 0; }

		if (reloadStart != 0) { if (spellCount < totalSpellCount) reloadStart--; }
		else
		{
			if (spellCount < totalSpellCount) spellCount++;
			reloadStart = totalSpellReloadTime;
		}

		//cooldown tracking
		if (castingCooldown != 0)
			castingCooldown--;

		//player movement
		if (collissionBox.x >= playerLimit && collissionBox.x <= (SCREEN_WIDTH - collissionBox.w - playerLimit))
		{
			position.x += static_cast<int> (velocity.x);
			position.y += static_cast<int> (velocity.y);
		}
		else
		{
			if (collissionBox.x < playerLimit) position.x = playerLimit - playerSpriteOffsetX;
			if (collissionBox.x > (SCREEN_WIDTH - collissionBox.w - playerLimit)) position.x = (SCREEN_WIDTH - collissionBox.w - playerSpriteOffsetX - playerLimit);
			//if (collissionBox.y < 0.0f) position.y = 0.0f;
			//if (position.y > (SCREEN_HEIGHT - collissionBox.h)) position.y = (PLATFORM_HEIGHT - collissionBox.h);
			velocity.x = 0.0f;
			velocity.y = 0.0f;
		}

		//updating destRect values
		UpdateDestRect();
		//updating collission box values
		UpdateCollissionBox();
	}
}
/*
GameObject* Player::Shoot(bool isMissile)
{
	GameObject* bullet;
	if (isMissile)
	{
		//homing missile
		bullet = new Bullet("assets/PlayerMissile.png", position.x + 16, position.y - 16, 32, 32, 1, 32, true, false, 270.0f, 1);
		missileCount--;
		Mix_PlayChannel(-1, missileSound, 0);
		reloadStart = totalReloadTime;

	}
	else
	{
		//normal bullet
		bullet = new Bullet("assets/PlayerBullet.png", position.x + 16, position.y - 16, 32, 32, 1, 96, false, false, 270.0f, 1);
		Mix_PlayChannel(-1, bulletSound, 0);
	}
	shootingCoolDown = totalShootingCoolDown;
	return bullet;
}*/

bool Player::OnCoolDown()
{
	return castingCooldown != 0;
}