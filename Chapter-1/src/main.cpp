#include <thread>
#include <iostream>
#include "threadLaunch.h"
#include "threadGuard.h"

using namespace std;

static void thread_launch();
static void thread_launch_safe();

int main() {
	cout << "[thread initialize]" << endl;
	thread_launch();
	cout << endl;

	cout << "[thread guard]" << endl;
	thread_launch_safe();
	cout << endl;
	return 0;
}

static void thread_launch() {
	// Spawning thread from background_task class
	cout << "t1, t2, t3 spawned!" << endl;
	background_task f;
	thread t1(f);
	// Spawning thread from class constructor
	// thread t2(background_task()) 	// this is wrong, this declare a function called t2 with one background_task parameter and thread object return type.
	thread t2((background_task()));
	// list constructor
	thread t3{background_task()};
	if (t1.joinable())
		t1.join();
	if (t2.joinable())
		t2.join();
	if (t3.joinable())
		t3.join();
	cout << endl;
	cout << "t1, t2, t3, joined!" << endl;
}

static void thread_launch_safe() {
	thread t1{background_task()};
	thread t2{background_task()};
	thread t3{background_task()};
	thread_guard g1(t1), g2(t2), g3(t3);
	cout << "t1, t2, t3 spawned!" << endl;
}