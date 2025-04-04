#include"externs.h"
#include"builder.h"
#include"subnet.h"
#include"heron.h"
#include"converter.h"
#include"branch.h"
//#include<iostream>

int main() {
// create inputs 

	int len = 45;
	float * nets_input = (float*)malloc(sizeof(float)*len);
	mconverterf* conv=new mconverterf(&nets_input, 1, len);

	for (int i = 0; i < len; i++) {
		nets_input[i] = ((float)rand()) / 20;
	}

	// create one heron:
	/*heron* h = new heron();
// create links to tests hero:
	h->create_links(conv->v_retlist(), len);
// herons work
// пока нет?
// delete all:
	delete(h);*/
	/*
	heron** h = (heron**)malloc(sizeof(heron*) * 2);
	h[0] = new heron();
	h[1] = new heron();

	h[1]->create_links(copy(h,2), 2);
	*/
	
	
	subnet nh;
	/*
	heron* lay1 = new heron[32], *lay2 = new heron[10], *h =new heron();
	linking_a(lay1, 32, lay2, 10);
	heron**la1__ = new_layer(lay1, 32);
	h->create_links(la1__, 32);

	linking_b(conv->v_retlist(), len, la1__, 32);

	heron** la2__ = new_layer(lay2, 10);
	h->create_links(la2__, 10);
	*/
	nh.list_input = new heron [32];
	nh.list_inside = new heron[10];
	nh.list_output= new heron();

	nh.num_input =32;
	nh.num_inside=10;
	nh.num_output=1;

	linking_a(nh.list_input, 32, nh.list_inside, 10);
	heron**la1__ = new_layer(nh.list_input, 32);
	nh.list_output->create_links(la1__, 32);

	linking_b(conv->v_retlist(), len, la1__, 32);

	heron** la2__ = new_layer(nh.list_inside, 10);
	nh.list_output->create_links(la2__, 10);

	for (int i = 0; i < 1000; i++) {
		tik=0;
		nh.work_subnet_in_tik();
		tik = 1;
		nh.work_subnet_in_tik();
		tiks_counter++;
		conv->iteration();
		for (int j = 0; j < 32; j++) {
			if (nh.list_input[j].activations)
				printf("t");
			else printf("0");
		}
		printf("\n");
		for (int j = 0; j < 10; j++) {
			if (nh.list_inside[j].activations)
				printf("t");
			else printf("0");
		}
		if(nh.list_output->activations)
			printf("\nt\n");
		else printf("\n0\n");
			if (i % 100 == 0)
			printf("\n");
	}
	//delete(h[1]);
	//delete_queue(dellist);

	printf("the end\n");
	/*
	tests_h.activations = 1;

	FILE*trash;
	fopen_s(&trash, "tr.txt", "w");
	fwrite(&tests_h, sizeof(heron), 1, trash);
	*/

	return(0);

}
