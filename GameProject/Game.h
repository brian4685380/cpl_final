#pragma once
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

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
enum player {
	defenderPlayer,
	attackerPlayer,
	unassigned,
};
class Game {
   public:
	Game();
	~Game();

	void init(const char *, int, int, int, int, bool);

	SDL_Texture *resultTexture;
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
	player winner = unassigned;
	corner getCorner(int);

   private:
	defenderType chosenDefender = none;
	bool isRunning;
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
};
