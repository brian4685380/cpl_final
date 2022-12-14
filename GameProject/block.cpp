#include "block.h"

#include <utility>

#include "SDL.h"
block::block(const char *textureSheet, SDL_Renderer *ren, std::pair<int, int> pos, int len, blockType block_type) {
	renderer = ren;
	objTexture = IMG_LoadTexture(renderer, "assets/Blocks/blocks.png");
	this->pos.first = pos.first;
	this->pos.second = pos.second;
	length = len;
	type = block_type;
	srcRect.h = length;
	srcRect.w = length;
	destRect.h = length;
	destRect.w = length;

	std::cout << type << std::endl;
	switch (type) {
		case attackerOnly:
			srcRect.x = 0;
			srcRect.y = 0;
			break;

		case attackerOnIt:
			srcRect.x = 0;
			srcRect.y = 40;
			break;
		case defenderOnly:
			srcRect.x = 0;
			srcRect.y = 120;
			break;
		case defenderOnIt:
			srcRect.x = 0;
			srcRect.y = 160;
			break;
	}
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
	switch (type) {
		case attackerOnly:
			srcRect.x = 0;
			srcRect.y = 0;
			break;

		case attackerOnIt:
			srcRect.x = 0;
			srcRect.y = 40;
			break;
		case defenderOnly:
			srcRect.x = 0;
			srcRect.y = 120;
			break;
		case defenderOnIt:
			srcRect.x = 0;
			srcRect.y = 160;
			break;
	}
}

void block::getMouseState(int x, int y, Uint32 state) {
	mouseX = x;
	mouseY = y;
	mouseState = state;
}

void block::Update() {
	srcRect.h = 40;
	srcRect.w = 40;
	switch (type) {
		case attackerOnly:
			srcRect.x = 0;
			srcRect.y = 0;
			break;

		case attackerOnIt:
			srcRect.x = 0;
			srcRect.y = 40;
			break;
		case defenderOnly:
			srcRect.x = 0;
			srcRect.y = 120;
			break;
		case defenderOnIt:
			srcRect.x = 0;
			srcRect.y = 160;
			break;
	}
	destRect.x = length * pos.first;
	destRect.y = length * pos.second;
	destRect.w = 40;
	destRect.h = 40;
	if (mouseX - destRect.x < 40 && mouseX - destRect.x >= 0 && mouseY - destRect.y < 40 && mouseY - destRect.y >= 0) {
		if (type == attackerOnly)
			setType(attackerOnIt);
		if (type == defenderOnly)
			setType(defenderOnIt);
	} else {
		if (type == attackerOnIt)
			setType(attackerOnly);
		if (type == defenderOnIt)
			setType(defenderOnly);
	}
}
void block::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}
