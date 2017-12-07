#include "./matrix.h"
#include "./timer.h"
#include <iostream>
#include <assert.h>
#include <unistd.h>

extern "C"{
#include <pthread.h>	
}


typedef struct{
	Matrix*        pt_ma;
	Matrix*        pt_mb;
	Matrix*        pt_mc;
	pair<int, int> id;
} matrix_multiply_data_t;

void serialMultiplication(Matrix* pt_mc, Matrix& ma, Matrix& mb)
{
	Matrix& mc = *pt_mc;

	for(int i=0; i<mc.shape().first; ++i){
		for(int j=0; j<mc.shape().second; ++j){

			pair<int, int> id = make_pair(i, j);
			Matrix::mult(&mc, ma, mb, id);
		}
	}

	return;
}

void* peer_mul(void* pt_data_in)
{
	matrix_multiply_data_t* pt_data = (matrix_multiply_data_t*) pt_data_in	;
	Matrix::mult(pt_data->pt_mc, *(pt_data->pt_ma), *(pt_data->pt_mb), pt_data->id);
}

void parallelMultiplication(Matrix* pt_mc, Matrix& ma, Matrix& mb)
{
	assert(pt_mc != NULL);
	Matrix& mc = *pt_mc;

	pthread_t* pt_threads = (pthread_t*)malloc(mc.shape().first * mc.shape().second * sizeof(pthread_t));
	matrix_multiply_data_t* pt_data;


	int thread_id = 0;
	for(int i=0; i<mc.shape().first; ++i){
		for(int j=0; j<mc.shape().second; ++j){

			pt_data = (matrix_multiply_data_t*)malloc(1 * sizeof(matrix_multiply_data_t)); // this is not freed!
			pt_data->pt_ma = &ma; 
			pt_data->pt_mb = &mb;
			pt_data->pt_mc = &mc;
			pt_data->id    = make_pair(i, j);  

			pthread_create(&(pt_threads[thread_id]), NULL, peer_mul, pt_data);
			++thread_id;
		}
	}

	for(int i=0; i<mc.shape().first * mc.shape().second; ++i){
		pthread_join(pt_threads[i], NULL);
	}

	free(pt_threads);
	return;
}

int main()
{
	Matrix ma(5, 2, 7);
	ma.print();

	std::cout << "ma.shape() = " 
	          << "(" 
	          << ma.shape().first 
	          << ", " 
	          << ma.shape().second
	          << ")"
	          << std::endl;

	Matrix mb(2, 4, 9);
	mb.print();

	Matrix mc(5, 4, 0);
	
	Timer t;
	// multiplication without threads
	t.start();
	serialMultiplication(&mc, ma, mb);
	unsigned long elapsed_time = t.elapsed_time();
	std::cout << "serial elapsed_time = " << elapsed_time << endl;
	t.stop();
	mc.print();
	
	// multiplication using pthreads
	t.start();
	parallelMultiplication(&mc, ma, mb);
	elapsed_time = t.elapsed_time();
	std::cout << "parallel elapsed_time = " << elapsed_time << endl;
	t.stop();
	mc.print();
}