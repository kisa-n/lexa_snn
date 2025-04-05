#include "subnet.h"
#include"heron.h"


void subnet::work_subnet_in_tik(){
	
		for (int i = 0; i < num_input; i++) list_input[i]->herons_work(this);
		for (int i = 0; i < num_inside; i++) list_inside[i]->herons_work(this);
		for (int i = 0; i < num_output; i++) list_output[i]->herons_work(this);
	
}

heron ** subnet::_new_layer( int len){
	
	heron* list = (heron*)malloc(sizeof(heron)*len);
	for (int i = 0; i < len; i++) list[i]._heron();
	quehappend(list, &my_dellist);
	heron** res = (heron**)malloc(sizeof(void*)*len);
	for (int i = 0; i < len; i++) {
		res[i] = &list[i];
	}
	return res;
	
}

subnet::subnet()
{
}


subnet::~subnet(){
	queue_element* buffer_list = dellist;
	dellist = 0;

	for (int i = 0; i < num_input; i++)
		list_input[i]->~heron();
	for (int i = 0; i < num_inside; i++)
		list_inside[i]->~heron();
	for (int i = 0; i < num_output; i++)
		list_output[i]->~heron();
	
	delete_queue(my_dellist);

	free( list_input );
	free( list_inside);
	free( list_output);

	// detected warning to create branch - потенциальная ошибка устранена
	delete_queue(dellist);
	dellist = buffer_list;

	list_input = 0;
	list_inside = 0;
	list_output = 0;
	num_input = 0;
	num_inside = 0;
	num_output = 0;
}

