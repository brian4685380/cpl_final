#include "block.h"

#include <utility>

#include "SDL.h"
block::block(const char *textureSheet, SDL_Renderer *ren, std::pair<int, int> pos, int len, blockType block_type) {
	renderer = ren;
	objTexture = IMG_LoadTexture(renderer, textureSheet);
	this->pos.first = pos.first;
	this->pos.second = pos.second;
	length = len;
	type = block_type;
	std::cout << type << std::endl;
	srcRect.h = length;
	srcRect.w = length;
	destRect.h = length;
	destRect.w = length;
}
block::~block() {}
std::pair<int, int> block::getPos() {
	return pos;
}
int block::getLength() {
	return length;
}
blockType block::getType() {
	return type;
}
void block::setType(blockType newType) {
	type = newType;
	if (type == attackerOnly)
		objTexture = IMG_LoadTexture(renderer, "assets/Blocks/grass_stone.png");
	if (type == defenderOnly)
		objTexture = IMG_LoadTexture(renderer, "assets/Blocks/redclay_stone.png");
	if (type == attackerOnIt)
		objTexture = IMG_LoadTexture(renderer, "assets/Blocks/grass_highlight.png");
	if (type == defenderOnIt)
		objTexture = IMG_LoadTexture(renderer, "assets/Blocks/redclay_highlight.png");
}

void block::getMouseState(int x, int y, Uint32 state) {
	mouseX = x;
	mouseY = y;
	mouseState = state;
}

void block::Update() {
	srcRect.h = 40;
	srcRect.w = 40;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = length * pos.first;
	destRect.y = length * pos.second;
	destRect.w = 40;
	destRect.h = 40;
	if (mouseX - destRect.x < 40 && mouseX - destRect.x >= 0 && mouseY - destRect.y < 40 && mouseY - destRect.y >= 0) {
		if (type == attackerOnly)
			objTexture = IMG_LoadTexture(renderer, "assets/Blocks/grass_highlight.png");
		if (type == defenderOnly)
			objTexture = IMG_LoadTexture(renderer, "assets/Blocks/redclay_highlight.png");
	} else {
		if (type == attackerOnly)
			objTexture = IMG_LoadTexture(renderer, "assets/Blocks/grass_stone.png");
		if (type == defenderOnly)
			objTexture = IMG_LoadTexture(renderer, "assets/Blocks/redclay_stone.png");
	}
}
void block::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}
