/*
 * main_test.c
 *
 *  
 * polynomes de test :
 * -2x+x^2+3x^3
 * -5*x+5*x^7-6*x^3
 * 3x^4+5x^2+8x+9
 * -5*x + 5 *x^7- 6*x^3 + 7x + 5 + 12 fonctionne
 */


/* Lignes de commandes de contruction avec plusieurs fichiers c
 * gcc -Wall -c *.c -lsndfile -lncurses -std=gnu99 -lm
 * gcc -Wall -std=gnu99 -o main_test *.o   -lncurses -lm
 */


/* Le degré du polynôme sera l'indice du tableau et la valeur 
 * à cet indice sera le coefficient devant la variable x
 */


#include "operations.h"


void initDouble(int tab[][DEGREMAX], int sizex)
{
	for(int i = 0; i < sizex; i++)
	{
		for(int j = 0; j < DEGREMAX; j++)
		{
			tab[i][j] = 0;
		}
	}
}

void initChar(char tab[], int size)
{
	for(int i = 0; i < size; i++)
	{
		tab[i] = ' ';
	}
}

void triPoly(char * tabIn, int * tabOut)
{
	int coef = 0; // coeffcient devant x
	int power = 0;
	int j = 1;
	int l = 1;
	for(int i = 0; i < ENTREEMAX; i++)
	{
		j = 1;
		if( tabIn[i] == 'x') // on repere un x
		{
			coef = 0;
			if( (i != 0) && isdigit(tabIn[i-1]) )
			{
				while( isdigit(tabIn[i-j]) ) // lire d'un decalage de j tant qu'on a des digit
				{
					coef = coef + (tabIn[i-j]-'0')*pow(10.0, j-1); // exemple pour comprendre : 112 = 10^2 + 10^1 + 2*10^0
					j++;
				}
				if( tabIn[i-j] == '-' )
				{
					coef = -coef;
				}
				if( tabIn[i+1] == '^' )
				{
					power = tabIn[i+2] - '0';
				}
				else
				{
					power = 1;
				}
				
				tabOut[power] = tabOut[power] + coef;
			}
			else 			// on a rien devant le x
			{
				coef = 1;
				if( tabIn[i-1] == '-' )
				{
					coef = -coef;
				}
				if( tabIn[i+1] == '^' )
				{
					power = tabIn[i+2] - '0';
				}
				else
				{
					power = 1;
				}
				tabOut[power] = tabOut[power] + coef;
			}
		}
		else if ( (isdigit(tabIn[i])) && (!isdigit(tabIn[i-1])) ) // chercher une constante
		{
			coef = 0;
			j = 1;
			l = 1;
			while( isdigit(tabIn[i+j]) ) // lire d'un decalage de j tant qu'on a des digit
			{
				j++;	
			}
			if( (tabIn[i+j] != 'x') && (tabIn[i-1] != '^')) // si le caractere apres le nombre n'est pas x et pas de ^ devant le nombre, alors on a une constante
			{
				power = 0;
				while( isdigit(tabIn[i+j-l]) ) // lire d'un decalage de l tant qu'on a des digit
				{
					coef = coef + (tabIn[i+j-l]-'0')*pow(10.0, l-1); // exemple pour comprendre : 112 = 10^2 + 10^1 + 2*10^0
					l++;	
				}
				if( tabIn[i-1] == '-' )
				{
					coef = -coef;
				}
				tabOut[power] = tabOut[power] + coef;
			}
		}
	}
}

void afficherCommande()
{
	printf("P : declare le polynome qui suit P\n");
	printf("A : Commande d'addition\n");
	printf("E : Commande de sortie de programme \n");
	printf("D : Affiche les polynomes saisis\n");
}

/* commandes : P + saisie pour declarer un poly 
 * 				D pour afficher les poly */

int main(void)
{
	/*int N[] = {-3,2,-4,1,0,0,0,0,0,0};  
	int D[] = {2,1,0,0,0,0,0,0,0,0}; 
	int reste[10] ;
	int Q[10];
	init(reste, 10);
	init(Q, 10);
	divEucl(N,D,Q,reste);
	printf("N :");ecriture(N);
	printf("D :");ecriture(D);
	printf("Q :");ecriture(Q);
	printf("reste :");ecriture(reste);*/
	int res[DEGREMAX] ;
	int exit = 0;
	int c = 0;
	int i = 0;
	char saisie[ENTREEMAX] = " ";
	char parametre[10] = " ";
	char commande = ' ';
	int nbPolynome = 0;
	polynome p;
	
	initDouble(p, 10);
	afficherCommande();
	while( exit == 0 )
	{
		i = 0;
		initChar(saisie, ENTREEMAX);
		while( (c = getchar()) != '\n')		// on recupere le contenu
		{
			if(c != ' ' && c != '*')
			{
				if( i < 1 ) 
				{
					commande = c;
				}
				else
				{
					saisie[i-1] = c;
				}
				i++;
			}
		}
		if( commande == 'P' )
		{
			triPoly(saisie, p[nbPolynome]);;
			nbPolynome++;
		}
		if( commande == 'E' )
		{
			exit = 1;
		}
		if( commande == 'D' )
		{
			for(int i = 0; i < nbPolynome; i++)
			{
				ecriture(p[i]);
			}
		}
		if( commande == 'A' )
		{
			i = 0;
			printf("Saisir les 2 numero des polynomes a additionner, les numeros commencent a 0 \n");
			while( (c = getchar()) != '\n' )
			{
				if( (c != ' ') )
				parametre[i] = c;
				i++;
			}
			somme(p[parametre[0] - '0'], p[parametre[1] - '0'], res);
			ecriture(res);
		}
	}
	return 0;
}
