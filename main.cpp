#include"externs.h"
#include"builder.h"
#include"subnet.h"
#include"heron.h"
#include"converter.h"

int main() {
// create inputs matrica 5x1:
/*
	int len = 5;
	float * nets_input = new float[len];
	mconverterf conv(&nets_input, len, 1);*/
// create one heron:
	heron tests_h;
// create links to tests hero:
	//tests_h.create_links(conv.v_retlist(), len);
// herons work
// пока нет?
// delete all:
	delete(&tests_h);
	delete_queue(dellist);

	printf("the end\n");
	/*
	tests_h.activations = 1;

	FILE*trash;
	fopen_s(&trash, "tr.txt", "w");
	fwrite(&tests_h, sizeof(heron), 1, trash);
	*/

	return(0);

}
