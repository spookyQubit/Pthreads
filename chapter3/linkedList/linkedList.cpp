#include "linkedList.h"

#include <iostream>
#include <memory>

using namespace std;


LinkedList::LinkedList()
{
	d_pt_head = NULL;
}

void LinkedList::print() const
{
	shared_ptr<node_t> cur = d_pt_head;
	while(cur != NULL){
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << endl;
}

void LinkedList::insert_data(int index, int data)
{
	if(d_pt_head == NULL){		
		d_pt_head = make_shared<node_t>(index, data);
		return;
	}

	shared_ptr<node_t> cur = d_pt_head;
	shared_ptr<node_t> prev = cur;

	while(cur != NULL){
		if(cur->index == index){
			cur->data = data;
			return;
		}

		prev = cur;
		cur = cur->next;
	}

	// The index is not found
	prev->next = make_shared<node_t>(index, data);
}
