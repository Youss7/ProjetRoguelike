/**
 * @file model/maze.c
 * Fichier implémentant les fonctions permettant la création, la supression et la gestion du labyrinthe et de ses cases.
 * @author Hector Basset
 * @date 16 décembre 2014
 */

//librairies du système
#include <stdlib.h>

//librairies du modèle
#include "maze.h"

/**
 * La taille minimum (taille du niveau 1).
 */
#define MIN_SIZE 30

/**
 * La vitesse d'accroissement de la taille du labyrinthe.
 */
#define GROWING_SPEED 1.1

/**
 * Fonction libérant l'espace mémoire occupé par les cases du labyrinthe.
 * Cette fonction détruit aussi les entités se trouvant sur ces cases.
 */
static void free_squares() {
	short row, column;
	for (row = 0 ; row < g_maze->size ; row++) {
		for (column = 0 ; column < g_maze->size ; column++) {
			free(g_maze->squares[row * g_maze->size + column].entity);
		}
	}
	free(g_maze->squares);
}

void generate_maze() {
	short row, column;
	if (g_maze == NULL) {
		g_maze = malloc(sizeof(Maze));
		g_maze->size = MIN_SIZE;
	} else {
		free_squares();
		g_maze->size *= GROWING_SPEED;
	}
	g_maze->squares = malloc(g_maze->size * g_maze->size * sizeof(Square));
	for (row = 0 ; row < g_maze->size ; row++) {
		for (column = 0 ; column < g_maze->size ; column++) {
			g_maze->squares[row * g_maze->size + column].type = WALL;
			g_maze->squares[row * g_maze->size + column].entity = NULL;
		}
	}
	for (row = 1 ; row < (g_maze->size - 1) ; row++) {
		for (column = 1 ; column < (g_maze->size - 1) ; column++) {
			g_maze->squares[row * g_maze->size + column].type = AIR;
		}
	}
}

void free_maze() {
	free_squares();
	free(g_maze);
}
