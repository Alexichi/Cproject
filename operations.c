#include "operations.h"


void somme( int* p, int* q, int* res){
	for(int i = 0; i<DEGREMAX; i++){
		res[i] = p[i] + q[i];
	}
}

void difference(int* p, int* q, int* res){
	
}

void produit( int* p, int* q, int* res){
	
}

void derivation( int* p, int* res){
	
}

void integration( int* p, int* res){
	
}

void divEucl( int* p, int* q, int* res){
	
}

//void factorisation(int* p, int* res){}

void ecriture (int* p){
	for(int i = DEGREMAX-2; i>=0; i--){
		if(p[i] != 0){
			printf("%dx^%d + ", p[i], i);
		}
	}
	printf("%d ",p[0]);
}

void horner(){}


