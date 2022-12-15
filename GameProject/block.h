#pragma once
#include <utility>

#include "Game.h"
enum blockType {
	attackerOnIt,
	defenderOnIt,
	attackerOnly,
	defenderOnly,
	defenderOption,
	defenderChosen,
};
class block {
   public:
	block(SDL_Renderer *ren, std::pair<int, int> pos, int length, blockType type);
	~block();
	std::pair<int, int> getPos();
	int getLength();
	blockType getType();

	void Update();
	void Render();
	void setType(blockType);
	void getMouseState(int, int, Uint32);
	void setChosen(bool);
	
	bool isChosen();
	bool isOcupied();

	int getDestX();
	int getDestY();

	void setOcupied(bool);
	void switchType();
	void setMouseState(Uint32);
	void setMouseX(int);
	void setMouseY(int);
	static int mouseX, mouseY;
	static Uint32 mouseState;

   private:
	bool chosen = false;
	bool ocupied = false;
	std::pair<int, int> pos;  // left top corner
	int length;
	blockType type;
	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer *renderer;
};

