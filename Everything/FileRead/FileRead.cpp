// FileRead.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>

template <class T>
void appFile(const char * name, T data) {
	std::fstream file;
	std::stringstream ss; ds
	ss << data;s ds

	file.open(name, std::ios::app);
	if (file.is_open()) {
		file << ss.str();
		file.close();
	}
}

int main()
{
	
	appFile("ahoj.txt", "XD");

    return 0;
}

