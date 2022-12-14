#include "defender.h"

#include <iostream>
#include <utility>
#include <vector>

#include "Attacker.h"

using namespace std;

// building
building::building(int8_t tp, pair<double, double> co) {
	type = tp;
	orientation = false;  // default horizontal
	coordinate = co;
	//  obtain width, height from type definition
	occupied_set();
}

building::~building() {}

pair<int, int> building::pos_get() {
	return pos;
}

void building::orn_change() {
	orientation = !orientation;
}

bool building::orn_get() {
	return orientation;
}

void building::occupied_set() {
	block_occupied.clear();
	int8_t row, col;
	if (!orientation) {
		row = height;
		col = width;
	}  // horizontal
	else {
		row = width;
		col = height;
	}  // vertical

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			block_occupied.push_back(make_pair(pos.first + i, pos.second + j));
		}
	}
}

// defender

defender::defender(int8_t tp, pair<double, double> co, int id, int attack, int heart, int8_t radius)
	: building(tp, co), D_id(id), D_attack(attack), D_heart(heart), D_attack_radius(radius) {
	D_attack_block_set();
}

defender::~defender() {}

void defender::D_attack_block_set() {
	D_attack_block.clear();
	int row, col;
	if (!orientation) {
		row = height;
		col = width;
	} else {
		row = width;
		col = height;
	}

	for (int i = -D_attack_radius; i < 0 || (i >= row && i < row + D_attack_radius); i++) {
		for (int j = -D_attack_radius; j < 0 || (i >= col && i < col + D_attack_radius); j++) {
			block_occupied.push_back(make_pair(pos.first + i, pos.second + j));
		}
	}
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

// vector<int> defender::D_attack_search(*Attacker attacker, int NumOfAttacker)  //
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
