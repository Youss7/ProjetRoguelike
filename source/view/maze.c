/**
 * @file view/maze.c
 * Fichier implémentant les fonctions permettant de contrôler l'affichage du labyrinthe.
 * @author Hector Basset
 * @date 12 décembre 2014
 */

//librairies du système
#include <stdio.h>

//librairies de la vue
#include "ansi.h"
#include "maze.h"
#include "terminal.h"

//librairies du modèle
#include "../model/maze.h"

/**
 * Fonction permettant d'afficher une case en fonction de son type.
 * @param square Le type de case à afficher.
 */
static void print_square(Square * square) {
	switch (square->type) {
		case AIR:
			ansi_set_bg_color(ANSI_BLACK);
			break;
		case WALL:
			ansi_set_bg_color(ANSI_LIGHT_GREY);
			break;
		case WATER:
			ansi_set_bg_color(ANSI_LIGHT_BLUE);
			break;
		case FIRE:
			ansi_set_bg_color(ANSI_LIGHT_RED);
			break;
	}
	if (square->entity == NULL) {
		putchar(' ');
	} else {
		switch (square->entity->type) {
			case PLAYER:
				ansi_set_color(ANSI_GREEN);
				fputs("☻", stdout);
				break;
			case GOBLIN:
				ansi_set_color(ANSI_RED);
				fputs("⚉", stdout);
				break;
			case GHOST:
				ansi_set_color(ANSI_WHITE);
				fputs("⚇", stdout);
				break;
			default:
				break;
		}
	}
}

void display_maze() {
	const int width = get_terminal_width();
	int i, j;
	for (i = 0 ; i < g_maze->size ; i++) {
		ansi_set_column((width - g_maze->size) / 2);
		for (j = 0 ; j < g_maze->size ; j++) {
			print_square(&(g_maze->squares[i * g_maze->size + j]));
		}
		ansi_set_bg_color(ANSI_BLACK);
		putchar('\n');
	}
	g_maze_height = g_maze->size;
}
