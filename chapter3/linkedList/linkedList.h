#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <memory>

extern "C"{
#include <pthread.h>
}

using namespace std;

class LinkedList{

public:
LinkedList();
void print();
void insert_data(int index, int data);

private:
typedef struct node {

	// ctr
	node(int in, int dat)
	{
		index = in;
		data = dat;
		next = NULL;
	}
	
	// data variables
	int index;
	int data;
	struct shared_ptr<node> next;
} node_t;

shared_ptr<node_t> d_pt_head;
pthread_mutex_t d_mutex;
};

#endif