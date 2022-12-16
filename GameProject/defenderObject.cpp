#include "defenderObject.h"

#include "SDL_image.h"

defenderObject::defenderObject(SDL_Renderer *ren, int x, int y, int w, int h, int id, od_type otp) {
	
	O_Init_Profile(id, otp, ren);
	xpos = x;
	ypos = y;
	width = w;
	height = h;
	block_width = w / 40;
	block_height = h / 40;
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
			D_heart = 100;
			D_attack = 10;
		    D_attack_type = d_Single;
			D_attack_radius = 5;
            break;

        case Bike:
			D_id = id;
			objTexture = IMG_LoadTexture(renderer, "assets/Defender/truck.png");
			Od_type = Bike;
			D_id = id;
			D_heart = 100;
			D_attack = 10;
		    D_attack_type = d_Single;
			D_attack_radius = 5;
            break;

        case Library:
			D_id = id;
			objTexture = IMG_LoadTexture(renderer, "assets/Defender/NTULibrary.png");
			Od_type = Library;
			D_id = id;
			D_heart = 100;
			D_attack = 10;
		    D_attack_type = d_Single;
			D_attack_radius = 5;
            break;

        case Home:
			D_id = id;
			objTexture = IMG_LoadTexture(renderer, "assets/Defender/BL_building_hollow.png");
			Od_type = Home;
			D_id = id;
			D_heart = 100;
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
}

void defenderObject::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

