#include <utility>

#include "block.h"
block::block(std::pair<int, int> pos, int length, blockType type) {
	this->pos = pos;
	this->length = length;
	this->type = type;
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