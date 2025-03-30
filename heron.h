#pragma once
#include"externs.h"

class subnet;
class branch;

class heron{
public:
	char activations = 0;

	heron() {}
	~heron();

	void herons_work(subnet* may_layer);

	//it is impractical to create links in a number that is not a multiple of 32
	void create_links(heron**senders, float* weights, char n_links);
	//it is impractical to create links in a number that is not a multiple of 32
	inline void create_links(heron**senders, char n_links);
private:
	char num_stacks_brances = 0, counter_reab = 0;
	float stability = 1; // ý[1;+<x>)
	branch** branches = nullptr;
	char* numbers_branches = 0;
	void herons_in_reab(subnet* may_layer);
};

void heron::create_links(heron ** senders, char n_links) {
	float* weights = new float[n_links];
	for (int i = 0; i < n_links; i++) {
		weights[i] = ((float)rand() - (float)20) / (float)1000;
	}
	create_links(senders, weights, n_links);
}