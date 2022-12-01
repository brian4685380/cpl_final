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

	bool running();

   private:
	int cnt = 0;
	bool isRunning;
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
};