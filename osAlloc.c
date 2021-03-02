#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyMemory.h"
#include "MyBlock.h"

extern MyMemory memory;

struct V {
	int a;
	char b;
};

void affTab(int nELts, int *tab) {
	for (int i = 0; i < nELts; i++) {
		printf("%d ", tab[i]);
	}
	printf("\n");
}

int test();

int main(int argc, char** argv) {
	if (argc > 1) {
		char* param = argv[1];
		if (strcmp(param,"-i") == 0) {
			if (argc == 2) {
				printf("lancement prog interactif\n");
			}
			else {
				printf("trop d'argument pour le programme interactif\n");
			}
		}
		else if (strcmp(param,"-f") == 0) {
			if (argc == 3) {
				printf("lancement prog fichier\n");
			}
			else {
				printf("Nombre d'arguments incorrects pour lancer la lecture du fichier\n");
				printf("Attendu : -f [nomFichier]\n");
			}
		}
		else {
			printf("lancement prog command line\n");
		}
	}
	else {
		return test();
	}
	return 0;
}

int test() {
	printf("======== Start of the test ========\n");
	int memorySize = 2000;
	if (initMemory(memorySize) == -1) {
		printf("Cannot init memory of %d bytes\n", memorySize);
		return 1;
	}
	printf("Memory Initialize\n");

	//no errors in myAlloc for now
	int *a = myAlloc(10 * sizeof(int));
	for (int i = 0; i < 10; i++) {
		a[i] = i;
	}
	printf("Block a Initialized\n");

	int *b = myAlloc(15 * sizeof(int));
	for (int i = 0; i < 15; i++) {
		b[i] = i * 3;
	}
	printf("Block b Initialized\n");

	int *c = myAlloc(9 * sizeof(int));
	for (int i = 0; i < 9; i++) {
		c[i] = i - 2;
	}
	printf("Block c Initialized\n");

	struct V *v = myAlloc(10 * sizeof(struct V));
	for (int i = 0; i < 9; i++) {
		v[i].a = 127 + i;
		v[i].b = 'a' + i;
	}
	puts("Struct V Initialized\n");

	puts("Display all arrays content :");
	affTab(10, a);
	affTab(memory.listBlock->contentSize / sizeof(int), memory.listBlock->contentPtr);
	affTab(15, b);
	affTab(9, c);
	printf("Fin affichage Tab\n");

	printf("\nDisplay memory with arrays a, b, c & v\n");
	displayMemory();

	printf("\nFree a array\n");
	myFree(a);
	printf("a array is now free\n");

	printf("\nMemory without array a :\n");
	displayMemory();

	int *d = myAlloc(5 * sizeof(int));
	for (int i = 0; i < 5; i++) {
		d[i] = 20 * i;
	}
	printf("Block d Initialized\n");

	affTab(5, a);

	int res = myFree(c);
	if (res == -1) {
		perror("Error while freeing\n");
	}
	else {
		printf("%d\n", res);
		printf("%d\n", myFree(v));
	}

	printf("\nDisplay memory with arrays in order : d (size : 5 bytes), b (size : 15 bytes)\n");
	displayMemory();

	freeMemory();
	printf("======== End of the test ========\n");
	return 0;
}
