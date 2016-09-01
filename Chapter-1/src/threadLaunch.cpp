#include <iostream>
#include "threadLaunch.h"

using namespace std;

int background_task::count = 0;

void background_task::operator() () const {
	for (unsigned i = 0; i < 1000000; i++)
		int j = i;
	cout << ++count;
}