#include "heron.h"
#include"branch.h"
#include"subnet.h"
#include"builder.h"
#include <stdexcept>

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

	if (branches) {
		for (int i = 0; i < num_stacks_brances; i++) {
			delete [] branches[i];
		}
        free(branches);
	}
	if(numbers_branches)
        free(numbers_branches);
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

void heron::create_links32(heron *** senders, float ** weights, char n_links){
	int i = 0;

	if (branches) {
        if (0 == num_stacks_brances)
        {
            throw std::runtime_error("num_stacks_brances = 0");
        }
		branches = (branch**)realloc(branches, sizeof(void*)*(num_stacks_brances++));
	}
	else {
		branches = (branch**)malloc(sizeof(void*));
		num_stacks_brances = 1;
	}

	branches[num_stacks_brances - 1] = new branch[(n_links+31)/32];
	for (i = 0; i < n_links / 32; i++) {
		branches[num_stacks_brances - 1][i].create(32, senders[i], weights[i]);
	}
	if (int num_end = n_links%32) {
		branches[num_stacks_brances - 1][i].create(num_end, senders[i], weights[i]);
	}
	if (numbers_branches)
		numbers_branches = (char*)realloc(numbers_branches, sizeof(char)*num_stacks_brances);
	else numbers_branches = (char*)malloc(sizeof(char));
	numbers_branches[num_stacks_brances - 1] = (n_links + 31) / 32;

}

// warning: will by deleted 'senders' and 'weights'
void heron::create_links(heron ** senders, float * weights, char n_links) {

	create_links32(hrestructer32(senders, n_links), frestructer32(weights, n_links), n_links);

}

void heron::create_links(heron ** senders, char n_links) {
	float**result = (float**)malloc(sizeof(float*)*((n_links + 31) / 32));
	int i;
	for (i = 0; i < n_links / 32; i++) {
		result[i] = (float*)malloc(sizeof(float)*32);
		for (int j = 0; j < 32; j++) {
			result[i][j] = ((float)rand() - (float)20) / _st_wei;
		}
	}
	if (int end_num = n_links%32) {
		result[i] = (float*)malloc(sizeof(float) * end_num);
		for (int j = 0; j <end_num; j++) {
			result[i][j] = ((float)rand() - (float)20) / _st_wei;
		}
	}

	create_links32(__hrestructer32(senders, n_links), result, n_links);
}
