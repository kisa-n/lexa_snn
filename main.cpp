#include"externs.h"
#include"builder.h"
#include"subnet.h"
#include"heron.h"
#include"converter.h"
#include"branch.h"

int main() {
// create inputs matrica 5x1:
/*
	int len = 45;
	float * nets_input = new float[len];
	mconverterf* conv=new mconverterf(&nets_input, len, 1);
// create one heron:
	*/
// create links to tests hero:
	//tests_h->create_links(conv->v_retlist(), len);
// herons work
// пока нет?
// delete all:
	
	heron** h = new heron*[2]{nullptr};
	h[0] = new heron();
	h[1] = new heron();

	h[1]->create_links(h, 2);

	

	//delete(b1);
	delete(h[1]);
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
