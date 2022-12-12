#include <iostream>
#include <utility>
#include <vector>

using namespace std;
int main() {
	int x = 0, y = 0;
	vector<pair<int, int>> vp;
	pair<int, int> p1(x, y);
	p1 = make_pair(x, y);
	vp.push_back(make_pair(x, y));
	
	// create a 2D vector with 10 by 2 and initialize all elements to 0
	vector<vector<int>> v(10, vector<int>(2, 0));
	for (auto &i: v) {
		for (auto &j: i) {
			cout << j << " ";
		}
		cout << endl;
	}
}
