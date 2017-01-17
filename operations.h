/* Importation des bibliothèques nécessaires au bon fonctionnement du programme */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

/* Valeur correspondant à la taille maximale d'un tableau correspondant à un polynôme */
#define DEGREMAX 10			/* en realite : DEGREMAX - 1, si DEGREMAX = 5, le degree reel max est 4, on commence a puissance 0 */

#define NBMAXPOLY 26
/* Définition d'un tableau de polynômes étant un tableau à double entrée pouvant contenir 10 polynômes */
typedef int polynome[NBMAXPOLY][DEGREMAX];

/* Nombre de caractères maximal que l'on peut taper sur l'entrée standard lorsque l'on veut entrer un polynôme*/
#define ENTREEMAX 200



/* Déclaration des prototypes des fonctions écrites dans operations.c 
 * Pour plus d'informations aller voir le fichier operations.c
 */
void init(int *, int );

int degre( int * );

void somme( int* , int* , int* );

void difference(int* , int* , int* );

void produit( int* , int* , int* );

void produitMonome( int* , int* , int* , int );

void derivation( int* , int* );

void integration( int* , int* );

void affectation( int * , int *);

void decalage( int * , int *, int);

void divEucl( int* , int* , int* , int*);

void factorisation(int* ,int* , int );

void ecriture (int* p);

void horner();
