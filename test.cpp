#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main() {
	string s1("Input test 123 5.7 A"), s2, s3;
	int i;
	int x;
	char c;
	istringstream sin(s1);
	sin >> s2 >> s3 >> i >> x >> c;
	cout << "The following items are extracted:"
		 << "\nstring: " << s2 << ", " << s3
		 << "\ninteger: " << i
		 << "\ndouble: " << x
		 << "\ncharacter: " << c << endl
		 << int(c) << endl;
}