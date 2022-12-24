#pragma once
#include <utility>
#include <vector>

#include "Game.h"
#include "Money.h"
#include "defender.h"
#include "Music.h"

class attackerObject;  // Forward Declartion to prevent circular dependancy

class defenderObject: public defender {
   public:
	defenderObject(SDL_Renderer *, int, int, int, int, int, od_type);
	~defenderObject();

	void O_Init_Profile(int, od_type, SDL_Renderer *);

	static int D_get_price(od_type otp) {
		switch (otp) {
			case Prof1:
				return 100;
				break;
			case Prof2:
				return 300;
				break;
			case Bike:
				return 500;
				break;
			case Library:
				return 1500;
				break;
			default:
				return 0;
				break;
		}
	}

	void Update(Money *, Money *, Music *);
	void D_Attack(vector<attackerObject *> &);
	void D_range_attack(vector<attackerObject *> &);
	void D_single_attack(vector<attackerObject *> &);
	void Render();

	int getDestX();
	int getDestY();

	// void D_single_attack(vector<attackerObject*>);

   private:
	int D_attack_count = 0;
	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer *renderer;
};
