#ifndef THREADLAUNCH_H
#define THREADLAUNCH_H

class background_task {
public:
	static int count;
	void operator() () const;
};

#endif