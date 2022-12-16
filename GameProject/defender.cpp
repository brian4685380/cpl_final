#include "defender.h"

#include <iostream>
#include <utility>
#include <vector>

#include "Attacker.h"

using namespace std;

// building

building::building() {
	orientation = false;  // default horizontal

	occupied_set();
}

building::~building() {}

void building::orn_change() {
	orientation = !orientation;
}

bool building::orn_get() {
	return orientation;
}


void building::occupied_set() {
	//////BUG

	// block_occupied.clear();
	// int row, col;
	// if (!orientation) {
	// 	row = block_height;
	// 	col = block_width;
	// }  // horizontal
	// else {
	// 	row = block_width;
	// 	col = block_height;
	// }  // vertical

	// for (int i = 0; i < row; i++) {
	// 	for (int j = 0; j < col; j++) {
	// 		block_occupied.push_back(make_pair(block_xpos + i, block_ypos + j));
	// 	}
	// }
}

int building::block_xpos_get(){
    return block_xpos;
}

int building::block_ypos_get(){
    return block_ypos;
}

// defender

defender::defender()
{
    // TODO3: set parameters below from D_type list
    //D_attack_set(?);
    //D_heart_set(?);
    //D_attack_radius = ?
	//
	D_attack_block_set();
}

defender::~defender() {}

void defender::D_attack_block_set() {
	////////BUGBUG

	// D_attack_block.clear();
	// int row, col;
	// if (!orientation) {
	// 	row = block_height;
	// 	col = block_width;
	// } else {
	// 	row = block_width;
	// 	col = block_height;
	// }

	// for (int i = -D_attack_radius; i < 0 || (i >= row && i < row + D_attack_radius); i++) {
	// 	for (int j = -D_attack_radius; j < 0 || (i >= col && i < col + D_attack_radius); j++) {
	// 		block_occupied.push_back(make_pair(block_xpos + i, block_ypos + j));
	// 	}
	// }
}

od_type defender::D_get_type(){
	return Od_type;
}

// heart
void defender::D_heart_set(int a) {
	D_heart = a;
}

int defender::D_heart_get() {
	return D_heart;
}

void defender::D_heart_add(int a) {
	D_heart += a;
}

void defender::D_heart_minus(int a) {
	D_heart -= a;
}

// attack

void defender::D_attack_set(int a) {
	D_attack = a;
}

int defender::D_attack_get() {
	return D_attack;
}

void defender::D_attack_add(int a) {
	D_attack += a;
}

void defender::D_attack_minus(int a) {
	D_attack -= a;
}

int defender::D_block_xpos_get(){
    return block_xpos;
}

int defender::D_block_ypos_get(){
    return block_ypos;
}



// vector<int> defender::D_attack_search(const * Attacker attacker, int NumOfAttacker)  //
// {
// 	vector<int> target;
// 	target = new int[NumOfAttacker];
// 	/*for (int i = 0; i < NumOfAttacker; i++){

// 		for int j in D_attack_blocks
// 			if attacker[i].A_pos_get() in attack_blocks
// 				target.push_back(i) //ID of target
// 	}*/
// 	return target;
// }

bool defender::D_is_dead(){
	return (D_heart <= 0);
}

