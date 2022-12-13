#include "Attack_path.h"
#include <cctype>
using namespace std;

// setting path_map row and col
AttackPath:: AttackPath(int r, int c){
    row = r;
    col = c;

    a_row = row - 1;
    a_col = 0;

    t_row = 0;
    t_col = col - 1;

    new_row = 0;
    new_col = 0;

    path_map.resize(row, vector<char>(col));
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            path_map[i][j] = 'O';
        }
    }

    move_pos_list.push_back(make_pair(a_row, a_col));    // setting start point
    path_map[a_row][a_col] = '+';    // setting start point
    path_map[t_row][t_col] = 'X';    // setting end point
    print_map();
}

// detect if path over the border
bool AttackPath:: is_over_border(int new_row, int new_col){
    if(new_row < 0 || new_row >= row || new_col < 0 || new_col >= col){
        return true;
    }
    return false;
}


// print the path_map and path
void AttackPath:: print_map(){
    for(int i = 0; i < path_map.size(); i++){
        for(int j = 0; j < path_map[0].size(); j++){
            cout << path_map[i][j] << " ";
        }
        cout << endl;
    }
}


// when input 'C' restart the path
void AttackPath:: restart(){

    // reset row, col
    a_row = row - 1;
    a_col = 0;
    new_row = 0;
    new_col = 0;

    // clear path_map
    for(int i = 0; i < path_map.size(); i++){
        for(int j = 0; j < path_map[0].size(); j++){
            if((i == row - 1 && j == 0) || (i == t_row && j == t_col)){
                continue;
            }
            path_map[i][j] = 'O';
        }
    }
    path_map[a_row][a_col] = '+';    // setting start point
    path_map[t_row][t_col] = 'X';    // setting end point
    move_dir_list.clear();
    move_pos_list.clear();
    move_pos_list.push_back(make_pair(a_row, a_col));    

    // print path_map
    cout << endl  << "RESTART" << endl;
    print_map();
}



void AttackPath:: draw_path(char dir){
    //TODOTODO toupper
    dir = toupper(dir);

    // input are invalid
    if(dir != 'U' && dir != 'D' && dir != 'R' && dir != 'L' && dir != 'C'){
        cout << "invalid input" << endl;
        return;
    }
    // reset
    if(dir == 'C'){
        restart();
        return;
    }

    // simulate temp next positoin
    new_row = a_row;
    new_col = a_col;
    if(dir == 'U'){
        new_row -= 1; 
    }
    if(dir == 'D'){
        new_row += 1; 
    }
    if(dir == 'R'){
        new_col += 1; 
    }
    if(dir == 'L'){
        new_col -= 1; 
    }

    // next pos over the border
    if(is_over_border(new_row, new_col)){
        cout << "over border" << endl;
        return;
    }

    // move back

    // if(!move_dir_list.empty()){
    //     // moving back 'U' + 'D' = 153, 'L' + 'R' = 158
    //     if(dir + move_dir_list.back() == 153 || dir + move_dir_list.back() == 158){
    //         cout << "cannot move back" << endl;
    //         return;
    //     }
    // }
    if(!move_dir_list.empty()){
    //cout << dir << " + " << move_dir_list.back() << "=" << dir + move_dir_list.back() << endl;
        // moving back 'U' + 'D' = 153, 'L' + 'R' = 158
        if(dir + move_dir_list.back() == 153 || dir + move_dir_list.back() == 158){
            cout << "move back" << endl;
            path_map[a_row][a_col] = 'O';
            a_row = new_row;
            a_col = new_col;
            path_map[a_row][a_col] = '+';
            move_dir_list.pop_back();
            move_pos_list.pop_back();
            print_map();
            return;
        }
    }

    // path intersects
    if(find(move_pos_list.begin(), move_pos_list.end(), make_pair(new_row, new_col)) != move_pos_list.end()){
        cout << "path intersects" << endl;
        return;
    }

    // if next pos is legal
    path_map[a_row][a_col] = dir;
    a_row = new_row;
    a_col = new_col;
    path_map[a_row][a_col] = '+';
    move_dir_list.push_back(dir);
    move_pos_list.push_back(make_pair(a_row, a_col));
    print_map();


    return;
}

// if arrive end point
bool AttackPath:: is_path_end(){
    if(a_row == t_row && a_col == t_col){
        cout << "attack path arrive the destination" << endl;
        for(char d: move_dir_list){
            cout << d << " ";
        }
        for(pair<int, int> d: move_pos_list){
            cout << "(" << d.first << "," << d.second << ") ";
        }
        return true;
    }
    return false;
}

vector< pair<int, int> > AttackPath:: get_path(){
    return move_pos_list;
}

// int main(){

//     AttackPath P(3,4);

//     while(1){
//         char d;
//         cin >> d;
//         P.draw_path(d);
//         if(P.is_path_end()){
//             break;
//         }
//     }
// }