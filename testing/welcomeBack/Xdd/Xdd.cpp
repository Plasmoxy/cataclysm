// Xdd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

bool active = true;
string cmd;

string a;

int main(){
	
	while (active) {

		cout << ">";
		cin >> cmd;

		a[4] = 'X';

		if (cmd == "exit" || cmd == "q" || cmd == "e") {
			active = false;
			break;
		}
		else if (cmd == "a") {
			cout << a;
		}

	}

    return 0;
}



