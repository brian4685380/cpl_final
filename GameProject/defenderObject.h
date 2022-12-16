#pragma once
#include <utility>
#include <vector>

#include "Game.h"
#include "defender.h"
class attackerObject;	//Forward Declartion to prevent circular dependancy

class defenderObject : public defender{
   public:
	defenderObject(SDL_Renderer *, int, int, int, int, int, od_type);
	~defenderObject();

	void O_Init_Profile(int, od_type, SDL_Renderer *);

	void Update();
	void Render();

	//void D_range_attack(vector<attackerObject*>);
	//void D_single_attack(vector<attackerObject*>);
	

   private:

	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer *renderer;
};