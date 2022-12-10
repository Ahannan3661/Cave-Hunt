#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h, float angle, string tag, bool hasAnimations, float scale)
{
	this->hasAnimations = hasAnimations;
	this->scale = scale;
	flipStatus = SDL_FLIP_NONE;
	if (hasAnimations)
	{
		char temp[200];
		memset(temp, 0, sizeof temp);
		strcpy_s(temp, sizeof temp, path);
		strcat_s(temp, sizeof temp, "/idle.png");
		textures.push_back(TextureManager::LoadTexture(renderer, temp));
		memset(temp, 0, sizeof temp);
		strcpy_s(temp, sizeof temp, path);
		strcat_s(temp, sizeof temp, "/run.png");
		textures.push_back(TextureManager::LoadTexture(renderer, temp));
		memset(temp, 0, sizeof temp);
		strcpy_s(temp, sizeof temp, path);
		strcat_s(temp, sizeof temp, "/attack.png");
		textures.push_back(TextureManager::LoadTexture(renderer, temp));
		memset(temp, 0, sizeof temp);
		strcpy_s(temp, sizeof temp, path);
		strcat_s(temp, sizeof temp, "/hit.png");
		textures.push_back(TextureManager::LoadTexture(renderer, temp));
		memset(temp, 0, sizeof temp);
		strcpy_s(temp, sizeof temp, path);
		strcat_s(temp, sizeof temp, "/death.png");
		textures.push_back(TextureManager::LoadTexture(renderer, temp));
	} 
	else
	{
		textures.push_back(TextureManager::LoadTexture(renderer, path));
	}
	state = IDLE;
	sheetWidth = textures[state]->srcRect.w;
	sheetHeight = textures[state]->srcRect.h;
	this->position.x = x*1.0f;
	this->position.y = y*1.0f;
	this->angle = angle;
	this->tag = tag;
	//if(hasTag("Smoke"))
		//SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
	srcRect.x = srcRect.y = 0;
	srcRect.w = w;
	srcRect.h = h;
	destRect.x = x;
	destRect.y = y;
	destRect.w = w * scale;
	destRect.h = h * scale;
	collissionBox = destRect;
	health = 1;
	velocity.Zero();
}

void GameObject::setState(int s)
{
	if (s < textures.size() && s >= 0)
	{
		if (state != s && state != DEATH)
		{
			if ((state == HIT && srcRect.x != sheetWidth - srcRect.w)) return;
			state = s;
			spriteTime = totalSpriteTime;
			sheetHeight = textures[state]->srcRect.h;
			sheetWidth = textures[state]->srcRect.w;
		}
	}
	else
	{
		cout << "INVALID STATE";
	}
}

void GameObject::UpdateDestRect()
{
	destRect.x = static_cast<int>(position.x);
	destRect.y = static_cast<int>(position.y);
	destRect.w = srcRect.w * scale;
	destRect.h = srcRect.h * scale;
}

void GameObject::UpdateCollissionBox()
{
	collissionBox.x = destRect.x + (spriteOffsetX*scale);
	collissionBox.y = destRect.y + (spriteOffsetY*scale);
}

GameObject::~GameObject()
{
	for (int i = 0;i < textures.size(); i++)
	{
		SDL_DestroyTexture(textures[i]->tex);
		delete textures.at(i);
		textures.erase(textures.begin() + i);
	}
}

void GameObject::Render(SDL_Renderer* renderer)
{
	//if(hasTag("Smoke"))
		//TextureManager::Draw1(texture, srcRect, destRect, angle);
	//else

	TextureManager::Draw(renderer, textures[state]->tex, srcRect, destRect, angle, flipStatus);
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderDrawRect(renderer, &collissionBox);
	//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	//SDL_RenderDrawRect(renderer, &destRect);
}

void GameObject::NextSprite(int totalTime)
{
	if ((state == ATTACKING || state == HIT) && srcRect.x == sheetWidth - srcRect.w) 
	{
		setState(IDLE); srcRect.x = 0; 
		return; 
	}
	if (!(state == DEATH && srcRect.x == sheetWidth - srcRect.w))
	{
		spriteTime = totalTime;
		srcRect.x += srcRect.w;
		srcRect.x %= sheetWidth;
	}
}