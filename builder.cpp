#include "builder.h"



builder::builder()
{
}


builder::~builder()
{
}

float** builder::collapc_link(int pkrt, heron * frw, int sfx, int sfy, heron * wto, int stx, int sty) {
//пока нет?
	return nullptr;
}

void builder::linking(heron * from_where, int size_fr, heron * where_to, int size_to) {
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


