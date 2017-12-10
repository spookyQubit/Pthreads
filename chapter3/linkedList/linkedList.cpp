#include "linkedList.h"

#include <iostream>
#include <memory>

extern "C"{
#include <pthread.h>
}

using namespace std;


LinkedList::LinkedList()
{
	d_pt_head = NULL;
	pthread_mutex_init(&d_mutex, NULL);
}

void LinkedList::print()
{
	pthread_mutex_lock(&d_mutex);

	shared_ptr<node_t> cur = d_pt_head;
	while(cur != NULL){
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << endl;

	pthread_mutex_unlock(&d_mutex);

}

void LinkedList::insert_data(int index, int data)
{
	// lock the mutex
	pthread_mutex_lock(&d_mutex);

	// Check in the list is initially empty
	if(d_pt_head == NULL){		
		d_pt_head = make_shared<node_t>(index, data);
		pthread_mutex_unlock(&d_mutex);
		return;
	}

	// At this stage, the list is not empty
	shared_ptr<node_t> cur = d_pt_head;
	shared_ptr<node_t> prev = cur;

	// If the index is already present, 
	// just modify the data
	while(cur != NULL){
		if(cur->index == index){
			cur->data = data;
			pthread_mutex_unlock(&d_mutex);
			return;
		}

		prev = cur;
		cur = cur->next;
	}

	// The index is not found
	prev->next = make_shared<node_t>(index, data);

	// Unlock the mutex
	pthread_mutex_unlock(&d_mutex);
	return;
}
