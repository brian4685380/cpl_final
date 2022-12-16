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
    int block_xpos_get();
    int block_ypos_get();
	od_type get_type();
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

    int D_block_xpos_get();
    int D_block_ypos_get();
	void D_attack_block_set();
	od_type D_get_type();
	// Heart
	int D_heart_get();
	void D_heart_set(int);
	void D_heart_add(int);	// default add 1
	void D_heart_minus(int);	// default minus 1
    bool D_is_dead();                   // default false

	// Attack
    int D_attack_get();
	void D_attack_set(int);
	void D_attack_add(int);   // default add 1
	void D_attack_minus(int); // default minus 1



};
