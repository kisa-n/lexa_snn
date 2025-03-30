#include "subnet.h"
#include"heron.h"


void subnet::work_subnet_in_tik(){
	
		for (int i = 0; i < num_input; i++) list_input[i].herons_work(this);
		for (int i = 0; i < num_inside; i++) list_inside[i].herons_work(this);
		for (int i = 0; i < num_output; i++) list_output[i].herons_work(this);
	
}

subnet::subnet()
{
}


subnet::~subnet(){
	queue_element* buffer_list = dellist,* iterator=0;
	dellist = 0;

	delete list_input;
	delete list_inside;
	delete list_output;
	// detected warning to create branch
	iterator = dellist;
	while (dellist) {
		iterator = dellist->nextquh;
		delete dellist;
		dellist = iterator;
	}
	dellist = buffer_list;
}

