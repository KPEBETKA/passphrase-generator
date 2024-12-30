#include "stdio.h"
#include "stdlib.h"

long letters = 0;
long frequencies = 0;
int trigrams[26][26][26] = {0};

int argno;
int files;

FILE *file;

char word[100];
int i;
int c1, c2, c3;

int main (int argc, char ** argv) {
	if (argc < 2) {
		printf ("USAGE: gentrigrams /path/to/wordlist ...");
		exit (1);
	}

	files = 0;
	
	for (argno = 1; argno < argc; argno++) {
		if ((file = fopen (argv[argno], "r")) == NULL) {
			printf ("** file %s not found\n", argv[argno]);
			break;
		}
		files++;
		while (fgets (word, sizeof (word), file)) {
			i = 0;
			c1 = -1;
			c2 = -1;
			while (word[i]) {
				c3 = word[i];
				if (c3 > 90) {
					c3 = c3 - 97;
				}
				else {
					c3 = c3 - 65;
				}
				if (c3 >= 0 && c3 <= 25) {
					if (c1 >= 0) {
						trigrams[c1][c2][c3]++;
						frequencies++;
					}
					c1 = c2;
					c2 = c3;
				}
				i++;
			}
		}
		fclose (file);
	}

	if (files) {
		printf ("var trigrams = [");
		for (c1 = 0; c1 < 26; c1++) {
			printf ("[");
			for (c2 = 0; c2 < 26; c2++) {
				printf ("\n/* %c %c */ [", c1 + 65, c2 + 65);
				for (c3 = 0; c3 < 26; c3++) {
					if (c3 < 25) {
						printf ("%d,", trigrams[c1][c2][c3]);
					}
					else {
						printf ("%d", trigrams[c1][c2][c3]);
					}
					if (trigrams[c1][c2][c3] > 0) {
						letters++;
					}
				}
				if (c2 < 25) {
					printf("],");
				}
				else {
					printf("]");
				}
			}
			if (c1 < 25) {
				printf("\n],");
			}
			else {
				printf("\n]");
			}
		}
		printf ("];\n\n");
		printf ("var frequencies = %ld;\n", frequencies);
		printf ("var letters = %ld;\n", letters);
	}
	exit (0);
}
