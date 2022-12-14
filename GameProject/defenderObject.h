#pragma once
#include <utility>
#include <vector>

#include "Game.h"
#include "defender.h"

class defenderObject {
   public:
	defenderObject(const char *, SDL_Renderer *, int, int);
	~defenderObject();

	void Update();
	void Render();
	

   private:
	int xpos;
	int ypos;

	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer *renderer;
};