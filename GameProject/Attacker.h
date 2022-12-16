#pragma once
#include <vector>


using namespace std;

enum oa_type{Attacker1, Attacker2, Attacker3, Attacker4};
enum a_attack_type{a_Single, a_Range};

class People{
    protected:
        int xpos, ypos;  // pixel position
        int block_xpos, block_ypos; //block position
        oa_type Oa_type; // Attacker type
    public:
        People(){};
        ~People(){};
};

class Attacker: public People{
protected:
    int A_id;   // unique for each attacker
    int A_v;    // Attacker moving velocity
    int A_heart;    // Attacker heart
    int A_attack;   // Attacker attack
    a_attack_type A_attack_type; // S for single, R for range
    int A_attack_range;

public:
    // Constructor and Deconstructor
    Attacker(){};
    ~Attacker(){};

    // Position and Moving
    int A_block_xpos_get();
    int A_block_ypos_get();
    
    int A_v_get();
    void A_v_set(int);
    
    // Heart
    int A_heart_get();
    void A_heart_set(int);
    void A_heart_add(int);
    void A_heart_minus(int);
    bool A_is_dead();

    // Attack
    int A_attack_get();
    void A_attack_set(int);
    void A_attack_search(); //回傳值應該不是voids
};