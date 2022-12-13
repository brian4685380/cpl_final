#pragma once
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

class Game {
   public:
	Game();
	~Game();

	void init(const char *, int, int, int, int, bool);

	void handleEvents();
	void update();
	void render();
	void clean();
	void createMap();

	bool running();

   private:
	bool isRunning;
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
};
