#include <vector>
#include <string>
#include <iostream>
#include "Attacker.h"
using namespace std;

// Constructor and Deconstructor

// Attacker:: Attacker(){

// }
// Attacker:: ~Attacker(){

// }

// Moving and Pos
vector<double> Attacker::A_pos_get(){
    return A_pos;
}

vector<int> Attacker:: A_block_pos_get(){
    return A_block_pos;
}

void Attacker:: A_block_pos_update(){
    // Need to be REVISED
    A_block_pos[0] = A_pos[0] / 40;
    A_block_pos[1] = A_pos[0] / 40;
    return;
}

void Attacker:: A_move(){
    // if can move

    switch(A_direction){
        case U:
            A_pos[0] += A_v;
            break;
        case D:
            A_pos[0] -= A_v;
            break;
        case R:
            A_pos[1] += A_v;
            break;
        case L:
            A_pos[1] -= A_v;
            break;
        default:
            break;
    }
    A_block_pos_update();
}

void Attacker:: A_change_dir(char d){
    switch(d){
        case 'U':
            A_direction = U;
            break;
        case 'D':
            A_direction = D;
            break;
        case 'L':
            A_direction = L;
            break;
        case 'R':
            A_direction = R;
            break;
        default:
            cout << "ERROR : invalid direction type" << endl;
            break;
    }
}

double Attacker:: A_v_get(){
    return A_v;
}

void Attacker:: A_v_set(double v){
    A_v = v;
}

// Heart
int Attacker:: A_heart_get(){
    return A_heart;
}

void Attacker:: A_heart_set(int heart){
    A_heart = heart;
}

void Attacker:: A_heart_add(int n){
    A_heart += n;
}

void Attacker:: A_heart_minus(int n){
    A_heart -= n;
}

bool Attacker:: A_is_dead(){
    return A_heart > 0 ? false : true;
}

// Attack
int Attacker:: A_damage_get(){
    return A_damage;
}

void Attacker:: A_damage_set(int n){
    A_damage = n;
}

void Attacker:: A_attack_search(){
    ////TODO
} //回傳值應該不是void

// int A_id = 0
// unique for each attacker
// vector<double> A_pos = {0, 0};    // {Row, Col}
// vector<int> A_block_pos = {0, 0};    // {Row, Col}
// double A_v = 0;
// //char A_direction = 'U';   // U, L, D, R
// DIR A_direction = U;

// int A_heart = 0;
// int A_damage = 0;
// char A_attack_type = 'S'; // S for single, R for range
// int A_attack_range = 0;


int main(){
    Attacker a;
    
    a.A_pos_get();
    a.A_block_pos_get();
    a.A_block_pos_update();
    a.A_move();
    a.A_change_dir('U');
    a.A_v_get();
    a.A_v_set(20);
    return 0;
}