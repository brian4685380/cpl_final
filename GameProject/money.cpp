#include <iostream>
#include <string>
#include "Money.h"

using namespace std;

/*
使用方法
class name : Money
constructor : Money() or Money(n) to set player's initial money

Functions:
money_set() set player's money
money_get() return player's money(int)

Operators:
support 
Money+=Money, Money+=int, Money+Money, Money+int, int+Money 
Money-=int, Money-Money, Money-int, int-Money
if _money < 0 after deduction, it will be set to 0 automatically

Examples:
    Money my_money;
    Money my_money2(100);
    my_money.money_set(1000);
    my_money -= 200;
    my_money += my_money2;
    cout << A.money_get() << endl;
*/

// constructor
Money:: Money(){
    _money = 0;
}
Money:: Money(int n){
    _money = n;
}
Money:: ~Money(){};

// +
void Money:: operator+=(Money & m){  // _money +=
    _money += m._money;
    return;
}
void Money:: operator+=(int n){  // _money +=
    _money += n;
    return;
}
Money Money:: operator+ (Money & m){  // _money + _money
    Money temp;
    temp._money = this->_money + m._money;
    return temp;
}
Money Money:: operator+ (int n){  // _money + int
    Money temp;
    temp._money = this->_money + n;
    return temp;   
}
Money operator+ (int n, Money & m)  {   // int + _money (global)
    Money temp;
    temp._money = m._money + n;
    return temp;
}

// -
bool Money:: is_positive(){ // if money < 0, set money to 0
    if(this -> _money < 0){
        _money = 0;
        return false;
    }
    else{
        return true;
    }
}
void Money:: operator-= (Money & m){    // _money -=
    _money -= m._money;
    this->is_positive();
    return;
}
void Money:: operator-= (int n){    // _money -=
    _money -= n;
    this->is_positive();
    return;
}
Money Money:: operator- (Money & m){  // _money - _money
    Money temp;
    temp._money = this->_money - m._money;
    temp.is_positive();
    return temp;
}
Money Money:: operator- (int n){  // _money - int
    Money temp;
    temp._money = this->_money - n;
    temp.is_positive();
    return temp;   
}
Money operator- (int n, Money & m){  // int - _money (global)
    Money temp;
    temp._money = n - m._money;
    temp.is_positive();
    return temp;
}

// set and get
void Money:: money_set(int n){
    _money = n;
}
int Money:: money_get(){
    return _money;
}

// int main(){
//     Money my_money;
//     Money my_money2(100);
//     my_money.money_set(1000);
//     my_money -= 200;
//     my_money += my_money2;
//     cout << my_money.money_get() << endl;
// }