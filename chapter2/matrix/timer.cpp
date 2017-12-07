#include "./timer.h"
#include <iostream>

extern "C"{
#include <time.h>
}


Timer::Timer()
{
	d_is_started = false;
	d_begin_time = 0;
}

void Timer::start()
{
	d_is_started = true;
	d_begin_time = clock();
}

void Timer::stop()
{
	d_is_started = false;
	d_begin_time = 0;
}


unsigned long Timer::elapsed_time()
{
	if(!d_is_started){
		std::cout << "The timer has not started!" << std::endl;
	}

	return ((unsigned long)clock() - d_begin_time);


}


