#pragma once
#include"externs.h"
class heron;

class mconverterf {
public:
	char* outputs;
	float** input;
	int size[2], minT, *timers, *realTs;
	
	mconverterf(float**input, int m, int n, int minT = 23);
	~mconverterf() {
		free(timers);
		free(realTs);
		free(outputs);
	}
	
	void iteration();

	heron** v_retlist();

	//char*** m_retlist();

};