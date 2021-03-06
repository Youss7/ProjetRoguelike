/**
 * @file utility/math.c
 * Fichier implémentant les fonctions mathématiques utilitaires.
 * @author Hector Basset
 * @date 10 décembre 2014
 */

//librairies du système
#include <stdlib.h>

int rand_between(int a, int b) {
	a += 1;
	return (rand() % (b - a)) + a;
}

char mins(short a, short b) {
	return a < b ? a : b;
}

char maxs(short a, short b) {
	return a > b ? a : b;
}
