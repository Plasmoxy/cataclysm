// Matematix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <pmxy.h>
#include <pmxyvec.h>

using namespace std;
using namespace pmxy;

int main()
{
	Vec a(1, 1);
	a.rotate(Vec(0, 1), M_PI/2);
	a.round();
	a.dump();

    return 0;
}

