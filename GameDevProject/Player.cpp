#include "Player.h"

Player::Player(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, float scale, int health) : GameObject(renderer, path, x, y, w, h, angle, tag, hasAnimations, scale, health)
{
	totalDeathTime = totalPlayerDeathTime;
	spriteOffsetX = playerSpriteOffsetX;
	spriteOffsetY = playerSpriteOffsetY;
	collissionBox.x += playerSpriteOffsetX;
	collissionBox.y += playerSpriteOffsetY;
	collissionBox.w = playerSpriteW* scale;
	collissionBox.h = playerSpriteH* scale;
	setSpeed(playerSpeed);
	spriteTime = totalSpriteTime;
	score = 0;
	spellCount = totalSpellCount;
	castingCooldown = totalCastingCooldown;
	velocity.Zero();
	healthBar->Update(collissionBox.x, collissionBox.y - 20);
	youLose = Mix_LoadWAV(YOULOSESOUND);
	spellSound = Mix_LoadWAV(PLAYERSPELLSOUND);
}

GameObject* Player::cast1(SDL_Renderer* renderer)
{
	Mix_PlayChannel(-1, spellSound, 0);
	castingCooldown = totalCastingCooldown;
	return new StraightProjectile(renderer, PLAYERSPELL, position.x + (playerSpriteOffsetX + playerSpriteW * (flipStatus == SDL_FLIP_NONE ? 1 : -1)), position.y + playerSpriteOffsetY + 20, projW, projH, 0.0f, "Projectile", false, playerProjDamage, (flipStatus == SDL_FLIP_HORIZONTAL ? -1 : 1), 1, false, projHealth);
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

		if (position.y > PLATFORM_HEIGHT - playerSpriteOffsetY - playerSpriteH) 
		{
			isJumping = false;
			position.y = PLATFORM_HEIGHT - playerSpriteOffsetY - playerSpriteH; velocity.y = 0; 
		}

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
			velocity.x = 0.0f;
			velocity.y = 0.0f;
		}

		//updating destRect values
		UpdateDestRect();
		//updating collission box values
		UpdateCollissionBox();
	}
	else
	{
		if (!soundPlayed)
		{
			Mix_PlayChannel(-1, youLose, 0);
			soundPlayed = true;
		}
	}
}

bool Player::OnCoolDown()
{
	return castingCooldown != 0;
}