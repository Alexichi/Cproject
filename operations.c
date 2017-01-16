#include "operations.h"

/*
 * Fonction permettant d'initialiser un polynôme qui est un tableau en mettant toutes
 * les cases à 0.
 * Paramètres : tab, un tableau d'entier
 * 				size, la taille du tableau
 */
void init(int * tab, int size)
{
	for(int i = 0; i < size; i++)
	{
		tab[i] = 0;
	}
}

/*
 * Fonction permettant de connaître le degré d'un polynôme
 * Paramètre : p, un polynôme
 * Retourne un entier qui est le degré du polynôme
 */
int degre( int * p){
	/* on parcours le polynôme */
	for(int i = DEGREMAX-1; i>=0; i--){
		if(p[i] != 0) return i;
	}
	/* Si le polynôme est nulle on renvoi la valeur -1 (en théorie on devrait renvoyer la valeur -infini) */
	return -1;
}

/*
 * Fonction permettant de faire la somme de 2 polynôme
 * Paramètres : p, polynôme
 * 				q, polynôme
 * 				res, résultat de p+q
 */
void somme( int* p, int* q, int* res){
	for(int i = 0; i<DEGREMAX; i++){
		res[i] = p[i] + q[i];
	}
}

/*
 * Fonction permettant de faire la différence de 2 polynôme
 * Paramètres : p, polynôme
 * 				q, polynôme
 * 				res, résultat de p-q
 */
void difference(int* p, int* q, int* res){
	for(int i = 0; i<DEGREMAX; i++){
		res[i] = p[i] - q[i];
	}
}

/*
 * Fonction permettant de faire le produit de 2 polynôme
 * Paramètres : p, polynôme
 * 				q, polynôme
 * 				res, résultat de p*q
 */
void produit( int* p, int* q, int* res){
	for(int i = 0; i<DEGREMAX; i++){
		for(int j = 0; j<DEGREMAX; j++){
			res[i+j] += p[i] * q[j];
		}
	}
}

/*
 * Fonction permettant de faire le produit d'un polynôme avec un monôme
 * Paramètres : p, polynôme
 * 				q, monôme de degré pMon
 * 				res, résultat de p*q
 */
void produitMonome( int* p, int* q, int* res, int pMon){
	for(int i = 0; i<DEGREMAX; i++){
		res[i+pMon] += p[i] * q[pMon];
	}
}

/*
 * Fonction permettant de faire la dérivée d'un polynôme
 * Paramètres : p, polynôme à dériver
 * 				res, résultat de p'
 */
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

/*
 * Fonction permettant de faire p=q avec p et q deux polynômes.
 * On copie le contenu du polynôme p dans le polynôme q.
 * Paramètres : p, un polynôme
 * 				res, le polynôme qui sera égale à p
 */
void affectation(int * p, int * res){
	for(int i = 0; i<DEGREMAX; i++){
		res[i] = p[i];
	}
}

/*
 * Cette fonction permet de réaliser un décalage vers la droite d'un certain nombre de "cases"
 * d'un polynôme.
 * Exemple : decalage(1 + 3x + 4x^2 + 6x^3 , 2) = 4 + 6x
 * Paramètres : p, un polynôme
 * 				res, le polynôme résultat qui a subit un décalage nb
 */
void decalage( int * p, int * res, int nb){
	for( int i = nb; i<DEGREMAX; i++){
		p[i-nb] = p[i];
	}
}

/*
 * Fonction permettant de réaliser la division euclidienne entre deux polynômes
 * Paramètres : N, le polynôme à diviser
 * 				D, le polynôme diviseur
 * 				Q, le quotient de la division de N par D
 * 				R, le reste de la division de N par D 
 */
void divEucl( int* N, int* D, int* Q, int * R){
	int d[DEGREMAX];
	/*
	 * Création d'un tableau qui sera au départ égal à N mais qui sera modifié tout au long du 
	 * processus via les soustractions successives de la boucle while (voir difference(Ntmp, d, Ntmp))
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


/*
 * Fonction permettant d'afficher un polynôme sur la sortie standard (Terminal) de manière litérale
 * et lisible par l'utilisateur.
 * Paramètre : p, le polynôme à afficher qui est sous forme d'un tableau d'entier
 */
void ecriture (int* p){
	/* variable servant à éviter d'afficher un + si le(s) coefficient(s) précédent est(sont) nul(s)*/
	int zeroCounter;
	/* Si le polynome est nul on écrit qu'il est égale à 0 */
	if(degre(p) == -1){
		printf("0\n");
		return;
	}
	/* On parcourt le polynôme */
	for(int i = DEGREMAX-1; i>=0; i--)
	{
		zeroCounter = 1;
		/* Dans le cas où on a un monôme courant du type ax^n avec a et n non nuls */
		if( (p[i] != 0) && (i > 1) )
		{
			//Cette condition évite d'afficher un coefficient 1 devant une variable x^n
			if(p[i] == 1) printf("x^%d",i);
			else printf("%dx^%d", p[i], i);
			
			while(p[i-zeroCounter]==0 && (zeroCounter <= i)) zeroCounter++;
			if(p[i-zeroCounter] > 0)
			{
				printf("+");
			}
		}
		/* Dans le cas où on a un monôme courant du type ax */
		else if ( (p[i] != 0) && (i == 1) )
		{
			if(p[i] == 1) printf("x");
			else printf("%dx",p[i]);
			while(p[i-zeroCounter]==0 && (zeroCounter <= i)) zeroCounter++;
			if(p[i-zeroCounter] > 0 )
			{
				printf("+");
			}
		}
		/* Dans le cas où on a un monôme courant du type a c'est-à-dire une constante */
		else if ( (p[i] != 0) && (i == 0) )
		{
			printf("%d",p[i]);
		}
	}
	printf("\n");
}

void horner(){}


