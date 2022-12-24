#include "attackerObject.h"
#include "SDL_image.h"
#include <cmath>


// Constructor
attackerObject::attackerObject(SDL_Renderer *ren, int x, int y, int id, oa_type atp) {
	//cout << "create attacker" << id << endl;
	A_Init_Profile(id, atp, ren);
	//renderer = ren;
	//objTexture = IMG_LoadTexture(renderer, "assets/Attackers/student1.png");
	xpos = x;
	ypos = y;
	block_xpos = 0;
	block_ypos = 13;	//block_pos initialize to (0,13)
	pathIndex = 0;
	A_update_count = 0;
	A_attack_count = 0;
}

attackerObject:: ~attackerObject(){};

void attackerObject:: A_Init_Profile(int id, oa_type atp, SDL_Renderer *ren){
	//cout << "INIT Attacker " << id << endl;
	renderer = ren;
	switch(atp){
		case Attacker1:
			objTexture = IMG_LoadTexture(renderer, "assets/Attackers/student1.png");
			Oa_type = Attacker1;
			A_id = id;
			A_v = 1;
			A_heart = 100;
			A_attack = 10;
			A_attack_type = a_Single;
			A_attack_range = 2;
			break;
		case Attacker2:
			objTexture = IMG_LoadTexture(renderer, "assets/Attackers/student2.png");
			Oa_type = Attacker2;
			A_id = id;
			A_v = 2;
			A_heart = 150;
			A_attack = 10;
			A_attack_type = a_Range;
			A_attack_range = 2;
			break;
		case Attacker3:
			objTexture = IMG_LoadTexture(renderer, "assets/Attackers/student3.png");
			Oa_type = Attacker3;
			A_id = id;
			A_v = 4;
			A_heart = 600;
			A_attack = 8;
			A_attack_type = a_Single;
			A_attack_range = 2;
			break;
		case Attacker4:
			objTexture = IMG_LoadTexture(renderer, "assets/Attackers/student4.png");
			Oa_type = Attacker4;
			A_id = id;
			A_v = 1;
			A_heart = 1000;
			A_attack = 10;
			A_attack_type = a_Range;
			A_attack_range = 3;
			break;
	}
	
	return;
}

void attackerObject::Update() {

	// Dead
	if (A_is_dead()) {
		// // Destroy the texture
		// SDL_DestroyTexture(objTexture);
		// // Destroy the texture
		// SDL_RenderClear(renderer);
		destRect.x = 750;
		return;
	}
	if (pathIndex == move_pos_list.size() - 1) {
		//ATTACK BL BUILDING
		
		//destRect.x = -100;
		destRect.x = 750;
		return;
	}

	// Render setting
	int imageLength = 40;

	srcRect.h = 40;
	srcRect.w = 40;
	srcRect.x = 0;
	srcRect.y = 0;


	// Moving
	A_update_count++;
	if(A_update_count >= 4){
		A_update_count = 0;
		if (move_dir_list[pathIndex] == 'U')
			ypos -= A_v;
		if (move_dir_list[pathIndex] == 'D')
			ypos += A_v;
		if (move_dir_list[pathIndex] == 'L')
			xpos -= A_v;
		if (move_dir_list[pathIndex] == 'R')
			xpos += A_v;
		if (xpos % 40 == 0 && ypos % 40 == 0){
			pathIndex++;
		}

		block_xpos = max((xpos + 20) / 40, 0);	//must positive
		block_ypos = max((ypos + 20) / 40, 0);
			
		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = 40;
		destRect.h = 40;
	}
	

}

void attackerObject::A_range_attack(vector<defenderObject *> & defender_list){
	if(defender_list.empty()) return;
	
	for(auto &i: defender_list){
		if(i->D_is_dead()) continue;

		switch(i->D_get_type()){
			case Prof1:
			case Prof2:
				//cout << "x : " << i->D_block_xpos_get() << " - " <<block_xpos << " y : " << i->D_block_ypos_get() << " - " << block_ypos << endl;
				if(abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) <= A_attack_range){
					//cout << "attacker " << A_id << " range attack !" << endl;
					i->D_heart_minus(A_attack);	//A_attack = A's damage, A_Attack is a function
				}
				break;
			case Bike:
				if((abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) <= A_attack_range) ||
					(abs(i->D_block_xpos_get() + 1 - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) <= A_attack_range)){
					//cout << "attacker " << A_id << " range attack !" << endl;
					i->D_heart_minus(A_attack);	//A_attack = A's damage, A_Attack is a function
				}
				break;
			case Library:
				if((abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) <= A_attack_range) ||
					(abs(i->D_block_xpos_get() + 1 - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) <= A_attack_range) ||
					(abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() + 1 - block_ypos) <= A_attack_range) ||
					(abs(i->D_block_xpos_get() + 1 - block_xpos) + abs(i->D_block_ypos_get() + 1 - block_ypos) <= A_attack_range)){
					//cout << "attacker " << A_id << " range attack !" << endl;
					i->D_heart_minus(A_attack);	//A_attack = A's damage, A_Attack is a function
				}
				break;
			case Home:
				if((abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) <= 1) ||
				 	(abs(i->D_block_xpos_get() + 1 - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) <= 1) ||
					(abs(i->D_block_xpos_get() + 2 - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) <= 1) ||
					(abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() + 1 - block_ypos) <= 1) ||
					(abs(i->D_block_xpos_get() + 1 - block_xpos) + abs(i->D_block_ypos_get() + 1 - block_ypos) <= 1) ||
					(abs(i->D_block_xpos_get() + 2 - block_xpos) + abs(i->D_block_ypos_get() + 1 - block_ypos) <= 1)){
					//cout << "attacker " << A_id << " range attack !" << endl;
					i->D_heart_minus(A_attack);	//A_attack = A's damage, A_Attack is a function
					A_heart_set(0);		// Attackers can only attack Home once
				}
				break;
			default:
				break;

		}
	}
}

void attackerObject::A_single_attack(vector<defenderObject *> & defender_list){
	if(defender_list.empty()) return;

	int A_min_dis_to_D = INT_MAX;
	defenderObject* A_closest_D = defender_list[0];

	for(auto &i: defender_list){
		if(i->D_is_dead()) continue;

		switch(i->D_get_type()){
			case Prof1:
			case Prof2:
				if(abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) < A_min_dis_to_D){
					A_min_dis_to_D = abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() - block_ypos);
					A_closest_D = i;
				}
				break;

			case Bike:
				if(abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) < A_min_dis_to_D){
					A_min_dis_to_D = abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() - block_ypos);
					A_closest_D = i;
				}

				if(abs(i->D_block_xpos_get() + 1 - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) < A_min_dis_to_D){
					A_min_dis_to_D = abs(i->D_block_xpos_get() + 1 - block_xpos) + abs(i->D_block_ypos_get() - block_ypos);
					A_closest_D = i;
				}
				break;

			case Library:
				if(abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) < A_min_dis_to_D){
					A_min_dis_to_D = abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() - block_ypos);
					A_closest_D = i;
				}
				if(abs(i->D_block_xpos_get() + 1 - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) < A_min_dis_to_D){
					A_min_dis_to_D = abs(i->D_block_xpos_get() + 1 - block_xpos) + abs(i->D_block_ypos_get() - block_ypos);
					A_closest_D = i;
				}
				if(abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() + 1 - block_ypos) < A_min_dis_to_D){
					A_min_dis_to_D = abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() + 1 - block_ypos);
					A_closest_D = i;
				}
				if(abs(i->D_block_xpos_get() + 1 - block_xpos) + abs(i->D_block_ypos_get() + 1 - block_ypos) < A_min_dis_to_D){
					A_min_dis_to_D = abs(i->D_block_xpos_get() + 1 - block_xpos) + abs(i->D_block_ypos_get() + 1 - block_ypos);
					A_closest_D = i;
				}	
				break;

			case Home:
				if(abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) <= A_min_dis_to_D){
					A_min_dis_to_D = abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() - block_ypos);
					A_closest_D = i;
				}
				if(abs(i->D_block_xpos_get() + 1 - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) <= A_min_dis_to_D){
					A_min_dis_to_D = abs(i->D_block_xpos_get() + 1 - block_xpos) + abs(i->D_block_ypos_get() - block_ypos);
					A_closest_D = i;
				}
				if(abs(i->D_block_xpos_get() + 2 - block_xpos) + abs(i->D_block_ypos_get() - block_ypos) <= A_min_dis_to_D){
					A_min_dis_to_D = abs(i->D_block_xpos_get() + 2 - block_xpos) + abs(i->D_block_ypos_get() - block_ypos);
					A_closest_D = i;
				}
				if(abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() + 1 - block_ypos) <= A_min_dis_to_D){
					A_min_dis_to_D = abs(i->D_block_xpos_get() - block_xpos) + abs(i->D_block_ypos_get() + 1 - block_ypos);
					A_closest_D = i;
				}
				if(abs(i->D_block_xpos_get() + 1 - block_xpos) + abs(i->D_block_ypos_get() + 1 - block_ypos) <= A_min_dis_to_D){
					A_min_dis_to_D = abs(i->D_block_xpos_get() + 1 - block_xpos) + abs(i->D_block_ypos_get() + 1 - block_ypos);
					A_closest_D = i;
				}
				if(abs(i->D_block_xpos_get() + 2 - block_xpos) + abs(i->D_block_ypos_get() + 1 - block_ypos) <= A_min_dis_to_D){
					A_min_dis_to_D = abs(i->D_block_xpos_get() + 2 - block_xpos) + abs(i->D_block_ypos_get() + 1 - block_ypos);
					A_closest_D = i;
				}
				break;

			default:
				break;
		}
	}
	if(A_closest_D->D_is_dead()) return;	// prevent A_closest_D default value (defender_list[0]) being attacked when it is dead
	if(A_closest_D->D_get_type() == Home){
		if(A_min_dis_to_D <= 1){
			A_closest_D->D_heart_minus(A_attack);	//A_attack = A's damage, A_Attack is a function
			A_heart_set(0);		// Attackers can only attack Home once
		}
	}
	else{
		if(A_min_dis_to_D <= A_attack_range){
			A_closest_D->D_heart_minus(A_attack);	//A_attack = A's damage, A_Attack is a function
		}
	}
}

void attackerObject::A_Attack(vector<defenderObject *> & defender_list){
	A_attack_count++;
	if(A_attack_count % 4 == 0){
		A_attack_count = 0;
		if(A_is_dead()){	
				return;
			}
			switch(A_attack_type){
				case a_Single:
					this->A_single_attack(defender_list);
					break;
				case a_Range:
					this->A_range_attack(defender_list);
					break;
				default:
					break;
			}
			return;
	}
	
}


void attackerObject::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

void attackerObject::getAttackerPath(std::vector<std::pair<int, int>> path) {
	move_pos_list.resize(path.size());
	for (int i = 0; i < path.size(); i++) {
		move_pos_list[i].first = path[i].first;
		move_pos_list[i].second = path[i].second;
	}
}

void attackerObject::getAttackerDir(std::vector<char> dir) {
	move_dir_list.resize(dir.size());
	for (int i = 0; i < dir.size(); i++) {
		move_dir_list[i] = dir[i];
	}
}

void attackerObject::setDestRectX(int x) {
	destRect.x = x;
}