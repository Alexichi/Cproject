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
			printf("lolp\n");
			return 0;
	}
	for(int i = 0; i < ENTREEMAX-1; i++){
		if(!(isdigit(tab[i])) && tab[i]!='+' && tab[i]!='-' && tab[i]!='x' && tab[i]!='^' && tab[i]!=' '){
			printf("%c\n", tab[i]);
			return 0;
		}
		else if((tab[i] == '+' && tab[i+1] == '+') || (tab[i] == '-' && tab[i+1] == '-') || (tab[i] == 'x' && tab[i+1] == 'x') ||
				(tab[i] == '^' && tab[i+1] == '^')){
				printf("lol1\n");
				return 0;
		}
		else if(tab[i] == '^' && !(isdigit(tab[i+1]))){
			printf("lol2\n");
			return 0;
		}
		else if(tab[i+1] == '^' && tab[i] != 'x'){
			printf("lol3\n");
			return 0;
		}
		else if(tab[i] == 'x' && (tab[i+1] != '+' && tab[i+1] != '^') && tab[i+1] != ' '){
			printf("lol4\n");
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

/*
 * Fonction permettant d'afficher les différentes commandes possibles
 * selon l'action que l'on désire réaliser
 */
void afficherCommande(void)
{
	printf("P : declare le polynome qui suit P\n");
	printf("A : Commande d'addition\n");
	printf("M : Commande de multiplication\n");
	printf("Q : Commande de division\n");
	printf("E : Commande de sortie de programme \n");
	printf("D : Affiche les polynomes saisis\n");
}

/*
 * Fonction principale permettant d'intéragir directement avec l'utilisateur
 */
int main(void)
{
	/*int N[] = {-3,2,-4,1,0,0,0,0,0,0};  
	int D[] = {2,1,0,0,0,0,0,0,0,0}; 
	int res[10] ;
	init(res, 10);
	produit(N,D,res);
	printf("résultat de la mutiplication : \n");ecriture(res);
	//printf("D :");ecriture(D);
	//printf("Q :");ecriture(Q);
	//printf("reste :");ecriture(reste);*/
	printf("Entrer un polynôme pour commencer en le précédant de la lettre P \n (n'utiliser que la variable x) \n");
	int res[DEGREMAX] ;
	int Q[DEGREMAX];
	int R[DEGREMAX];
	int exit = 0;
	int c = 0;
	int i = 0;
	int nbPolynome = 0;
	char saisie[ENTREEMAX] = " ";
	char parametre[ENTREEMAX] = " ";
	char commande = ' ';
	polynome p;
	
	initDouble(p, NBMAXPOLY);
	init(res, DEGREMAX);
	init(Q, DEGREMAX);
	init(R, DEGREMAX);
	afficherCommande();
	while( exit == 0 )
	{
		i = 0;
		initChar(saisie, ENTREEMAX);
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
		if( commande == 'P' )
		{
			i = 0;
			printf("Saisissez votre polynome\n");
			while( (c = getchar()) != '\n' )
			{
				if( (c != ' ') && (i<ENTREEMAX) )
				{
					saisie[i] = c;
					i++;
				}
			}
			if(verifPoly(saisie) == 0){
				printf("mauvaise syntaxe pour le polynome \n");
			}
			else{
				triPoly(saisie, p[nbPolynome]);
				nbPolynome++;
			}
		}
		if( commande == 'E' )
		{
			exit = 1;
		}
		if( commande == 'D' )
		{
			for(int i = 0; i < nbPolynome; i++)
			{
				printf("Polynome numero %d ", i);ecriture(p[i]);
			}
		}
		if( commande == 'A' )
		{
			i = 0;
			printf("Saisir le numéro des deux polynomes a additionner, les numeros commencent a 0 \n");
			while( (c = getchar()) != '\n' )
			{
				if( (c != ' ') )
				{
					parametre[i] = c;
					i++;
				}
			}
			somme(p[parametre[0] - '0'], p[parametre[1] - '0'], res);
			ecriture(res);
		}
		if( commande == 'M' )
		{
			i = 0;
			printf("Saisir le numéro des deux polynomes a multiplier, les numeros commencent a 0 \n");
			while( (c = getchar()) != '\n' )
			{
				if( (c != ' ') )
				parametre[i] = c;
				i++;
			}
			produit(p[parametre[0] - '0'], p[parametre[1] - '0'], res);
			ecriture(res);
		}
		if( commande == 'Q' )
		{
			i = 0;
			printf("Saisir le numéro des deux polynomes, les numeros commencent a 0 \n");
			printf("Le deuxieme polynome divise \n");
			while( (c = getchar()) != '\n' )
			{
				if( (c != ' ') )
				parametre[i] = c;
				i++;
			}
			divEucl(p[parametre[0] - '0'], p[parametre[1] - '0'], Q, R);
			init(res, DEGREMAX);
			printf("Quotient : ");ecriture(Q);
			printf("Reste : ");ecriture(R);
		}
	}
	return 0;
}
