#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;

class Timer{
public:

// constructor
Timer(int); // int total_time

void timer_update();
bool is_time_up();
int get_elapsed_s();
int get_left_s();
int get_elapsed_ms();
int get_left_ms();


private:
    chrono::steady_clock::time_point _time_start;   // game start time
    chrono::steady_clock::time_point _time_now;
    chrono::milliseconds _time_elapsed;   // time elapsed since game start = now - start
    chrono::milliseconds _time_total;   // attacker's total offense time
    chrono::milliseconds _time_left;   // attacker's left offense time = total - elapsed

};