#include <iostream>
#include <string>
#include "money.h"

using namespace std;

// constructor
player_money:: player_money(){};
player_money:: player_money(int n){
    _money = n;
}
player_money:: ~player_money(){};

// +
void player_money:: operator+=(int n){  // _money +=
    _money += n;
    return;
}
player_money player_money:: operator+ (player_money & m){  // _money + _money
    player_money temp;
    temp._money = this->_money + m._money;
    return temp;
}
player_money player_money:: operator+ (int n){  // _money + int
    player_money temp;
    temp._money = this->_money + n;
    return temp;   
}
player_money operator+ (int n, player_money & m)  {   // int + _money (global)
    player_money temp;
    temp._money = m._money + n;
    return temp;
}

// -
bool player_money:: is_positive(){ // if money < 0, set money to 0
    if(this -> _money < 0){
        _money = 0;
        return false;
    }
    else{
        return true;
    }
}
void player_money:: operator-= (int n){    // _money -=
    _money -= n;
    this->is_positive();
    return;
}
player_money player_money:: operator- (player_money & m){  // _money - _money
    player_money temp;
    temp._money = this->_money - m._money;
    temp.is_positive();
    return temp;
}
player_money player_money:: operator- (int n){  // _money - int
    player_money temp;
    temp._money = this->_money - n;
    temp.is_positive();
    return temp;   
}
player_money operator- (int n, player_money & m){  // int - _money (global)
    player_money temp;
    temp._money = n - m._money;
    temp.is_positive();
    return temp;
}

// set and get
void player_money:: money_set(int n){
    _money = n;
}
int player_money:: money_get(){
    return _money;
}

// int main(){
//     cout << "RUN" << endl;
//     player_money A;
//     player_money B(1);
//     A.money_set(10000);
//     A -= 1000;
//     A = A - 100;
//     A = A - B;
//     A = 10 - A;

//     cout << A.money_get() << endl;
// }