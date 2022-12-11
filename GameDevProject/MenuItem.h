#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>

//Each item in main menu is created via this struct
struct MenuItem
{
	const char* label;
	SDL_Rect pos;
	SDL_Texture* texture;
	bool isHighlighted = false;
	SDL_Color color = { 0,0,0 };
	int rows;
	int cols;

	//Menu Item is drawn using 3 sprites to make a complete box depending on the size of its contents
	void DrawMenuItem(SDL_Renderer* renderer, SDL_Texture* buttonCorner, SDL_Texture* buttonEdge, SDL_Texture* buttonMiddle)
	{
		for (int j = 0; j < rows; j++)
		{
			for (int k = 0; k < cols; k++)
			{
				SDL_Rect dest;
				if (j == 0 && k == 0)
				{
					dest.x = pos.x;
					dest.y = pos.y;
					dest.w = buttonSpriteW;
					dest.h = buttonSpriteH;
					SDL_RenderCopyEx(renderer, buttonCorner, NULL, &dest, 180.0f, NULL, SDL_FLIP_NONE);
				}
				else if (j == rows - 1 && k == cols - 1)
				{
					dest.x = pos.x + buttonSpriteW * j;
					dest.y = pos.y + buttonSpriteH * k;
					dest.w = buttonSpriteW;
					dest.h = buttonSpriteH;
					SDL_RenderCopyEx(renderer, buttonCorner, NULL, &dest, 0.0f, NULL, SDL_FLIP_NONE);
				}
				else if (j == rows - 1 && k == 0)
				{
					dest.x = pos.x;
					dest.y = pos.y + buttonSpriteH * j;
					dest.w = buttonSpriteW;
					dest.h = buttonSpriteH;
					SDL_RenderCopyEx(renderer, buttonCorner, NULL, &dest, 90.0f, NULL, SDL_FLIP_NONE);
				}
				else if (j == 0 && k == cols - 1)
				{
					dest.x = pos.x + buttonSpriteW * k;
					dest.y = pos.y;
					dest.w = buttonSpriteW;
					dest.h = buttonSpriteH;
					SDL_RenderCopyEx(renderer, buttonCorner, NULL, &dest, -90.0f, NULL, SDL_FLIP_NONE);
				}
				else if (j == 0 && k != 0 && k != cols - 1)
				{
					dest.x = pos.x + buttonSpriteW * k;
					dest.y = pos.y;
					dest.w = buttonSpriteW;
					dest.h = buttonSpriteH;
					SDL_RenderCopyEx(renderer, buttonEdge, NULL, &dest, 180.0f, NULL, SDL_FLIP_NONE);
				}
				else if (j == rows - 1 && k != 0 && k != cols - 1)
				{
					dest.x = pos.x + buttonSpriteW * k;
					dest.y = pos.y + buttonSpriteH * j;
					dest.w = buttonSpriteW;
					dest.h = buttonSpriteH;
					SDL_RenderCopyEx(renderer, buttonEdge, NULL, &dest, 0.0f, NULL, SDL_FLIP_NONE);
				}
				else if (j != 0 && j != rows - 1 && k == 0)
				{
					dest.x = pos.x;
					dest.y = pos.y + buttonSpriteH * j;
					dest.w = buttonSpriteW;
					dest.h = buttonSpriteH;
					SDL_RenderCopyEx(renderer, buttonEdge, NULL, &dest, 90.0f, NULL, SDL_FLIP_NONE);
				}
				else if (j != 0 && j != rows - 1 && k == cols - 1)
				{
					dest.x = pos.x + buttonSpriteW * k;
					dest.y = pos.y + buttonSpriteH * j;
					dest.w = buttonSpriteW;
					dest.h = buttonSpriteH;
					SDL_RenderCopyEx(renderer, buttonEdge, NULL, &dest, -90.0f, NULL, SDL_FLIP_NONE);
				}
				else
				{
					dest.x = pos.x + buttonSpriteW * k;
					dest.y = pos.y + buttonSpriteH * j;
					dest.w = buttonSpriteW;
					dest.h = buttonSpriteH;
					SDL_RenderCopyEx(renderer, buttonMiddle, NULL, &dest, 0.0f, NULL, SDL_FLIP_NONE);
				}

			}
		}

		SDL_Rect menuItemDest = pos;

		menuItemDest.x += (rows * buttonSpriteW - pos.w) / 2;
		menuItemDest.y += (cols * buttonSpriteH - pos.h) / 2;
		SDL_RenderCopy(renderer, texture, NULL, &menuItemDest);
	}

	//Change menu Item's color when the mouse does/doesn't hover over it
	void HighLight(SDL_Renderer* renderer, bool shouldHighlight, TTF_Font* font)
	{
		isHighlighted = shouldHighlight;
		color = colors[(shouldHighlight ? 1 : 0)];
		SDL_Surface* tempSurface = TTF_RenderText_Solid(font, label, color);
		SDL_DestroyTexture(texture);
		texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		tempSurface = nullptr;
	}
};
