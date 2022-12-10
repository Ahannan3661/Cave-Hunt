#pragma once
#include <SDL.h>
#include <SDL_image.h>

struct texStruct
{
	SDL_Texture* tex;
	SDL_Rect srcRect;
};

class TextureManager
{
public:
	static texStruct* LoadTexture(SDL_Renderer*, const char*);
	static void DrawBG(SDL_Renderer*, SDL_Texture*, SDL_Rect);
	static void Draw(SDL_Renderer*, SDL_Texture*, SDL_Rect, SDL_Rect, float, SDL_RendererFlip);
	static void Draw1(SDL_Renderer*, SDL_Texture*, SDL_Rect, SDL_Rect, float);
};