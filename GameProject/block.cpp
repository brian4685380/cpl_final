#include "block.h"

#include <utility>
block::block(const char *textureSheet, SDL_Renderer *ren, std::pair<int, int> pos, int len, blockType type) {
	renderer = ren;
	objTexture = IMG_LoadTexture(renderer, textureSheet);
	this->pos.first = pos.first;
	this->pos.second = pos.second;
	std::cout << this->pos.first << " " << this->pos.second << std::endl;
	length = len;
	std::cout << length << std::endl;
	type = type;
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

void block::Update() {
	srcRect.h = 40;
	srcRect.w = 40;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = length * pos.first;
	destRect.y = length * pos.second;
	std::cout << length << ' ' << pos.first << ' ' << pos.second << std::endl;
	destRect.w = 40;
	destRect.h = 40;
}
void block::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}
