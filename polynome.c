#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEGREMAX 30
typedef int polynome[DEGREMAX];

void isPolynomeCorrect(void);
void triTableau(char *);

int main(void){
	int c;
	int i = 0;
	int j = 0;
	char tousLesC[200]; //tableau contenant tous les caractères entrées sur l'ES
	char tableauTrie[2][DEGREMAX];
	int polynomes[10][2][DEGREMAX]; /*tableau contenant tous les polynômes (10 max).Le 2 correspond à un 
									 * tableau comprenant les coefficients et les puissances. 
									 */
	printf("Entrez un polynôme :\n");
	do{
		if((c=getchar()) == '\n'){
			if(isPolynomeCorrect(tousLesC)){
				triTableau(tousLesC, tableauTrie);
				polynomes[i] = tableauTrie;
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
void triTableau(char * tabATrier, char * tabTrier[DEGREMAX]){
	for(int i = 0; i < 200; i++){
		
	}
}

void isPolynomeCorrect(char * request){
	int err;
	regex_t preg;
	const char *str_request = (string)request;
	const char *str_regex = "[\s*[0-9]\*?*x[\\^[0-9]+]?\s*\+|\-\s*]+";
	
	err = regcomp (&preg, str_regex, REG_NOSUB | REG_EXTENDED);
	if (err == 0){
		int match;
		
		match = regexec (&preg, str_request, 0, NULL, 0);
		
		regfree (&preg);
		
		if (match == 0){
			printf ("%s est un polynome valide\n", str_request);
		}
		else if (match == REG_NOMATCH){
			printf ("%s n\'est pas un polynome valide\n", str_request);
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
	puts ("\nPress any key\n");
	/* Dev-cpp */
	getchar ();
}
