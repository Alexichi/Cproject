#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEGREMAX 30
typedef int polynome[DEGREMAX];

void isPolynomeCorrect(void);

int main(void){
	/*int c;
	int i = 0;
	char pol[DEGREMAX];
	int polynomes[10][DEGREMAX];
	printf("Entrez un polynôme :\n");
	do{
		if((c=getchar()) == '\n'){
			polynomes[i] = pol;
		}
	}
	while ((c=getchar()) != EOF);*/
	
	isPolynomeCorrect();
	
	return EXIT_SUCCESS;
}

void isPolynomeCorrect(void){
	int err;
	regex_t preg;
	const char *str_request = "3*x^24 - 4x^3 + 5*x^2 + 43x^10";
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
