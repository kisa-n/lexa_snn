#include"queueh.h"
#include<stdlib.h>

bool quehappend(void* whus,/* int har,*/ queue_element**startque) {
	//fprintf(glog, "*q*");
	queue_element *newqueh = 0;
	queue_element *pque = 0;
	if (*startque ) {
		pque = *startque;
		while (pque->nextquh) {
			if ((pque->who == whus)/* && (pque->harackter == har)*/) {
				//fprintf(glog, ";q;");
				return(1);
		}
			pque = pque->nextquh;
		}
		if ((pque->who == whus) /*&& (pque->harackter == har)*/) { /*fprintf(glog, ";q;");*/ return(1); }
	}
	newqueh = new queue_element(whus,0);
	if (pque) pque->nextquh = newqueh;
	else *startque = newqueh;
	//fprintf(glog, ";q;");
	return(0);
}

void delete_queue(queue_element * &ptr){
	queue_element* iter = ptr;
	while (iter) {
		iter = ptr->nextquh;
		free(ptr->who);
		delete ptr;
		ptr = iter;
	}

}
