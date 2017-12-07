#ifndef TIMER_H
#define TIMER_H

class Timer{

private:
	unsigned long d_begin_time;
	bool d_is_started;

public:
	Timer();
	void start();
	void stop();
	unsigned long elapsed_time();
};

#endif