#include <iostream>
#include <vector>

using namespace std;

// setting map row and col
int row = 4;
int col = 6;

int a_row = row - 1;
int a_col = 0;

int t_row = 0;
int t_col = col - 1;

int new_row = 0;
int new_col = 0;

// map
vector< vector<char> > map(row, vector<char>(col, 'O'));
// moving list
vector<char> move_dir_list; // store moving direction
vector< pair<int, int> > move_pos_list; // store passing blocks


// detect if path over the border
bool is_over_border(int new_row, int new_col){
    if(new_row < 0 || new_row >= row || new_col < 0 || new_col >= col){
        return true;
    }
    return false;
}


// print the map and path
void print_map(){
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[0].size(); j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

// when input 'C' restart the path
void restart(){

    // reset row, col
    a_row = row - 1;
    a_col = 0;
    new_row = 0;
    new_col = 0;

    // clear map
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[0].size(); j++){
            if((i == row - 1 && j == 0) || (i == t_row && j == t_col)){
                continue;
            }
            map[i][j] = 'O';
        }
    }
    map[a_row][a_col] = '+';    // setting start point
    map[t_row][t_col] = 'X';    // setting end point
    move_dir_list.clear();
    move_pos_list.clear();
    move_pos_list.push_back(make_pair(a_row, a_col));    

    // print map
    cout << endl  << "RESTART" << endl;
    print_map();
}


int main(){

    move_pos_list.push_back(make_pair(a_row, a_col));    // setting start point
    map[a_row][a_col] = '+';    // setting start point
    map[t_row][t_col] = 'X';    // setting end point
    print_map();

    while(a_row != t_row || a_col != t_col){
        char dir = 0;
        cin >> dir;
        cout << endl;

        // input are invalid
        if(dir != 'U' && dir != 'D' && dir != 'R' && dir != 'L' && dir != 'C'){
            cout << "invalid input" << endl;
            continue;
        }
        // reset
        if(dir == 'C'){
            restart();
            continue;
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
            continue;
        }

        if(!move_dir_list.empty()){
            // moving back 'U' + 'D' = 153, 'L' + 'R' = 156
            if(dir + move_dir_list.back() == 153 || dir + move_dir_list.back() == 156){
                cout << "cannot move back" << endl;
                continue;
            }
        }

        // path intersects
        if(find(move_pos_list.begin(), move_pos_list.end(), make_pair(new_row, new_col)) != move_pos_list.end()){
            cout << "path intersects" << endl;
            continue;
        }

        // is next pos is legal
        map[a_row][a_col] = dir;
        a_row = new_row;
        a_col = new_col;
        map[a_row][a_col] = '+';
        move_dir_list.push_back(dir);
        move_pos_list.push_back(make_pair(a_row, a_col));
        print_map();
        

    }

    // arrive end point
    if(a_row == t_row && a_col == t_col){
        cout << "arrive the destination" << endl;
    }

    for(char d: move_dir_list){
        cout << d << " ";
    }

}