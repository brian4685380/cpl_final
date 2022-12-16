#include "attackerObject.h"
#include "SDL_image.h"

// Constructor
attackerObject::attackerObject(SDL_Renderer *ren, int x, int y, int id, oa_type Oa_type) {
	//cout << "create attacker" << id << endl;
	Init_Profile(id, Oa_type, ren);
	//renderer = ren;
	//objTexture = IMG_LoadTexture(renderer, "assets/Attackers/student1.png");
	xpos = x;
	ypos = y;
	pathIndex = 0;
	update_count = 0;
}

attackerObject:: ~attackerObject(){};

void attackerObject::Update() {
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

	int imageLength = 40;

	srcRect.h = 40;
	srcRect.w = 40;
	srcRect.x = 0;
	srcRect.y = 0;

	update_count++;
	if(update_count >= 4){
		update_count = 0;
		if (move_dir_list[pathIndex] == 'U')
			ypos -= A_v;
		if (move_dir_list[pathIndex] == 'D')
			ypos += A_v;
		if (move_dir_list[pathIndex] == 'L')
			xpos -= A_v;
		if (move_dir_list[pathIndex] == 'R')
			xpos += A_v;
		if (xpos % 40 == 0 && ypos % 40 == 0)
			pathIndex++;
	}
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = 40;
	destRect.h = 40;

}


void attackerObject:: Init_Profile(int id, oa_type _type, SDL_Renderer *ren){
	cout << "INIT Attacker " << id << endl;
	renderer = ren;
	/// TODO
	switch(_type){
		case Attacker1:
			objTexture = IMG_LoadTexture(renderer, "assets/Attackers/student1.png");
			Oa_type = Attacker1;
			A_id = id;
			A_v = 1;
			A_heart = 100;
			A_attack = 10;
			A_attack_type = a_Single;
			A_attack_range = 3;
			break;
		case Attacker2:
			objTexture = IMG_LoadTexture(renderer, "assets/Attackers/student2.png");
			Oa_type = Attacker2;
			A_id = id;
			A_v = 2;
			A_heart = 100;
			A_attack = 10;
			A_attack_type = a_Single;
			A_attack_range = 3;
			break;
		case Attacker3:
			objTexture = IMG_LoadTexture(renderer, "assets/Attackers/student3.png");
			Oa_type = Attacker3;
			A_id = id;
			A_v = 4;
			A_heart = 100;
			A_attack = 10;
			A_attack_type = a_Single;
			A_attack_range = 3;
			break;
		case Attacker4:
			objTexture = IMG_LoadTexture(renderer, "assets/Attackers/student4.png");
			Oa_type = Attacker4;
			A_id = id;
			A_v = 8;
			A_heart = 100;
			A_attack = 10;
			A_attack_type = a_Single;
			A_attack_range = 3;
			break;
	}
	
	return;
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