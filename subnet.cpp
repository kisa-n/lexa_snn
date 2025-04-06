#include "subnet.h"
#include"heron.h"


void subnet::work_subnet_in_tik(){
	
		for (int i = 0; i < num_input; i++)   list_input[i]->herons_work(this);
		for (int i = 0; i < num_inside; i++) list_inside[i]->herons_work(this);
		for (int i = 0; i < num_output; i++) list_output[i]->herons_work(this);
	
}

subnet::subnet()
{
}


subnet::~subnet(){
	queue_element* buffer_list = dellist;
	dellist = 0;

	free( list_input );
	free( list_inside);
	free( list_output);
	// detected warning to create branch
	delete_queue(dellist);
	dellist = buffer_list;
}

