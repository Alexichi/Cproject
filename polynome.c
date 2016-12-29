/* Le degré du polynôme sera l'indice du tableau et la valeur 
 * à cet indice sera le coefficient devant la variable x
 */

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEGREMAX 30
typedef int polynome[DEGREMAX];

int isPolynomeCorrect(char * );
void triTableau(char *, char *);
void tabToPol(char * , polynome , int );
int isdigit (int );

int main(void){
	int c;
	int i = 0;
	int j = 0;
	char tousLesC[200]; //tableau contenant tous les caractères entrées sur l'ES
	char tableauTrie[DEGREMAX];
	polynome p;
	polynome polynomes[10][DEGREMAX]; /*tableau contenant tous les polynômes (10 max).Le 2 correspond à un 
									 * tableau comprenant les coefficients et les puissances. 
									 */
	printf("Entrez un polynôme :\n");
	do{
		if((c=getchar()) == '\n'){
			if(isPolynomeCorrect(tousLesC)){
				triTableau(tousLesC, tableauTrie);
				tabToPol(tableauTrie, p, DEGREMAX);
				polynomes[i] = p;
				i++;
			}
			else{
				printf ("ce n\'est pas un polynome valide\n");
				return EXIT_FAILURE;
			}
			
		}
		else{
			tousLesC[j] = getchar();
			j++;
		}
	}
	while ((c=getchar()) != EOF);
	
	return EXIT_SUCCESS;
}

/* Fonction qui permet de trier ce que l'utilisateur à écrit sur l'ES
 * en récupérant seulement les chiffres en faisant attention à différencier les 
 * coefficients des puissances.
 */
void triTableau(char * tabATrier, char * pol){
	int j = 0;
	for(int i = 0; i < 200; i++){
		if(tabATrier[i] == 'x' && tabATrier[i-1] == '*'){ //le polynome est de la forme a*x^b
			j = i-2;
		}
		else if(tabATrier[i] == 'x' && isdigit(tabATrier[i-1])){ //le polynome est de la forme ax^b
			j = i-1;
		}
		while(isdigit(tabATrier[j])){
				pol[0][0] =  pol[0][0] + tabATrier[j];
		}
	}
}

/* Fonction qui converti le tableau trié contenant les coefficients et 
 * les puissances en polynome.
 * tab[0] correspond aux coefficients et tab[1] correspond aux puissances
 */
void tabToPol(char * tab, polynome p, int size){
	int power = 0;
	for(int i ; i < size; i++){
		power = tab[1][i]; //power prend la puissance à l'indice i du tableau des puissances
		if(p[power] == 0){
			p[power] = tab[0][i]; // le coefficient va à l'indice correspondant à sa puissance associée
		}
		else{
			p[power] = p[power] + (int)tab[0][i]; //sinon on somme à la valeur déjà présente à cette indice
		}
	}
}

int isPolynomeCorrect(char * request){
	int err;
	regex_t preg;
	const char *str_request = request;
	const char *str_regex = "[\\s*[0-9]\\*?*x[\\^[0-9]+]?\\s*\\+|\\-\\s*]+";
	
	err = regcomp (&preg, str_regex, REG_NOSUB | REG_EXTENDED);
	if (err == 0){
		int match;
		
		match = regexec (&preg, str_request, 0, NULL, 0);
		
		regfree (&preg);
		
		if (match == 0){
			//printf ("%s est un polynome valide\n", str_request);
			return 1;
		}
		else if (match == REG_NOMATCH){
			//printf ("%s n\'est pas un polynome valide\n", str_request);
			return 0;
		}
		else{
			char *text;
			size_t size;
			size = regerror (err, &preg, NULL, 0);
			text = malloc (sizeof (*text) * size);
			if (text){
				regerror (err, &preg, text, size);
				fprintf (stderr, "%s\n", text);
				free (text);
			}
			else{
				fprintf (stderr, "Memoire insuffisante\n");
				exit (EXIT_FAILURE);
			}
		}
	}
}

/* puts ("\nPress any key\n");
	//Dev-cpp
	getchar ();
	*/
