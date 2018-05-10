// AutoPtr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>

template <class T>
using ptr = std::shared_ptr<T>;

class XD {
public:
	int a;

	XD(int i) {
		a = i;
	}
};

int main()
{

	ptr<XD> p;

	while (true) {
		p = ptr<XD>(new XD(2));
	}

    return 0;
}

