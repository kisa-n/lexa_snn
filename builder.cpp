#include "builder.h"
#include"heron.h"

// will deleted starts list
float ** frestructer32(float* &start_list, int len) {
	float**result = (float**)malloc(sizeof(float*) * ((len + 31) / 32)); 
	int i;
	for (i = 0; i < len / 32; i++) {
		result[i] = (float*)malloc(sizeof(float) * 32);
		for (int j = 0; j < 32; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}
	if (int end_num = len - i * 32) {
		result[i] = (float*)malloc(sizeof(float) * 32);
		for (int j = 0; j <end_num; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}
	free( start_list);
	start_list = 0;
	return result;
}

// will deleted starts list
heron*** hrestructer32(heron** &start_list, int len) {
	heron***result = (heron***)malloc(sizeof(heron**)*((len + 31) / 32));
	int i;
	for (i = 0; i < len / 32; i++) {
		result[i] = (heron**)malloc(sizeof(heron*)*32);
		for (int j = 0; j < 32; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}
	if (int end_num= len - i*32) {
		result[i] = (heron**)malloc(sizeof(heron*) * end_num);
		for (int j = 0; j <end_num; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}
	free(start_list);
	start_list = 0;
	return result;
}


float** collapc_link(int pkrt, heron * frw, int sfx, int sfy, heron * wto, int stx, int sty) {
//пока нет?
	return nullptr;
}

void linking(heron * from_where, int size_fr, heron * where_to, int size_to) {
	float* weights = 0;
	heron** ptr = (heron**)malloc(sizeof(heron*) * size_fr);

	for (int i = 0; i < size_fr; i++) {
		ptr[i] = &from_where[i];
	}

	for (int i = 0; i < size_to; i++) {

		weights = (float*)malloc(sizeof(float) * size_fr);
		for (int j = 0; j < size_fr; j++) {
			weights[j] = ((float)rand() - 20) / ((float)1000);
		}

		where_to[i].create_links(ptr, weights, size_fr);

	}
}


