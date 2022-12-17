#pragma once
#include "defenderObject.h"
#include "attackerObject.h"
#include "SDL_image.h"
#include <cmath>

defenderObject::defenderObject(SDL_Renderer *ren, int x, int y, int w, int h, int id, od_type otp) {
	
	O_Init_Profile(id, otp, ren);
	xpos = x;
	ypos = y;
	width = w;
	height = h;
	block_width = w / 40;
	block_height = h / 40;
	block_xpos = x / 40;
	block_ypos = y / 40;
	destRect.w = width;
	destRect.h = height;
	srcRect.w = width;
	srcRect.h = height;
}

defenderObject:: ~defenderObject(){};

void defenderObject:: O_Init_Profile(int id, od_type otp, SDL_Renderer *ren){
	cout << "INIT Defender " << id << endl;
	renderer = ren;
	orientation = false;
	switch(otp){
		case Prof1:
			objTexture = IMG_LoadTexture(renderer, "assets/Defender/defender1.png");
			Od_type = Prof1;
			D_id = id;
			D_heart = 1000;
			D_attack = 1000;
		    D_attack_type = d_Single;
			D_attack_radius = 2;
            break;

        case Prof2:
			objTexture = IMG_LoadTexture(renderer, "assets/Defender/defender2.png");
			Od_type = Prof2;
			D_id = id;
			D_heart = 200;
			D_attack = 1000;
		    D_attack_type = d_Single;
			D_attack_radius = 3;
            break;

        case Bike:
			D_id = id;
			objTexture = IMG_LoadTexture(renderer, "assets/Defender/truck.png");
			Od_type = Bike;
			D_id = id;
			D_heart = 300;
			D_attack = 1000;
		    D_attack_type = d_Single;
			D_attack_radius = 2;
            break;

        case Library:
			D_id = id;
			objTexture = IMG_LoadTexture(renderer, "assets/Defender/NTULibrary.png");
			Od_type = Library;
			D_id = id;
			D_heart = 400;
			D_attack = 1000;
		    D_attack_type = d_Single;
			D_attack_radius = 2;
            break;

        case Home:
			D_id = id;
			objTexture = IMG_LoadTexture(renderer, "assets/Defender/BL_building_hollow.png");
			Od_type = Home;
			D_id = id;
			D_heart = 500;
			D_attack = 10;
		    D_attack_type = d_Single;
			D_attack_radius = 5;
            break;
	}
}

void defenderObject::Update() {
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;

	if(D_is_dead()){
		destRect.x = 750;
		return;
	}
}

void defenderObject::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}


void defenderObject::D_range_attack(vector<attackerObject*> & attacker_list)
{
	switch(Od_type){
		case Prof1:
		case Prof2:
			for (auto &a_idx: attacker_list){
				if (a_idx->A_is_dead()) continue;
				bool D_attack_finished = false;
				// for (int i = max(0, block_xpos - D_attack_radius); i < min(18, block_xpos + block_width + D_attack_radius); i++){
				//     for (int j = max (0, block_ypos - D_attack_radius); j < min(14, block_ypos + block_height + D_attack_radius); j++){ 
				// 		if (i == a_idx->A_block_xpos_get() && j == a_idx->A_block_ypos_get()){
				// 			a_idx->A_heart_minus(D_attack);
				// 			D_attack_finished = true;
				// 			break;
				// 		}	
				//     }
				// 	if(D_attack_finished)	break;
				// }
				for (int i = max(0, block_xpos - D_attack_radius); i < min(18, block_xpos + block_width + D_attack_radius); i++){
					for(int j = max(0, block_ypos - (D_attack_radius - abs(block_xpos - i))); j < min(18, block_ypos + block_height + (D_attack_radius - abs(block_xpos - i))); j++){
						//cout << i << " " << j << endl;
						if (i == a_idx->A_block_xpos_get() && j == a_idx->A_block_ypos_get()){
							a_idx->A_heart_minus(D_attack);
							D_attack_finished = true;
							break;
						}	
					}
					if(D_attack_finished)	break;
				}
			}
			break;
		case Bike:
			for (auto &a_idx: attacker_list){
				if (a_idx->A_is_dead()) continue;
				bool D_attack_finished = false;

				for (int i = max(0, block_xpos - D_attack_radius); i <= block_xpos; i++){
					for(int j = max(0, block_ypos - (D_attack_radius - abs(block_xpos - i))); j < min(18, block_ypos + block_height + (D_attack_radius - abs(block_xpos - i))); j++){
						//cout << i << " " << j << endl;
						if (i == a_idx->A_block_xpos_get() && j == a_idx->A_block_ypos_get()){
							a_idx->A_heart_minus(D_attack);
							D_attack_finished = true;
							break;
						}	
					}
					if(D_attack_finished)	break;
				}

				if(D_attack_finished)	continue;

				for (int i = block_xpos + 1; i < min(18, block_xpos + block_width + D_attack_radius); i++){
					for(int j = max(0, block_ypos - (D_attack_radius - abs((block_xpos + 1) - i))); j < min(18, block_ypos + block_height + (D_attack_radius - abs((block_xpos + 1) - i))); j++){
						//cout << i << " " << j << endl;
						if (i == a_idx->A_block_xpos_get() && j == a_idx->A_block_ypos_get()){
							a_idx->A_heart_minus(D_attack);
							D_attack_finished = true;
							break;
						}	
					}
					if(D_attack_finished)	break;
				}

			}
			break;
		case Library:
			for (auto &a_idx: attacker_list){
				if (a_idx->A_is_dead()) continue;
				bool D_attack_finished = false;

				for (int i = max(0, block_xpos - D_attack_radius); i <= block_xpos; i++){
					for(int j = max(0, block_ypos - (D_attack_radius - abs(block_xpos - i))); j <= block_ypos; j++){
						cout << i << " " << j << endl;
						if (i == a_idx->A_block_xpos_get() && j == a_idx->A_block_ypos_get()){
							a_idx->A_heart_minus(D_attack);
							D_attack_finished = true;
							break;
						}	
					}
					if(D_attack_finished)	break;
					for(int j = block_ypos + 1; j < min(18, block_ypos + block_height + (D_attack_radius - abs(block_xpos - i))); j++){
						cout << i << " " << j << endl;
						if (i == a_idx->A_block_xpos_get() && j == a_idx->A_block_ypos_get()){
							a_idx->A_heart_minus(D_attack);
							D_attack_finished = true;
							break;
						}	
					}
					if(D_attack_finished)	break;
				}

				if(D_attack_finished)	continue;

				for (int i = block_xpos + 1; i < min(18, block_xpos + block_width + D_attack_radius); i++){
					for(int j = max(0, block_ypos - (D_attack_radius - abs((block_xpos + 1) - i))); j <= block_ypos; j++){
						cout << i << " " << j << endl;
						if (i == a_idx->A_block_xpos_get() && j == a_idx->A_block_ypos_get()){
							a_idx->A_heart_minus(D_attack);
							D_attack_finished = true;
							break;
						}	
					}
					if(D_attack_finished)	break;
					for(int j = block_ypos + 1; j < min(18, block_ypos + block_height + (D_attack_radius - abs((block_xpos + 1) - i))); j++){
						cout << i << " " << j << endl;
						if (i == a_idx->A_block_xpos_get() && j == a_idx->A_block_ypos_get()){
							a_idx->A_heart_minus(D_attack);
							D_attack_finished = true;
							break;
						}	
					}
					if(D_attack_finished)	break;
				}

			}
			break;
		case Home:
			break;
		default:
			break;
	}
    
   return;
}

// void defenderObject::D_single_attack(vector<attackerObject*> attacker_list)
// {

//     return;
// }

void defenderObject::D_Attack(vector<attackerObject*> & attacker_list){
	if(D_is_dead()){	
		return;
	}

	switch(Od_type){
		case Prof1:
		case Prof2:
		case Bike:
		case Library:
			this->D_range_attack(attacker_list);
			break;
			//this->D_single_attack(attacker_list);
		case Home:
			break;
	}
	return;
}

