#include "linkedList.h"


int main()
{
	LinkedList l;
	l.print();

	l.insert_data(0, 12);
	l.insert_data(0, 24);
	l.insert_data(1, 34);
	l.insert_data(0, 14);

	l.print();
}