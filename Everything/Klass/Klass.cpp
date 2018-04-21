// Klass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class Vector {
public:
	int x, y;
	Vector(int _x, int _y) {
		cout << "CONSTRUCTING VECTOR" << endl;
		x = _x;
		y = _y;
	}
	~Vector() {
		cout << "DESTRUCTING VECTOR" << endl;
	}

	void dump() {
		cout << "[ " << x << ", " << y << " ]" << endl;
	}
};

void change(int& a) {
	a = 5;
}

void increment(Vector& v) {
	v.x += 1;
	v.y += 1;
}

int main()
{
	Vector a = Vector(1, 1);
	a.dump();
	increment(a);
	a.dump();
    return 0;
}

