#include <iostream>
#include <vector>
#include "block.h"
using namespace std;

class AttackPath{
public:

    // Constructor
    AttackPath(int, int);   //int row, int col

    // Methods
    bool is_over_border(int , int);
    void print_map();
    void restart();
    void draw_path(char);
    bool is_path_end();
    vector< pair<int, int> > get_path();
    void getInitialMap(vector<block *>);
private:

    int row;
    int col;

    int a_row;  // attack row
    int a_col;

    int t_row;  // temp row
    int t_col;

    int new_row;    // new(next) row
    int new_col;

    std::vector<block *> initialMap;
    // path_map
    vector< vector<char>> path_map;
    // moving list
    vector<char> move_dir_list; // store moving direction
    vector< pair<int, int> > move_pos_list; // store passing blocks

};