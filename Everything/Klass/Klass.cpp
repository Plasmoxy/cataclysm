// Klass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sebu.h>

using namespace std;
using namespace sebu;

void change(int& a) {
	a = 5;
}

void increment(Vector& v) {
	v.x += 1;
	v.y += 1;
}

int main()
{
	Vector a(1, 1);
	Vector b(2, 3);
	a += b;



    return 0;
}

