#include "Game.h"

Game *game = nullptr;

using namespace std;

int main() {
	game = new Game();
	game->init("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}
	game->clean();
	return 0;
}