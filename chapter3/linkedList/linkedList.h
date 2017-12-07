#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <memory>

using namespace std;

class LinkedList{

public:
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


LinkedList();
void print() const;

void insert_data(int index, int data);


private:

shared_ptr<node_t> d_pt_head;


};

#endif