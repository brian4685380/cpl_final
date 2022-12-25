#include "SDL.h"

class Start {
   public:
	Start();
	~Start();

	void init(const char *, int, int, int, int, bool);

	void handleEvents();
	void update();
	void render();

	bool running();
	bool showingCover = 1;

   private:
	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
	bool isRunning = true;
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
};
