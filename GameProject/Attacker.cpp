#pragma once
#include "Attacker.h"
using namespace std;

pair<int,int> Attacker:: A_block_pos_get(){
    return make_pair(block_xpos, block_ypos);
}

int Attacker:: A_v_get(){
    return A_v;
}
void Attacker:: A_v_set(int v){
    A_v = v;
    return;
}

// Heart
int Attacker:: A_heart_get(){
    return A_heart;
}
void Attacker:: A_heart_set(int h){
    A_heart = h;
    return;
}
void Attacker:: A_heart_add(int n){
    A_heart += n;
    return;
}
void Attacker:: A_heart_minus(int n){
    A_heart -= n;
    return;
}
bool Attacker:: A_is_dead(){
    return A_heart <= 0 ? true : false;
}

// Attack
int Attacker:: A_attack_get(){
    return A_attack;
}
void Attacker:: A_attack_set(int n){
    A_attack = n;
    return;
}
void Attacker:: A_attack_search(){ 
    //////TODOTODO
} 
