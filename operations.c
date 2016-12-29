#include "operations.h"


void somme( int* p, int* q, int* res){
	for(int i = 0; i<DEGREMAX; i++){
		res[i] = p[i] + q[i];
	}
}

void ecriture (int* p){
	for(int i = 0; i<DEGREMAX-1; i++){
		printf("%d*x^%d+", p[i], i);
	}
	printf("%d*x^%d",p[DEGREMAX-1],DEGREMAX-1);
}
