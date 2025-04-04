#include "branch.h"
#include"externs.h"
#include"subnet.h"
#include"heron.h"

bool tik = 0;
char tiks_counter = 1;
queue_element* dellist;

float branch::normal_tik( subnet * may_layer, float stability){
	float sum_weights_new_sp = 0;
	
	counter_sigm++;
	if (counter_latest_sp)counter_latest_sp++;
	update_counters_and_gomeostat();
	
	// get_number_sigm:
		float atmp = expf((_l_o_w) / charact_time_between_sp*counter_sigm);
		float num_sigm = -sigms_starts_num*(atmp / (atmp + 1) - 1);
	
	if (counter_sigm >= charact_time_between_sp)flags = 0;

	// detected spikes:
		for (char i = 0; i < num_links; i++) {
			if (m_links[i]->activations % 2) {

				// response:
					two_spikes_change(i, may_layer);

				sum_weights_new_sp += links_weights[i];
				flags = flags | stepen2(i);
			}
		}

	gomeostatics_change(may_layer, stability);

	// response_for_received_spikes:
		if (sum_weights_new_sp){

			// update sigm:
				sigms_starts_num = sum_weights_new_sp + num_sigm;
				counter_sigm = (short)(-2 * charact_time_between_sp);
			// change charact_time_between_sp:
				atmp = (float)counter_latest_sp - charact_time_between_sp - 1;
				charact_time_between_sp += ((sum_weights_past_sp - sum_weights_new_sp)*may_layer->weights_measure_different_sigm + atmp*may_layer->times_measure_different_sigm) / (1 + ((atmp < 0) ? -atmp : atmp)) / stability; 
			sum_weights_past_sp = sum_weights_new_sp;
			counter_latest_sp = 1;
		}

	return sum_weights_new_sp + num_sigm;
}

float branch::normal_in_reab( subnet * may_layer, float stability) {
	float sum_weights_new_sp = 0;

	counter_sigm++;
	if (counter_latest_sp)counter_latest_sp++; 
	if (counter_sigm >= charact_time_between_sp)flags = 0;

	update_counters_and_gomeostat();

	for (char i = 0; i < num_links; i++) {
		if (m_links[i]->activations % 2) {
			sum_weights_new_sp += links_weights[i];
			if (!(flags2 & stepen2(i))) {
				links_weights[i] -= may_layer->ar_down / stability;
			}
			flags2 = flags2 | stepen2(i);
		}
	}

	// response_for_received_spikes:
		if (sum_weights_new_sp) {
			// get_number_sigm:
				float atmp = expf((_l_o_w) / charact_time_between_sp*counter_sigm);
				float num_sigm = -sigms_starts_num*(atmp / (atmp + 1) - 1);
			// update sigm:
				sigms_starts_num = sum_weights_new_sp + num_sigm;
				counter_sigm = (short)(-2 * charact_time_between_sp);
			// change charact_time_between_sp:
				atmp = (float)counter_latest_sp - 1 - charact_time_between_sp;
				charact_time_between_sp += ((sum_weights_past_sp - sum_weights_new_sp)*may_layer->weights_measure_different_sigm + atmp*may_layer->times_measure_different_sigm) / (1 + ((atmp < 0) ? -atmp : atmp)) / stability;
			sum_weights_past_sp = sum_weights_new_sp;
			counter_latest_sp = 1;
		}

	return sum_weights_new_sp;
}

void branch::err_in_reab( subnet * may_layer, float stability) {
	if (flags) {
		for (int i = 0; i < num_links; i++) {
			if (flags & stepen2(i)) {
				links_weights[i] -= may_layer->ar_up / ((float)stability) + may_layer->gjdiyc;
			}
		}
		flags = 0;
	}
}

void branch::start_reab(subnet * may_layer, float stability) {
	flags2 = 0;
	if (flags) {
		for (char i = 0; i < num_links; i++) {
			if (flags & stepen2(i)) {
				links_weights[i] += may_layer->ar_up / ((float)stability);
			}
		}
	}
}

void branch::update_counters_and_gomeostat() {
	char new_num_sp = 0;

	if (tiks_counter == 0)
		for (int i = 0; i < num_links; i++) {
			if (counters[i]) {
				counters[i]++;
			}
			new_num_sp += m_links[i]->activations % 2;
		}
	else for (int i = 0; i < num_links; i++) {
		if (counters[i] && counters[i] < 230) {
			counters[i]++;
		}
		new_num_sp += m_links[i]->activations % 2;
	}

	counter_gomeostat += new_num_sp - num_lately_sp;
	num_lately_sp = new_num_sp;
}

void branch::gomeostatics_change(subnet* may_layer, float stability) {

	if (-may_layer->max_dif_gomeostat >= counter_gomeostat) {
		counter_gomeostat = 0;
		for (int i = 0; i < num_links; i++) {
			links_weights[i] += may_layer->measure_gomeostat_plast / stability;
		}
	}
	else if (may_layer->max_dif_gomeostat <= counter_gomeostat) {
		counter_gomeostat = 0;
		for (int i = 0; i < num_links; i++) {
			links_weights[i] -= may_layer->measure_gomeostat_plast / stability;
		}
	}

}


inline void branch::two_spikes_change(int i, subnet* may_layer){
	if (counters[i]) {
		if (counters[i] < _tall_v) {
			diffs[i] += (signed char)( may_layer->c7_*_kakie );
			diffs[i] += (signed char)( ( (float)1 / ((float)1 + (links_weights[i] >= 0 ? links_weights[i] : -links_weights[i])) - (float)1 )*may_layer->c1_*_kakie );
		}
		else if (counters[i] < 230) {
			links_weights[i] += ((float)diffs[i]) / _kakie;
			diffs[i] = (signed char)(((float)1 / ((float)1 + (links_weights[i] >= 0 ? links_weights[i] : -links_weights[i])) - (float)1)*may_layer->c1_*_kakie);
		}
		else {
			links_weights[i] += ((float)diffs[i]) / _kakie + may_layer->c7_ ;
			diffs[i] = (signed char)(((float)1 / ((float)1 + (links_weights[i] >= 0 ? links_weights[i] : -links_weights[i])) - (float)1)*may_layer->c1_*_kakie);
		}
	}
	else {
		if (diffs[i]) {
			links_weights[i] += ((float)diffs[i] / (float)_kakie + may_layer->c7_ ) * may_layer->c8_;
			diffs[i] = 0;
		}
		diffs[i] += (signed char)(((float)1 / ((float)1 + (links_weights[i] >= 0 ? links_weights[i] : -links_weights[i])) - (float)1)*may_layer->c1_*_kakie);
	}
}

void branch::create(int n_links, heron ** links, float * weights){
	num_links = n_links;
	m_links = links;
	links_weights = weights;

	counters = new char[n_links] {0};
	diffs = new signed char [n_links] {0};
}


branch::~branch(){
	if (counters)delete[] counters;
	if (diffs)delete[] diffs;
	if (m_links)quehappend(m_links, &dellist);
	if (links_weights)quehappend(links_weights, &dellist);
	counters = 0;
	diffs = 0;
	m_links = 0;
	links_weights = 0;
}
/*
void branch::destroed(){
	if (counters)delete[] counters;
	if (diffs)delete [] diffs;
	if (m_links)quehappend(m_links, &dellist);
	if (links_weights)quehappend(links_weights, &dellist);
	counters = 0;
	diffs = 0;
	m_links = 0;
	links_weights = 0;
}
*/
