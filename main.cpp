/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

// Using SDL, standard IO, and strings
#include <SDL_bgi.h>
#include <graphics.h>

#include <cmath>
#include <iostream>
using namespace std;
class elipso {
   public:
	int x, y, a, b, c;
	void initialize(int x0, int y0, int a0, int b0) {
		x = x0;
		y = y0;
		a = a0;
		b = b0;	 // set center & semi-axes
		c = sqrt(fabs(a * a - b * b));
		show();
	}
	void show() {
		ellipse(x, y, 0, 360, a, b);  // draw a complete ellipse
		circle(x + c, y, 1);		  // mark the positive focuscircle
		circle(x - c, y, 1);		  // mark the negative focus
	}
	double area() { return 3.14159 * a * b; }
};

int main() {
	initwindow(800, 600);
	cleardevice();
	elipso e;
	e.initialize(100, 100, 50, 30);
	cout << "The area is " << e.area() << endl;
	elipso *p = &e;
	cout << "The center is at (" << p->x << ", " << p->y << ")" << endl;
	getch();
	closegraph();
}