#pragma once
#include <utility>

#include "Game.h"
enum blockType {
    attackerOnIt,
    defenderOnIt,
	attackerOnly,
	defenderOnly,
};
class block {
   public:
	block(const char *textureSheet, SDL_Renderer *ren, std::pair<int, int> pos, int length, blockType type);
	~block();
	std::pair<int, int> getPos();
	int getLength();
	blockType getType();

	void Update();
	void Render();
    void setType(blockType);

   private:
	std::pair<int, int> pos;  // left top corner
	int length;
	blockType type;
	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer *renderer;
};