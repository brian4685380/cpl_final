#include "Game.h"

class attackerObject {
   public:
	attackerObject(const char *, SDL_Renderer *, int, int);
	~attackerObject();

	void Update();
	void Render();

   private:
	int cnt = 0;
	int xpos;
	int ypos;

	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer *renderer;
};