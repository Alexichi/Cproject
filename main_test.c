/*
 * main_test.c
 *
 */


/* Lignes de commandes de contruction avec plusieurs fichiers c
 * gcc -Wall -c *.c -lsndfile -lncurses -std=gnu99 -lm
 * gcc -Wall -std=gnu99 -o main_test *.o   -lncurses -lm
 */


/* Le degré du polynôme sera l'indice du tableau et la valeur 
 * à cet indice sera le coefficient devant la variable x
 */


#include "operations.h"

/*
 * Fonction permettant d'initialiser un tableau d'entiers à double entrées
 * On utilise cette fonction principalement pour initialiser le tableau qui
 * va contenir les polynômes.
 * Paramètres : tab, le tableau d'entiers à double entrées à initialiser
 * 				sizex, qui correspond au nombre de polynômes que l'on peut stocker
 */
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

/*
 * Fonction permettant d'initialiser un tableau de caractères
 * On utilise cette fonction principalement pour initialiser le tableau qui
 * contient tous les caractères taper sur l'entrée standard (terminal)
 * Paramètres : tab, le tableau de caractères à initialiser
 * 				size, taille du tableau 
 */
void initChar(char tab[], int size)
{
	for(int i = 0; i < size; i++)
	{
		tab[i] = ' ';
	}
}

/*
 * Fonction permettant de vérifier ce que l'utilisateur a écrit lorsqu'il veut entrer un polynome
 * Paramètre : tab, le tableau contenant tous les caractères tapés sur l'entrée standard (terminal)
 */
int verifPoly(char * tab){
	if(tab[0] == '^'){
			return 0;
	}
	for(int i = 0; i < ENTREEMAX-1; i++){
		if(!(isdigit(tab[i])) && tab[i]!='+' && tab[i]!='-' && tab[i]!='x' && tab[i]!='^' && tab[i]!=' '){
			printf("%c\n", tab[i]);
			return 0;
		}
		else if((tab[i] == '+' && tab[i+1] == '+') || (tab[i] == '-' && tab[i+1] == '-') || (tab[i] == 'x' && tab[i+1] == 'x') ||
				(tab[i] == '^' && tab[i+1] == '^')){
				return 0;
		}
		else if(tab[i] == '^' && !(isdigit(tab[i+1]))){
			return 0;
		}
		else if(tab[i+1] == '^' && tab[i] != 'x'){
			return 0;
		}
		else if(tab[i] == 'x' && (tab[i+1] != '+' && tab[i+1] != '^') && tab[i+1] != ' '){
			return 0;
		}
	}
	return 1;
}

/*
 * Fonction permettant de rentrer dans un tableau le polynôme entré sur l'entrée standard 
 * et qui a été vérifié. L'indice correspond à la puissance du monôme courant et la valeur 
 * à cet indice est le coefficient se trouvent devant la variable x^n
 * Ex : pour 2x^4 , la valeur 2 sera stocké à l'indice 4 (sachant que l'indice commence à 0)
 * Paramètres : tabIn, le tableau de caractères à transformer
 * 				tabOut, le tableau d'entiers résultant du tri
 */
void triPoly(char * tabIn, int * tabOut)
{
	int coef = 0; // coeffcient devant x
	int power = 0;
	int j = 1;
	int l = 1;
	/* le but est de parcourir la chaine de charactere qui est dans tabIn
	 * */
	for(int i = 0; i < ENTREEMAX; i++) 
	{
		j = 1;
		if( tabIn[i] == 'x') /* On commence par cherche un x */
		{
			coef = 0;
			/* cette condition permet de savoir si il y a quelque chose devant x
			 * plus particulierement un nombre
			 * */
			if( (i != 0) && isdigit(tabIn[i-1]) ) 
			{
				/* cette boucle permet de recuperer les coeff a plusieurs chiffres par exemple 100 */
				while( isdigit(tabIn[i-j]) ) // lire d'un decalage de j tant qu'on a des digit
				{
					coef = coef + (tabIn[i-j]-'0')*pow(10.0, j-1); // exemple pour comprendre : 112 = 10^2 + 10^1 + 2*10^0
					j++;
				}
				/* Si on trouve un - devant le coeff
				 * on le passe en negatif
				 * */
				if( tabIn[i-j] == '-' ) 
				{
					coef = -coef;
				}
				/* on recherche la presence d'un ^
				 * pour ensuite recuperer la puissance 
				 * */
				if( tabIn[i+1] == '^' )
				{
					power = tabIn[i+2] - '0'; /* l'operation tabIn[i+2] - '0' permet de faire une conversion char -> int coherente */
				}
				else /* pas de ^ donc la puissance est forcement 1 */
				{
					power = 1;
				}
				/* maintenant que notre coeff est defini
				 * ainsi que la puissance
				 * on peut stocker le coeff a l'indice de la puissance
				 * */
				tabOut[power] = tabOut[power] + coef;
			}
			else 		/* on a rien devant le x */
			{
				coef = 1; /* donc le coeff est forcement 1 */
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
		else if ( (isdigit(tabIn[i])) && (!isdigit(tabIn[i-1])) ) /* si ce n'est pas un x on peut tomber sur le debut d'une constante */
		{
			coef = 0;
			j = 1;
			l = 1;
			while( isdigit(tabIn[i+j]) ) // lire d'un decalage de j tant qu'on a des digit
			{
				j++;	
			}
			/* si le caractere apres le nombre n'est pas x et pas de ^ devant le nombre, alors on a une constante */
			if( (tabIn[i+j] != 'x') && (tabIn[i-1] != '^')) 
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

/*
 * Fonction permettant d'afficher les différentes commandes possibles
 * selon l'action que l'on désire réaliser
 */
void afficherCommande(void)
{
	printf("P : Commande de declaration d'un polynome\n");
	printf("A : Commande d'addition\n");
	printf("M : Commande de multiplication\n");
	printf("Q : Commande de division euclidienne\n");
	printf("F : Commande de factorisation\n");
	printf("D : Affiche les polynomes saisis\n");
	printf("H : Affiche les commandes disponibles\n");
	printf("E : Commande de sortie de programme \n");
	
}

/*
 * Fonction principale permettant d'intéragir directement avec l'utilisateur
 */
int main(void)
{
	int res[DEGREMAX] ;
	int Q[DEGREMAX];
	int R[DEGREMAX];
	int exit = 0;
	int c = 0;
	char d = 0;
	int i = 0;
	char saisie[ENTREEMAX] = " ";
	char parametre[ENTREEMAX] = " ";
	char commande = ' ';
	polynome p;
	
	initDouble(p, NBMAXPOLY); /* on initialise tout nos polynomes a 0 */
	afficherCommande(); /* on affiche les commande disponibles */
	while( exit == 0 )
	{
		i = 0;
		initChar(saisie, ENTREEMAX);
		init(res, DEGREMAX);
		init(Q, DEGREMAX);
		init(R, DEGREMAX);
		while( (c = getchar()) != '\n')		// on recupere le contenu
		{
			if(c != ' ' && c != '*')
			{
				if( i == 0 ) 
				{
					commande = c;
				}
				i++;
			}
		}
		switch(commande){ /* on test quelle commande a été entrée */
			case 'P': /* Commande de declaration d'un polynome */
				i = 0;
				char nom = 'a';
				printf("nom du polynôme\n");
				while( (d = getchar()) != '\n' ) /* recuperation du nom de polynome */
				{
					if( i == 0 ) /* on recupera que le 1er caractere */
					{
						nom = d;
					}
					i++;
				}
				if((nom-'A')< 0 || (nom-'A')>26){ /* on empeche l'utilisateur de mettre autre chose qu'une majuscule */
					printf("Besoin d'un nom de polynôme en majuscule\n");
					break;
				}
				printf("Saisissez votre polynome\n");
				i = 0;
				while( (c = getchar()) != '\n' ) /* recuperation du polynome */
				{
					if( (i<ENTREEMAX) )
					{
						saisie[i] = c;
						i++;
					}
				}
				if(verifPoly(saisie) == 0){ /* test si le polynome est valide */
					printf("mauvaise syntaxe pour le polynome \n");
				}
				else{
					triPoly(saisie, p[nom-'A']); /* si oui, on peut analyser le polynome */
				}
				break;
			
			case 'E': /* fonction de sortie de la boucle principale */
				exit = 1;
				break;
			
			case 'D': /* fonction d'affichage des polynomes entrés */
				for(int i = 0; i < NBMAXPOLY; i++)
				{
					if(degre(p[i])!= (-1)) /* on affiche les polynomes qui sont differents de 0 */
					{
						printf("Polynome %c ", i+'A');ecriture(p[i]);printf("\n"); /* on indique aussi le nom du polynome */
					}
				}
				break;
			
			case 'A': /* fonction d'addition de 2 polynomes */
				i = 0;
				printf("Saisir le nom des deux polynomes a additionner \n");
				while( (c = getchar()) != '\n' ) /* on demande quels polynomes sont a additionner */
				{
					if( (c != ' ') )
					{
						parametre[i] = c;
						i++;
					}
				}
				somme(p[parametre[0] - 'A'], p[parametre[1] - 'A'], res); /* on somme */
				ecriture(res);printf("\n"); /* on affiche le resultat */
				break;
			
			case 'M': /* fonction de multiplication de 2 polynomes */
				i = 0;
				printf("Saisir le nom des deux polynomes a multiplier\n");
				while( (c = getchar()) != '\n' ) /* on demande quels polynomes sont a additionner */
				{
					if( (c != ' ') )
					{
						parametre[i] = c;
						i++;
					}
				}
				produit(p[parametre[0] - 'A'], p[parametre[1] - 'A'], res); /* on multiplie */
				ecriture(res);printf("\n"); /* on affiche le resultat */
				break;
			
			case 'Q': /* fonction de division euclidienne */
				i = 0;
				printf("Saisir le nom des deux polynomes \n");
				printf("Remarque : Le deuxieme polynome divise \n");
				while( (c = getchar()) != '\n' ) /* on recupere les deux polynomes */
				{
					if( (c != ' ') )
					{
						parametre[i] = c;
						i++;
					}
				}
				divEucl(p[parametre[0] - 'A'], p[parametre[1] - 'A'], Q, R); 
				/* on fait la division euclidienne,
				 * Q recupere le quotient, R le reste */
				printf("Quotient : ");ecriture(Q);printf("\n");
				printf("Reste : ");ecriture(R);printf("\n");
				break;
				
			case 'F':
				i = 0;
				printf("Saisir le nom du polynome a factoriser \n");
				while( (c = getchar()) != '\n' ) /* on recupere le polynome */
				{
					if( (c != ' ') )
					{
						if( i == 0 )
						{
							parametre[i] = c;
						}
						i++;
					}
				}
				printf("saisir une racine du polynome\n");
				i = 0;
				while( (c = getchar()) != '\n' ) /* on recupere la racine */
				{
					if( (c != ' ') )
					{
						if( i == 0 )
						{
							parametre[i+1] = c;
						}
						i++;
					}
				}
				factorisation( p[parametre[0] - 'A'], res, parametre[1] - '0' );/* on factorise, l'affichage est géré par la fonction */
				break;
			case 'H':
				afficherCommande();
				break;
			default : /* si la commande n'est pas reconnue, on le signal */
				printf("Commande inconnue\n");
		}
	}
	return 0;
}
