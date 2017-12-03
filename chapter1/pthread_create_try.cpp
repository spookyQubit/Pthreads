#include <iostream>

extern "C"{
#include <pthread.h>	
}


void do_one_thing(int* pt_r)
{
	int& r = *pt_r;
	r += 42;  
}


void do_another_thing(int* pt_r)
{
	int& r = *pt_r;
	r += 142;
}

typedef void* (*thread_func_pointer) (void *);

int main()
{
	int r1 = 0, r2 = 0, r3 = 0;

	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, (thread_func_pointer) do_one_thing, (void *) &r1);
	pthread_create(&thread2, NULL, (thread_func_pointer) do_another_thing, (void *) &r2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	std::cout << "r1 + r2 = " << r1 + r2 << std::endl;

}