#include "util.h"
#include <string.h>
#include <stdio.h>

int areStringsEquals(char *string1, char *string2) {
	return strcmp(string1, string2) == 0;
}

void displayArray(int nELts, int *tab) {
	for (int i = 0; i < nELts; i++) {
		printf("%d ", tab[i]);
	}
	printf("\n");
}