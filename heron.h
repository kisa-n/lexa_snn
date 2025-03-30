#pragma once
#include"externs.h"

class subnet;
class branch;

class heron{
	float stability=1; // ý[1;+<x>)
	branch** branches = nullptr; 

	void herons_in_reab(subnet* may_layer);

public:

	char activations=0, num_stacks_brances=0, counter_reab = 0;
	char* numbers_branches = 0;
	

	heron() {}
	~heron();

	void herons_work(subnet* may_layer);

	//it is impractical to create links in a number that is not a multiple of 32
	void create_links(heron**senders, float* weights, char n_links);

};

