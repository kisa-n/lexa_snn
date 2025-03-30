#include "builder.h"
#include"heron.h"


float ** restructer_copyf(float *start_list, int len) {
	float**result = new float*[(len + 31) / 32];
	int i;
	for (i = 0; i < len / 32; i++) {
		result[i] = new float[32];
		for (int j = 0; j < 32; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}
	if ((len + 31) / 32 > i) {
		result[i] = new float[len - (len / 32) * 32];
		for (int j = 0; j <len-(len / 32)*32 ; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}

	return result;
}

heron*** restructer_copyh(heron**start_list, int len) {
	heron***result = new heron**[(len + 31) / 32];
	int i;
	for (i = 0; i < len / 32; i++) {
		result[i] = new heron*[32];
		for (int j = 0; j < 32; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}
	if ((len + 31) / 32 > i) {
		result[i] = new heron*[len - (len / 32) * 32];
		for (int j = 0; j <len - (len / 32) * 32; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}
	return result;
}


float** collapc_link(int pkrt, heron * frw, int sfx, int sfy, heron * wto, int stx, int sty) {
//пока нет?
	return nullptr;
}

void linking(heron * from_where, int size_fr, heron * where_to, int size_to) {
	float* weights = 0;
	heron** ptr = new heron*[size_fr];

	for (int i = 0; i < size_fr; i++) {
		ptr[i] = &from_where[i];
	}

	for (int i = 0; i < size_to; i++) {

		weights = new float[size_fr];
		for (int j = 0; j < size_fr; j++) {
			weights[j] = ((float)rand() - 20) / ((float)1000);
		}

		where_to[i].create_links(ptr, weights, size_fr);

	}
}


