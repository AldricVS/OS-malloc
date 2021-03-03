/**
* @file Util.h
* Collection of useful fonctions that can be used anywhere in the code
*/

#ifndef UTIL_H
#define UTIL_H

/**
* Check if two given strings are equals or not. This is a shortcut of the function "strcmp"
* @param string1 
* @param string2
* @return 1 is both strings are equal, 0 else.
*/
int areStringsEquals(char *string1, char *string2);

/**
* Display an array of integers.
* @param nElts the number of elements in the array
* @tab the array to display
*/
void displayArray(int nELts, int *tab);

#endif // !UTIL_H
