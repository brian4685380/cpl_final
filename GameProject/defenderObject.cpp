#include "defenderObject.h"

#include "SDL_image.h"

defenderObject::defenderObject(const char *textureSheet, SDL_Renderer *ren, int x, int y, int width, int height) {
	renderer = ren;
	objTexture = IMG_LoadTexture(renderer, textureSheet);
	xpos = x;
	ypos = y;
	destRect.w = width;
	destRect.h = height;
	srcRect.w = width;
	srcRect.h = height;
}

void defenderObject::Update() {
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
}

void defenderObject::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}
