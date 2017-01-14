#include "operations.h"

void init(int * tab, int size)
{
	for(int i = 0; i < size; i++)
	{
		tab[i] = 0;
	}
}

int degre( int * p){
	for(int i = DEGREMAX-1; i>=0; i--){
		if(p[i] != 0) return i;
	}
	return -1;
}

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

void produitMonome( int* p, int* q, int* res, int pMon){
	for(int i = 0; i<DEGREMAX; i++){
		res[i+pMon] += p[i] * q[pMon];
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

void affectation(int * p, int * res){
	for(int i = 0; i<DEGREMAX; i++){
		res[i] = p[i];
	}
}

/*
 * Cette fonction permet de réaliser un décalage vers la droite d'un certain nombre de "cases"
 * d'un polynôme.
 * Exemple : decalage(1 + 3x + 4x^2 + 6x^3 , 2) = 4 + 6x
 */
void decalage( int * p, int * res, int nb){
	for( int i = nb; i<DEGREMAX; i++){
		p[i-nb] = p[i];
	}
}

void divEucl( int* N, int* D, int* Q, int * R){
	int d[DEGREMAX];
	/*
	 * Création d'un tableau qui sera au départ égal à N mais qui sera modifié tout au long du 
	 * processus via les soustractions successives de la boucle while (voir difference(Ntmp, d, Ntmp)
	 * Le but est de ne pas modifier le polynôme de départ N afin de pouvoir l'afficher.
	 */
	int Ntmp[DEGREMAX];
	/* On initialise le polynôme Ntmp afin de s'assurer qu'il soit composé seulement de zéros*/
	init(Ntmp, DEGREMAX);
	/* On affecte à Ntmp tous les monômes de N */
	affectation(N, Ntmp);
	/* Il faut vérifier que le degré du diviseur soit au moins nul car on ne peut diviser pas 0 */
	if (degre(D) < 0){
		printf("mauvais polynome entré");
		return;
	}
	//Q doit être initialiser à 0 avant l'appel de la fonction
	/* Invariant : degré(Ntmp) >= degré(D) */
	while (degre(Ntmp) >= degre(D)){
		/*On initialise le polynôme d à chaque tour de boucle afin de ne pas garder les monômes du
		 * tour de boucle précédent ce qui fausserait les résultats.
		 */
		init(d, DEGREMAX);
		Q[degre(Ntmp) - degre(D)] = Ntmp[degre(Ntmp)] / D[degre(D)];
		//multiplication du polynôme D avec le monôme courant du polynôme Q
		produitMonome(D, Q, d, degre(Ntmp) - degre(D));
		/* On soustrait le résultat de produitMonome() à Ntmp afin de baisser le degré de ce dernier et de recommencer une boucle */
		difference(Ntmp,d,Ntmp);
	}
	/* Lorsque toutes les opérations ont été réalisés et que degre(Ntmp) < degre(D),
	 * On affecte au reste le restant de Ntmp
	 */ 
	affectation(Ntmp, R);
}

//void factorisation(int* p, int* res){}

void ecriture (int* p){
	int zeroCounter;
	/*Si le polynome est nul on écrit qu'il est égale à 0 */
	if(degre(p) == -1){
		printf("0\n");
		return;
	}
	for(int i = DEGREMAX-1; i>=0; i--)
	{
		zeroCounter = 1;
		if( (p[i] != 0) && (i > 1) )
		{
			//Cette condition évite d'afficher un coefficient 1 devant une variable x^n
			if(p[i] == 1) printf("x^%d",i);
			else printf("%dx^%d", p[i], i);
			while(p[i-zeroCounter]==0) zeroCounter++;
			if(p[i-zeroCounter] >= 0)
			{
				printf("+");
			}
		}
		else if ( (p[i] != 0) && (i == 1) )
		{
			if(p[i] == 1) printf("x");
			else printf("%dx",p[i]);
			while(p[i-zeroCounter]==0) zeroCounter++;
			if(p[i-zeroCounter] >= 0)
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


