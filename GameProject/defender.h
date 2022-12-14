#pragma once
#include <utility>
#include <vector>

#include "Attacker.h"

using namespace std;

class building {
   protected:
	int8_t type;
	bool orientation;				  // 0 for horizontal, 1 for vertical;
	pair<double, double> coordinate;  // CAUTION! "coordinate" is similar �I!dd�}!to "pos" of Attacker!
	pair<int, int> pos;				  // arbitrary, just for convenience
	int8_t width, height;
	vector<pair<int, int>> block_occupied;

   public:
	building(int8_t, pair<double, double>);	 // building type, coordinate generated.
	~building();
	pair<int, int> pos_get();
	void orn_change();
	bool orn_get();
	void occupied_set();  // called when placed firmly, be cautious with negative index.

	// debug
};

class defender: public building {
   private:
	int8_t D_type;
	int D_id;
	int D_heart;
	int D_attack;
	int8_t D_attack_radius;
	vector<pair<int, int>> D_attack_block;	// be cautious with negative index.

   public:
	// defender
	defender(int8_t, pair<double, double>, int, int, int, int8_t);	// defender type(mostly correspond to building type), coordinate, id generated, heart, attack, radius
	~defender();
	void D_attack_block_set();
	// Heart
	void D_heart_set(int);
	void D_heart_add(int a = 1);	// default add 1
	void D_heart_minus(int a = 1);	// default minus 1

	// Attack
	void D_attack_set(int);
	void D_attack_add(int a = 1);
	void D_attack_minus(int a = 1);
	
	int D_heart_get();
    int D_attack_get();
	// vector<int> D_attack_search(*Attacker attacker, int NumOfAttacker)	// return target ID
};
