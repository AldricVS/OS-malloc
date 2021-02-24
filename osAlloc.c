#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "MyMemory.h"
#include "MyBlock.h"

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

int main() {
	printf("Start of the test\n");
	int memorySize = 2000;
	if (initMemory(memorySize) == -1) {
		printf("Cannot init memory of %d bytes", memorySize);
		return 1;
	}
	printf("Memory Initialize\n");

	//no errors in myAlloc for now
	int *a = myAlloc(10 * sizeof(int));
	for (int i = 0; i < 10; i++) {
		a[i] = i;
	}
	printf("Block a Initialize\n");

	int *b = myAlloc(15 * sizeof(int));
	for (int i = 0; i < 15; i++) {
		b[i] = i * 3;
	}
	printf("Block b Initialize\n");

	int *c = myAlloc(9 * sizeof(int));
	for (int i = 0; i < 9; i++) {
		c[i] = i - 2;
	}
	printf("Block c Initialize\n");

	struct V *v = myAlloc(10 * sizeof(struct V));
	for (int i = 0; i < 9; i++) {
		v[i].a = 127 + i;
		v[i].b = 'a' + i;
	}
	printf("Struct V Initialize\n");


	affTab(10, a);
	affTab(15, b);
	affTab(9, c);

	int res = myFree(a);
	if (res == -1) {
		perror("Error while freeing");
	}
	else {
		printf("%d\n", res);
		printf("%d\n", myFree(v));
	}

	freeMemory();
	//error testing
	//int *d = myAlloc(2);

	return 0;
}
