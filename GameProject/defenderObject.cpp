#pragma once
#include "defenderObject.h"
#include "attackerObject.h"
#include "SDL_image.h"

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
			D_heart = 100;
			D_attack = 10;
		    D_attack_type = d_Single;
			D_attack_radius = 5;
            break;

        case Prof2:
			objTexture = IMG_LoadTexture(renderer, "assets/Defender/defender2.png");
			Od_type = Prof2;
			D_id = id;
			D_heart = 200;
			D_attack = 10;
		    D_attack_type = d_Single;
			D_attack_radius = 5;
            break;

        case Bike:
			D_id = id;
			objTexture = IMG_LoadTexture(renderer, "assets/Defender/truck.png");
			Od_type = Bike;
			D_id = id;
			D_heart = 300;
			D_attack = 10;
		    D_attack_type = d_Single;
			D_attack_radius = 5;
            break;

        case Library:
			D_id = id;
			objTexture = IMG_LoadTexture(renderer, "assets/Defender/NTULibrary.png");
			Od_type = Library;
			D_id = id;
			D_heart = 400;
			D_attack = 10;
		    D_attack_type = d_Single;
			D_attack_radius = 5;
            break;

        case Home:
			D_id = id;
			objTexture = IMG_LoadTexture(renderer, "assets/Defender/BL_building_hollow.png");
			Od_type = Home;
			D_id = id;
			D_heart = 1;
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


//void defenderObject::D_range_attack(vector<attackerObject*> attacker_list)
//{

    // int NumOfAttacker = attacker_list.size();

    // for (int attacker_idx = 0; attacker_idx < NumOfAttacker; attacker_idx++){
    //     if (attacker_list[attacker_idx]->A_is_dead()) continue;

    //     for (int i = max(0, block_xpos-D_attack_radius); i < min(18, block_xpos+block_width+D_attack_radius); i++){
    //         for (int j = max (0, block_ypos-D_attack_radius); j < min(14, block_ypos+block_height+D_attack_radius); j++){
    //             if ((i<block_xpos || i>=block_xpos+width) && (j<block_ypos || j>=block_ypos+height)){
    //                 if (i == attacker_list[attacker_idx]->A_block_xpos_get() && j == attacker_list[attacker_idx]->A_block_ypos_get())
    //                     attacker_list[attacker_idx]->A_heart_minus(D_attack);
    //                     goto D_attack_finished;
    //             }
    //         }
    //     }
    //     D_attack_finished:
    // }
 //   return;
//}

// void defenderObject::D_single_attack(vector<attackerObject*> attacker_list)
// {

//     return;
// }

