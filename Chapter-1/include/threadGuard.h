#ifndef THREADGURAD_H
#define THREADGURAD_H

#include <thread>

class thread_guard {
	std::thread &t;
public:
	explicit thread_guard(std::thread &t_): t(t_) {}
	thread_guard(const thread_guard &) = delete;		// disable copy constructor
	thread_guard& operator=(const thread_guard &) = delete;	// disable = operator
	~thread_guard();
};

#endif