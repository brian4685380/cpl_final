#pragma once
#include <utility>
#include <vector>

#include "Attacker.h"

using namespace std;

enum od_type {Prof1, Prof2, Bike, Library, Home};
enum d_attack_type {d_Single, d_Range};

class building {
   protected:
	od_type Od_type;
	bool orientation;		        // 0 for horizontal, 1 for vertical;
	int block_xpos, block_ypos;     // coordinate for blocks
	int xpos, ypos;	                // position for pixels
	int block_width, block_height;  // height for blocks
    int width, height;              // height for pixels
	vector<pair<int, int>> block_occupied;

   public:

	building();             // constructor
	~building();            // destructor
	void orn_change();
	bool orn_get();
	void occupied_set();    // called when placed firmly, be cautious with negative index.
    pair<int, int> block_pos_get();
};

class defender: public building {
 protected:
    d_attack_type D_attack_type;              // Single or Range
	int D_id;                               // id in number order
	int D_heart;
	int D_attack;
	int D_attack_radius;
	vector<pair<int, int>> D_attack_block;

   public:
	// defender
	defender();
	~defender();

	void D_attack_block_set();
	// Heart
	int D_heart_get();
	void D_heart_set(int);
	void D_heart_add(int);	// default add 1
	void D_heart_minus(int);	// default minus 1

	// Attack
    int D_attack_get();
	void D_attack_set(int);
	void D_attack_add(int);   // default add 1
	void D_attack_minus(int); // default minus 1

    pair<int, int> D_block_pos_get();
	//vector<int> D_attack_search(const * Attacker, int)
    bool is_dead();                   // default false


};
