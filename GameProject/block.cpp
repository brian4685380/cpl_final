#include "block.h"

#include <utility>

#include "Game.h"
#include "SDL.h"

Uint32 block::mouseState = 0;
int block::mouseX = 0;
int block::mouseY = 0;

block::block(SDL_Renderer *ren, std::pair<int, int> pos, int len, blockType block_type) {
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
	srcRect.x = 0;
	// std::cout << type << std::endl;
	switchType();
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
	switchType();
}

// void block::getMouseState(int x, int y, Uint32 state) {
// 	mouseX = x;
// 	mouseY = y;
// 	mouseState = state;
// }

void block::Update() {
	if (type == defenderOption && chosen) {
		setType(defenderChosen);
	}
	srcRect.h = 40;
	srcRect.w = 40;
	switchType();
	destRect.x = length * pos.first;
	destRect.y = length * pos.second;
	destRect.w = 40;
	destRect.h = 40;
	// if (mouseX - destRect.x < 40 && mouseX - destRect.x >= 0 && mouseY - destRect.y < 40 && mouseY - destRect.y >= 0) {
	// 	if (type == defenderOption) {
	// 		if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
	// 			std::cout << "clicked" << std::endl;
	// 			type = defenderChosen;
	// 			setChosen(true);
	// 		}
	// 	}
	// }
}
void block::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

bool block::isChosen() {
	return chosen;
}

bool block::isOcupied() {
	return ocupied;
}

void block::setOcupied(bool ocup) {
	ocupied = ocup;
}
void block::setChosen(bool choose) {
	chosen = choose;
}

int block::getDestX() {
	return destRect.x;
}
int block::getDestY() {
	return destRect.y;
}

void block::setMouseState(Uint32 state) {
	block::mouseState = state;
}
void block::setMouseX(int x) {
	block::mouseX = x;
}
void block::setMouseY(int y) {
	block::mouseY = y;
}

void block::switchType() {
	switch (type) {
		case attackerOnly:
			srcRect.y = 0;
			break;
		case attackerOnIt:
			srcRect.y = 40;
			break;
		case defenderOnly:
			srcRect.y = 120;
			break;
		case defenderOnIt:
			srcRect.y = 160;
			break;
		case defenderOption:
			srcRect.y = 120;
			break;
		case defenderChosen:
			srcRect.y = 160;
			break;
	}
}