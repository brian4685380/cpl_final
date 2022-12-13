#pragma once
#include <utility>
#include <vector>

#include "Game.h"

class attackerObject {
   public:
	attackerObject(const char *, SDL_Renderer *, int, int);
	~attackerObject();

	void Update();
	void Render();
	void getAttackerPath(std::vector<std::pair<int, int>>);
	void getAttackerDir(std::vector<char>);

   private:
	int pathIndex = 0;
	int xpos;
	int ypos;
	int path;
	std::vector<char> move_dir_list;
	std::vector<std::pair<int, int>> move_pos_list;

	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer *renderer;
};