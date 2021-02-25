#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "MyMemory.h"
#include "MyBlock.h"

void initMem(int taille);
void allocBlock(int taille);
void desallocBlock(int nbBlock);
void displayMem();
void clearMem();
