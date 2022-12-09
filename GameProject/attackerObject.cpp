#include "attackerObject.h"

#include "SDL_image.h"

attackerObject::attackerObject(const char *textureSheet, SDL_Renderer *ren, int x, int y) {
	renderer = ren;
	objTexture = IMG_LoadTexture(renderer, textureSheet);

	xpos = x;
	ypos = y;
}

void attackerObject::Update() {
	int imageLength = 40;

	srcRect.h = 40;
	srcRect.w = 40;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = 40;
	destRect.h = 40;
}

void attackerObject::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}