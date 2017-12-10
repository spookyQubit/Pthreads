#include <iostream>

extern "C"{
#include <pthread.h>
}


/*
Multiple signaling threads increment the global variable count.
When the value of count reaches count_signalling_threshold, the thread
running the signalling function signals the thread running the waiting function.
*/


int count;
int count_signal_threshold = 6;
int max_inc = 5;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;


void* signalling_function(void* pt_id_v)
{
	int* pt_id = (int*)pt_id_v;

	std::cout << "signalling *pt_id = " << *pt_id 
	          << " count = " << count
	          << std::endl;

	for(int i=0; i<max_inc; ++i){
		pthread_mutex_lock(&mutex);
		++count;
		std::cout << "signalling *pt_id = " << *pt_id 
	              << " count = " << count
	              << std::endl;

		if(count == count_signal_threshold){
			//pthread_mutex_unlock(&mutex);
			std::cout << "signalling *pt_id = " << *pt_id 
	                  << " count = " << count
	                  << " signalling"
	                  << std::endl;
			pthread_cond_signal(&cv);
		}

		/*
		The thing that throws me off:
		When we unlock the mutex at this point, the mutex will be in demand by:
		1) The waiting thread(s)
		2) Other signaling thread ready to change count

		If the mutex is acquired my the waiting thread, things are fine. 
		But what happens if the mutex is acquired by another 
		signaling thread, possibaly changing count??

		Is priority given to the waiting thread to acquire the mutex? 

		Ans: Possible run:
		
		waiting_function *pt_id = 0
        signalling *pt_id = 0 count = 0
        signalling *pt_id = 0 count = 1
        signalling *pt_id = 0 count = 2
        signalling *pt_id = 0 count = 3
        signalling *pt_id = 0 count = 4
        signalling *pt_id = 0 count = 5
        signalling *pt_id = 1 count = 5
        signalling *pt_id = 1 count = 6
        signalling *pt_id = 1 count = 6 signalling
        signalling *pt_id = 1 count = 7
        signalling *pt_id = 1 count = 8
        signalling *pt_id = 1 count = 9
        signalling *pt_id = 1 count = 10
        waiting *pt_id = 0 count = 10

        Note that even though the signalling took place when count == 6, 
        by the time waiting thread got the mutex, the count has incremented to 10. 

        This means that the waiting thread need not get the mutext immediately after the signal!
		*/
		pthread_mutex_unlock(&mutex);
	}

	return(NULL);
}


void* waiting_function(void* pt_id_v)
{
	pthread_mutex_lock(&mutex);

	int* pt_id = (int*)pt_id_v;
	std::cout << "waiting_function *pt_id = " << *pt_id << std::endl;

	while(count<count_signal_threshold){
		pthread_cond_wait(&cv, &mutex);
	}

	std::cout << "waiting *pt_id = " << *pt_id 
              << " count = " << count
	          << std::endl; 
	pthread_mutex_unlock(&mutex);
	return(NULL);
}


int main()
{
	count = 0;

	pthread_t w0;
	int w[2] = {0, 1};
	pthread_create(&w0, NULL, waiting_function, (void*)&w[0]);
	
	pthread_t s0, s1, s2;
	int s[3] = {0, 1, 2};
	pthread_create(&s0, NULL, signalling_function, (void*)&s[0]);
	pthread_create(&s1, NULL, signalling_function, (void*)&s[1]);
	
	pthread_join(w0, NULL);
	
	pthread_join(s0, NULL);
	pthread_join(s1, NULL);
	
	return 0;
}