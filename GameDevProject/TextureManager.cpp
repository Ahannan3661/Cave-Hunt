#include "TextureManager.h"

texStruct* TextureManager::LoadTexture(SDL_Renderer* renderer, const char* texture)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	texStruct* temp = new texStruct();
	temp->tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	temp->srcRect.w = tempSurface->clip_rect.w;
	temp->srcRect.h = tempSurface->clip_rect.h;
	SDL_FreeSurface(tempSurface);

	return temp;
}

void TextureManager::Draw(SDL_Renderer* renderer, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, float angle, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, tex, &src, &dest, angle, NULL, flip);
}

void TextureManager::DrawBG(SDL_Renderer* renderer, SDL_Texture* tex, SDL_Rect dest)
{
	SDL_RenderCopy(renderer, tex, NULL, &dest);
}

void TextureManager::Draw1(SDL_Renderer* renderer, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, float angle)
{
	SDL_Point* c = new SDL_Point();
	c->x = dest.w / 2;
	c->y = 0;
	SDL_RenderCopyEx(renderer, tex, &src, &dest, angle, c, SDL_FLIP_NONE);
}
