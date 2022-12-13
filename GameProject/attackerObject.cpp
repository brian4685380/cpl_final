#include "attackerObject.h"

#include "SDL_image.h"

attackerObject::attackerObject(const char *textureSheet, SDL_Renderer *ren, int x, int y) {
	renderer = ren;
	objTexture = IMG_LoadTexture(renderer, textureSheet);
	xpos = x;
	ypos = y;
	pathIndex = 0;
}

void attackerObject::Update() {
	int imageLength = 40;

	srcRect.h = 40;
	srcRect.w = 40;
	srcRect.x = 0;
	srcRect.y = 0;

	if (move_dir_list[pathIndex] == 'U')
		ypos -= 1;
	if (move_dir_list[pathIndex] == 'D')
		ypos += 1;
	if (move_dir_list[pathIndex] == 'L')
		xpos -= 1;
	if (move_dir_list[pathIndex] == 'R')
		xpos += 1;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = 40;
	destRect.h = 40;
	if (xpos % 40 == 0 && ypos % 40 == 0)
		pathIndex++;
}

void attackerObject::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

void attackerObject::getAttackerPath(std::vector<std::pair<int, int>> path) {
	move_pos_list.resize(path.size());
	for (int i = 0; i < path.size(); i++) {
		move_pos_list[i].first = path[i].first;
		move_pos_list[i].second = path[i].second;
	}
}

void attackerObject::getAttackerDir(std::vector<char> dir) {
	move_dir_list.resize(dir.size());
	for (int i = 0; i < dir.size(); i++) {
		move_dir_list[i] = dir[i];
	}
}