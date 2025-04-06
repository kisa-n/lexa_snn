#pragma once
#include"externs.h"
class heron;

class subnet{
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



	heron** list_input = 0;
	heron** list_inside = 0;
	heron** list_output = 0;

	short num_input = 0; 
	short num_inside = 0;
	short num_output = 0;



	void work_subnet_in_tik();

	subnet();
	~subnet();
};

