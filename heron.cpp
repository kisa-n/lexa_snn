#include "heron.h"
#include"branch.h"
#include"subnet.h"


void heron::herons_in_reab(subnet* may_layer){
	int i = 0;
	float sum_all = 0;

	for (int i = 0; i < num_stacks_brances; i++) {
		for (int j = 0; j<numbers_branches[i]; j++)
			sum_all += branches[i][j].change_all(position::IN_REAB, may_layer, stability);
	
	}
	if (sum_all >= _herons_activations_lim) {
		
		if (stability > 1 + may_layer->diff_stability_up + may_layer->diff_stability_down) {
			stability -= may_layer->diff_stability_down + may_layer->diff_stability_up;
		}
		else if (stability > 1 + may_layer->diff_stability_up) {
			stability -= may_layer->diff_stability_up;
		}


		for (int i = 0; i < num_stacks_brances; i++) {
			for (int j = 0; j<numbers_branches[i]; j++)
				branches[i][j].change_all(position::ERR_IN_REAB, may_layer, stability);
		}

	}
}


heron::~heron(){

	for (int i = 0; i < num_stacks_brances; i++){
		delete branches[i];
	}
	if(branches)delete branches;
	if(numbers_branches)delete numbers_branches;
}

void heron::herons_work(subnet * may_layer){
		
	if (counter_reab) {
		if (tik) {
			counter_reab--;
			//deactivation:
				activations = activations & ((char)254);
		}
		else {
			herons_in_reab(may_layer);
		}
		return;
	}
	
	// herons "normal":
		if (tik) {
			activations = activations / 2;
			return;
		}
	
	if (activations % 2) {
		// herons "start reab":
			for (int i = 0, j; i < num_stacks_brances; i++) {
				for(j=0;j<numbers_branches[i];j++)
					branches[i][j].change_all(position::START_REAB, may_layer, stability);
			}
			counter_reab = may_layer->Time_reability;
			stability+= may_layer->diff_stability_up;
			
			herons_in_reab(may_layer);
	
		return;
	}
	else {
	// herons "normal":
		float sum_all = 0;

		for (int i = 0, j; i < num_stacks_brances; i++) {
			for (j = 0; j<numbers_branches[i]; j++)
				sum_all += branches[i][j].change_all(position::NORMAL, may_layer, stability);
		}
		if (sum_all >= _herons_activations_lim) {
			activations = activations | ((char)2);
		}

	}

}

//it is impractical to create links in a number that is not a multiple of 32
void heron::create_links(heron ** senders, float * weights, char n_links){
	int i = 0;
	sizeof(branch);
	
	if (branches){
		branches = (branch**)realloc(branches, num_stacks_brances++);
	}
	else {
		branches = (branch**)malloc(sizeof(void*));
		num_stacks_brances = 1;
	}

	branches[num_stacks_brances - 1] = new branch[(n_links + 31) / 32];
	for (i = 0; i < n_links / 32; i++) {
		branches[num_stacks_brances - 1][i].create(n_links - i * 32, senders, weights);
	}
	if (int num_end = n_links - i * 32) {
		branches[num_stacks_brances - 1][i].create(n_links - i * 32, senders, weights);
	}
	if(numbers_branches)
		numbers_branches = (char*)realloc(numbers_branches, sizeof(char)*num_stacks_brances);
	else numbers_branches = (char*)malloc(1);
	numbers_branches[num_stacks_brances - 1] = (n_links + 31) / 32;
}



