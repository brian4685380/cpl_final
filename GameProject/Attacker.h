#pragma once
#include <vector>
#include <string>
using namespace std;


enum DIR {U, L, D, R};

class Attacker{

public:
    // Constructor and Deconstructor
    Attacker();
    ~Attacker();

    // Moving and Pos
    vector<double> A_pos_get();
    vector<int> A_block_pos_get();
    void A_block_pos_update();
    void A_move();
    void A_change_dir(char);
    double A_v_get();
    void A_v_set(double);
    
    // Heart
    int A_heart_get();
    void A_heart_set(int);
    void A_heart_add(int);
    void A_heart_minus(int);
    bool A_is_dead();

    // Attack
    int A_damage_get();
    void A_damage_set(int);
    void A_attack_search(); //回傳值應該不是void

private:
    int A_id;           // unique for each attacker
    vector<double> A_pos;    // {Row, Col}
    vector<int> A_block_pos;  // {Row, Col}
    double A_v;
    //char A_direction;   // U, L, D, R
    DIR A_direction;
    int A_heart;
    int A_damage;
    char A_attack_type; // S for single, R for range
    int A_attack_range;

};