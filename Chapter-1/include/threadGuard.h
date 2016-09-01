#ifndef THREADGURAD_H
#define THREADGURAD_H

#include <thread>

class thread_guard {
	std::thread &t;
public:
	explicit thread_guard(std::thread &t_): t(t_) {}
	thread_guard(thread_guard const&) = delete;		// disable copy constructor
	thread_guard& operator=(thread_guard const&) = delete;	// disable = operator
	~thread_guard();
};

#endif