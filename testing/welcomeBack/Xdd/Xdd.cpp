// Xdd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

bool active = true;
string cmd;

int main(){

	SetConsoleTitle(TEXT("Hello"));
	cout << "say hello" << endl << endl;
	
	while (active) {

		cout << ">";
		cin >> cmd;

		if (cmd == "exit" || cmd == "q" || cmd == "e") {
			active = false;
			break;
		}
		else if (cmd == "hello") {
			cout << "hello fag" << endl;
		}

	}

    return 0;
}



