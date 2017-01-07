#include "operations.h"


void somme( int* p, int* q, int* res){
	for(int i = 0; i<DEGREMAX; i++){
		res[i] = p[i] + q[i];
	}
}

void difference(int* p, int* q, int* res){
	for(int i = 0; i<DEGREMAX; i++){
		res[i] = p[i] - q[i];
	}
}

void produit( int* p, int* q, int* res){
	for(int i = 0; i<DEGREMAX; i++){
		for(int j = 0; j<DEGREMAX; j++){
			res[i+j] += p[i] * q[j];
		}
	}
}

void derivation( int* p, int* res){
	for(int i = 0; i<DEGREMAX-1 ; i++){
		res[i] = (i+1)*p[i+1];
	}
}

/*
 * Pour pouvoir réaliser la fonction integration(), il faut 
 * manipuler des tableaux de doubles puisque les coefficients
 * seront des fractions. ex : primitive de 4x^5 = (4/6)x^6
 */
void integration( int* p, int* res){
	
}

void divEucl( int* p, int* q, int* res){
	
}

//void factorisation(int* p, int* res){}

void ecriture (int* p){
	for(int i = DEGREMAX-1; i>=0; i--)
	{
		if( (p[i] != 0) && (i > 1) )
		{
			printf("%dx^%d", p[i], i);
			if( (p[i-1] != 0) && (p[i-1] > 0) )
			{
				printf("+");
			}
		}
		else if ( (p[i] != 0) && (i == 1) )
		{
			printf("%dx",p[i]);
			if( (p[i-1] != 0) && (p[i-1] > 0) )
			{
				printf("+");
			}
		}
		else if ( (p[i] != 0) && (i == 0) )
		{
			printf("%d",p[i]);
		}
	}
	printf("\n");
}

void horner(){}


