/*
 * main_test.c
 *
 *  
 * polynomes de test :
 * -2x+x^2+3*x^3
 * -5*x+5*x^7-6*x^3
 * 
 */


/* Lignes de commandes de contruction avec plusieurs fichiers c
 * gcc -Wall -c *.c -lSDL  -lsndfile -lncurses -std=c99 -lm
 * gcc -Wall -std=c99 -o main_test *.o  `sdl2-config --cflags --libs` -lsndfile -lncurses -lm
 */


/* Le degré du polynôme sera l'indice du tableau et la valeur 
 * à cet indice sera le coefficient devant la variable x
 */


#include "operations.h"

void init(int * tab, int size)
{
	for(int i = 0; i < size; i++)
	{
		tab[i] = 0;
	}
}

void triPoly(char * tabIn, int * tabOut)
{
	int coef = 0;
	int power = 0;
	int j = 1;
	int k = 1; //incrément pour savoir la présence d'un *
	
	for(int i = 0; i < ENTREEMAX; i++)
	{
		j = 1;
		k = 1;
		if( tabIn[i] == 'x')
		{
			coef = 0;
			if( tabIn[i-1] == '*')
			{
					k = 2;
					j= 2;
			}
			if( (i != 0) && isdigit(tabIn[i-k]) )
			{
				while( isdigit(tabIn[i-j]) ) // lire d'un decalage de j tant qu'on a des digit
				{
					coef = coef + (tabIn[i-j]-'0')*pow(10.0, j-k); // exemple pour comprendre : 112 = 10^3 + 10^2 + 2*10^1
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
			}
		}
		tabOut[power] = coef;
	}
}


int main(void)
{
	int p[] = {3,2,7,3,8,0,0,0,0,0};
	int q[] = {4,3,0,0,0,0,0,0,0,0};
	int res[10] ;
	init(res, 10);
	produit(p,q, res);
	ecriture(res);
	/*char saisie[ENTREEMAX] = " ";
	polynome p;
	init(p, DEGREMAX);
	int c = 0;
	int i = 0;
	while( (c = getchar()) != EOF)		// on recupere le contenu
	{
		printf("%c", c);
		saisie[i] = c;
		i++;
	}
	triPoly(saisie, p);
	for(int i = 0; i < DEGREMAX; i++)
	{
		printf("Ordre : %d	Coeff : %d\n", i, p[i]);
	}*/
	return EXIT_SUCCESS;
}
