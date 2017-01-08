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
	int coefTmp = 0; //coefficient temporaire pour stocker le coefficient du terme courant
	int coef = 0; // coeffcient final issue de la somme des coeffcients de même puissance de x
	int power = 0;
	int j = 1;
	int l = 1;
	int constante = 0; // constante finale issue de la somme de toutes les valeurs constantes
	for(int i = 0; i < ENTREEMAX; i++)
	{
		j = 1;
		if( tabIn[i] == 'x')
		{
			coefTmp = 0;
			if( (i != 0) && isdigit(tabIn[i-1]) )
			{
				while( isdigit(tabIn[i-j]) ) // lire d'un decalage de j tant qu'on a des digit
				{
					coefTmp = coefTmp + (tabIn[i-j]-'0')*pow(10.0, j-1); // exemple pour comprendre : 112 = 10^2 + 10^1 + 2*10^0
					j++;
				}
				if( tabIn[i-j] == '-' )
				{
					coefTmp = -coefTmp;
				}
				if( tabIn[i+1] == '^' )
				{
					power = tabIn[i+2] - '0';
				}
				else
				{
					power = 1;
				}
				coef = tabOut[power];
				coef += coefTmp;
				tabOut[power] = coef;
			}
			else 			// on a rien devant le x
			{
				coefTmp = 1;
				if( tabIn[i-1] == '-' )
				{
					coefTmp = -coefTmp;
				}
				if( tabIn[i+1] == '^' )
				{
					power = tabIn[i+2] - '0';
				}
				else
				{
					power = 1;
				}
				coef = tabOut[power];
				coef += coefTmp;
				tabOut[power] = coef;
			}
		}
		else if ( (isdigit(tabIn[i])) && (!isdigit(tabIn[i-1])) ) // chercher une constante
		{
			coefTmp = 0;
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
					coefTmp = coefTmp + (tabIn[i+j-l]-'0')*pow(10.0, l-1); // exemple pour comprendre : 112 = 10^2 + 10^1 + 2*10^0
					l++;	
				}
				if( tabIn[i-1] == '-' )
				{
					coefTmp = -coefTmp;
				}
				/* constante est la variable finale. De ce fait on garde le résultat d'avant ,qu'on somme au coef actuel.
				 * ( ex :x + 7 + 12 = x + 19) 
				 */
				constante += coefTmp;  
				tabOut[power] = constante;
			}
		}
	}
}


int main(void)
{
	//int p[] = {3,2,7,3,8,0,0,0,0,0};  // 3 + 2x + 7x^2 + 3x^3 + 8x^4
	//int q[] = {4,3,0,0,0,0,0,0,0,0};  // 4 + 3x
	//int res[10] ;
	//init(res, 10);
	//produit(p,q, res);
	//somme(p, q, res);
	//ecriture(res);
	int c = 0;
	int i = 0;
	char saisie[ENTREEMAX] = " ";
	polynome p;
	init(p, DEGREMAX);
	while( (c = getchar()) != EOF)		// on recupere le contenu
	{
		if(c != ' ' && c != '*'){
			saisie[i] = c;
			i++;
		}
	}
	triPoly(saisie, p);
	ecriture(p);
	return 0;
}
