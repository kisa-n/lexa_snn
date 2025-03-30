#pragma once
#include "externs.h"
//#include"heron.h"
//#include"subnet.h"
class subnet;
class heron;

enum class position : int
{
	NORMAL = 0,
	START_REAB =1,
	IN_REAB=2,
	ERR_IN_REAB=3
};

class branch/*:private links*/{
public:
	float sigms_starts_num=0, sum_weights_past_sp = 0, charact_time_between_sp = 5;//chtbs-вначале ненулевое
	char num_lately_sp = 0, num_links, counter_latest_sp = 0;
	short counter_sigm=0, counter_gomeostat=0; 

	unsigned long flags = 0, flags2=0;//32
	char* counters = 0;
	signed char* diffs = 0;
	heron** m_links = 0;
	float* links_weights = 0;


	float normal_tik( subnet* may_layer, float stability);
	float normal_in_reab( subnet* may_layer, float stability);
	
	void start_reab(subnet* may_layer, float stability);
	void err_in_reab(subnet* may_layer, float stability);


	void update_counters_and_gomeostat();
	void gomeostatics_change(subnet* may_layer, float stability);

	void two_spikes_change(int iterator, subnet* may_layer);

//public:

	inline float change_all(position provise, subnet* may_layer, float stability);

	void create(int num_links, heron** links, float* weights);

	branch() {}
	~branch();
};

inline float branch::change_all(position provise, subnet * may_layer, float stability) {
	switch (provise)
	{
	case position::NORMAL:
		return normal_tik( may_layer, stability);
	case position::START_REAB:
		start_reab(may_layer, stability);
		return (float)0;
	case position::IN_REAB:
		return normal_in_reab( may_layer, stability);
	case position::ERR_IN_REAB:
		err_in_reab( may_layer, stability);
		return (float)0;
	}
	return 0;
}

