/*
 * main_test.c
 * 
 * Copyright 2016 Axel <axel@axel-GP62-6QE>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


/* Le degré du polynôme sera l'indice du tableau et la valeur 
 * à cet indice sera le coefficient devant la variable x
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define DEGREMAX 5			/* en realite : DEGREMAX - 1, si DEGREMAX = 5, le degree reel max est 4, on commence a puissance 0 */
#define ENTREEMAX 200

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
	
	for(int i = 0; i < ENTREEMAX; i++)
	{
		j = 1;
		if( tabIn[i] == 'x')
		{
			coef = 0;
			if( (i != 0) && isdigit(tabIn[i-1]) )
			{
				while( isdigit(tabIn[i-j]) ) // lire d'un decalage de j temps qu'on a des digit
				{
					coef = coef + (tabIn[i-j]-'0')*pow(10.0, j-1); // exemple pour comprendre : 112 = 10^3 + 10^2 + 2*10^1
					j++;	
				}
				power = tabIn[i+2] - '0';
			}
			else 			// on a rien devant le x
			{
				coef = 1;
				power = tabIn[i+2] - '0';
			}
		}
		tabOut[power] = coef;
	}
}


int main(void)
{
	char saisie[ENTREEMAX] = " ";
	int p[DEGREMAX];
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
	}
	
	
	
	return 0;
}
