#include "converter.h"

mconverterf::mconverterf(float**input, int m, int n, int minT)
:input(input), minT(minT)
{
	size[0] = m;
	size[1] = n;
	timers = (int*)malloc(sizeof(int)*n*m);
	
	long long nerr = (long long)timers;
	nerr = nerr* (long long)(realTs = (int*)malloc(sizeof(int)*n*m));
	nerr = nerr*  (long long)(outputs = new char[n*m]{0});
	
	if (0 == nerr)printf("crashed programm in mconverterf::mconverterf(...):\n\t oshibka kuchy\n");
}

void mconverterf::iteration() {

	for (int i = 0, j; i < size[1]; i++) {
		
		for (j = 0; j < size[0]; j++) {

			if (outputs[i*size[0] + j])
				outputs[i*size[0] + j] = 0;
			
			if (input[j][i] >= 1) {
				
				realTs[i*size[0] + j] =(int)( minT * 100 / log(input[j][i]));	
				if (realTs[i*size[0] + j] < timers[i*size[0] + j]) timers[i*size[0] + j] = realTs[i*size[0] + j];
			
			}

			timers[i*size[0] + j]--;
			if (timers[i*size[0] + j] == 0) {
				outputs[i*size[0] + j] = 1;
				timers[i*size[0] + j] = realTs[i*size[0] + j];
			}
		}

	}


}

heron** mconverterf::v_retlist() {
	char** result = (char**)malloc(sizeof(void*)*size[0]*size[1]);
	result[0] = outputs;
	for (int j = 1; j < size[1]*size[0]; j++)
		result[j] = (char*)((long long)result[0] + (long long)j);
	return((heron**)result);
}


/*char** mconverterf::retlist() {
	char** result = (char**)malloc(sizeof(void*)*size[0]);
	
	for (int i = 0; i < size[0]; i++) {
		result[i] = (char**)malloc(sizeof(void*)*size[1]);
	}
	
	for (int i = 0, j; i < size[0]; i++) {
		result[i][0] = &otput[i*size[1]];
		for (j = 1; j < size[1]; j++)
			result[i][j] = (char*)((int)result[i][0] + j);
	}
	
	return(result);
	}*/