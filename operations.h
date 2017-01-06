#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define DEGREMAX 10			/* en realite : DEGREMAX - 1, si DEGREMAX = 5, le degree reel max est 4, on commence a puissance 0 */
typedef int polynome[DEGREMAX];
#define ENTREEMAX 200



void somme( int* , int* , int* );
void difference(int* , int* , int* );
void produit( int* , int* , int* );
void derivation( int* , int* );
void integration( int* , int* );
void divEucl( int* , int* , int* );
void ecriture (int* p);
void horner();
