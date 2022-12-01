#include "GameObject.h"

#include "SDL_image.h"

GameObject::GameObject(const char *textureSheet, SDL_Renderer *ren, int x, int y) {
	renderer = ren;
	objTexture = IMG_LoadTexture(renderer, textureSheet);

	xpos = x;
	ypos = y;
}

void GameObject::Update() {
	xpos++;
	ypos++;

	srcRect.h = 512;
	srcRect.w = 512;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = 64;
	destRect.h = 64;
}

void GameObject::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}