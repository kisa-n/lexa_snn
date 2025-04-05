#pragma once
#include"externs.h"
#include"builder.h"
class heron;

enum class plase : char{
	INPUT = 'i',
	INSIDE = 's',
	OUTPUT = '0'
};

class subnet {
	heron** _new_layer(int len);

	heron** list_input = 0;
	heron** list_inside = 0;
	heron** list_output = 0;

	int  num_input = 0;
	int num_inside = 0;
	int num_output = 0;

	queue_element* my_dellist = 0;

public:

	char Time_reability = 23;//, tik

	// two-spikes plasticity:
	float c1_ = 0.002; //  _c1_ >= _kakie  -plast 2-blX spickes
	float c7_ = 0.001;  //  _c7_ >= _kakie !!!  -plast 2-blX spickes
	float c8_ = 0.3;      // umenshenie posle ~500 mc

	// gomeostat plasticity:
	short max_dif_gomeostat = (short)7;  // max change for gomeostat plast
	float measure_gomeostat_plast = 0.2;       //  ----------     na ckolko ^

	// adecvate plasticity:
	//     hebbovskaya plast:
	float ar_down = 0.05;
	float ar_up = 0.05;
	//     errors plast:
	float gjdiyc = 0.07;

	// sigms plastic:
	float weights_measure_different_sigm = 0.01;    //izmenenie isi ot raznizy vesov
	float times_measure_different_sigm = 0.01;    //izmenenie isi ot raznizy vremeni mezhdu cp i isi

	//  plasticity:
	float diff_stability_up = 0.1;
	float diff_stability_down = 0.1;

	void work_subnet_in_tik();

	subnet();
	~subnet();

	heron** new_layer(plase point, int len) {
		heron** res = nullptr;
		if (len <= 0)throw("");
		switch (point)
		{
		case plase::INPUT:
			res = _new_layer(len);
			if (list_input) {
				list_input = (heron**)realloc(list_input, sizeof(void*)*(num_input + len));

				for (int i = 0; i < len; i++) {
					list_input[i + num_input] = res[i];
				}
			}
			else list_input = copy(res, len);
			num_input += len;
			break;
		case plase::INSIDE:
			res = _new_layer(len);
			if (list_inside) {
				list_inside = (heron**)realloc(list_inside, sizeof(void*)*(num_inside + len));
				for (int i = 0; i < len; i++) {
					list_inside[i + num_inside] = res[i];
				}
			}
			else list_inside = copy(res, len);
			num_inside += len;
			break;
		case plase::OUTPUT:
			res = _new_layer(len);
			if (list_output) {
				list_output = (heron**)realloc(list_output, sizeof(void*)*(num_output + len));
				for (int i = 0; i < len; i++) {
					list_output[i + num_output] = res[i];
				}
			}
			else list_output = copy(res, len);
			num_output += len;
			break;
		default:
			break;
		}
		return res;
	}


	/*/ возможна утечка памяти
	/*inline heron** new_layer(heron* list, int len) {
	heron** res = (heron**)malloc(sizeof(void*)*len);
	for (int i = 0; i < len; i++) {
	res[i] = &list[i];
	}
	return res;
	}*/
};

