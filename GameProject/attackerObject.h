#pragma once
#include <utility>
#include <vector>

#include "Attacker.h"
#include "Game.h"
#include "defenderObject.h"

class attackerObject: public Attacker {
   public:
	attackerObject(SDL_Renderer *, int, int, int = 0, oa_type = Attacker1);
	~attackerObject();

	void A_Init_Profile(int, oa_type, SDL_Renderer *);

	static int A_get_price(oa_type atp) {
		switch (atp) {
			case Attacker1:
				return 50;
				break;
			case Attacker2:
				return 100;
				break;
			case Attacker3:
				return 200;
				break;
			case Attacker4:
				return 500;
				break;
			default:
				return 0;
				break;
		}
	}

	void Update();
	void A_Attack(vector<defenderObject *> &);
	void A_range_attack(vector<defenderObject *> &);
	void A_single_attack(vector<defenderObject *> &);
	void Render();
	void getAttackerPath(std::vector<std::pair<int, int>>);
	void getAttackerDir(std::vector<char>);
	void setDestRectX(int);

	

   private:
	int pathIndex = 0;
	int path;
	int A_update_count = 0;
	int A_attack_count = 0;

	std::vector<char> move_dir_list;
	std::vector<std::pair<int, int>> move_pos_list;

	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer *renderer;
};