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
	int memorySize = 2000;
	if (initMemory(memorySize) == -1) {
		printf("Cannot init memory of %d bytes", memorySize);
		return 1;
	}

	//no errors in myAlloc for now
	int *a = myAlloc(10 * sizeof(int));
	for (int i = 0; i < 10; i++) {
		a[i] = i;
	}
	int *b = myAlloc(15 * sizeof(int));
	for (int i = 0; i < 15; i++) {
		b[i] = i * 3;
	}
	int *c = myAlloc(9 * sizeof(int));
	for (int i = 0; i < 9; i++) {
		c[i] = i - 2;
	}

	struct V *v = myAlloc(10 * sizeof(struct V));
	for (int i = 0; i < 9; i++) {
		v[i].a = 127 + i;
		v[i].b = 'a' + i;
	}


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

	return 0;
}