#pragma once
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

enum defenderType {
	none,
	defender1,
	defender2,
	truck,
	NTULibrary,
};
enum corner {
	leftUp,
	rightUp,
	leftDown,
	rightDown,
	notCorner,
};

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
	defenderType getDefenderChosen();
	void setDefenderChosen(defenderType);
	void gameEnd();

	bool running();
	bool aDefenderChosen = false;

	corner getCorner(int);

   private:
	defenderType chosenDefender = none;
	bool isRunning;
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
};
