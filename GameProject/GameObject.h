#include "Game.h"

class GameObject {
   public:
	GameObject(const char *, SDL_Renderer *, int, int);
	~GameObject();

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