#include <iostream>
#include "threadGuard.h"

using namespace std;

thread_guard::~thread_guard() {
	if (t.joinable())
		t.join();
	cout << "thread safely joined!" << endl;
}