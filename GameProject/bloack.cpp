#include <utility>

#include "block.h"
block::block(const char *textureSheet, SDL_Renderer *ren, std::pair<int, int> pos, int length, blockType type) {
    renderer = ren;
	objTexture = IMG_LoadTexture(renderer, textureSheet);
	pos = pos;
	length = length;
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