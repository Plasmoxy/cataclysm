// StringsAndStuff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

int a = 4;
int* p = &a;

int main()
{

	cout << "pointer: " << p << endl;

	while (true) {
		cout << "A = " << a << endl;
		cin.get();
	}
	
	cin.get();
    return 0;
}

