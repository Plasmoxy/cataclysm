// Visual Studio Hello World xD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	int a[] = { 1,2,3,4 };
	for (int i : a)
	{
		cout << i << " ";
	}
	cin.get();
}

