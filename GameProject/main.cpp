#include "Game.h" 
#include "Start.h"
Game *game = nullptr;
Start *start = nullptr;
using namespace std;
int main() {
	const int FPS = 120;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	start = new Start();
	start->init("PionEEr", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, false);
	cout << "init success" << endl;
	while (start->running()) {
		frameStart = SDL_GetTicks();

		start->handleEvents();
		start->update();
		start->render();

		// Limiting frame rate
		// prevent too object from moving too fast
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}  // prevent too object from moving too fast
	}
	game = new Game();
	game->init("PionEEr", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, false);
	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		// Limiting frame rate
		// prevent too object from moving too fast
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}  // prevent too object from moving too fast
	}
	game->clean();
	return 0;
}