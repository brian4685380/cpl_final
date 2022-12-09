#include <utility>

#include "block.h"
block::block(std::pair<int, int> pos, int length, blockType type) {
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