/**
 * \file commands.c
 * \brief Parse argv and displaying help with error if it's the case
 * \author TAHRI Ahmed, SIMON Jérémy
 * \version 0.1
 * \date 8th november 2014
 *
 * Just parse argv and disp help if needed.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes/commands.h"

void display_help(int code) {
	
	printf(" .----------------. .----------------. .----------------. \n");
	printf("| .--------------. | .--------------. | .--------------. |\n");
	printf("| |    _______   | | |  _________   | | |     _____    | |\n");
	printf("| |   /  ___  |  | | | |  _   _  |  | | |    |_   _|   | |\n");
	printf("| |  |  (__ \\_|  | | | |_/ | | \\_|  | | |      | |     | |\n");
	printf("| |   '.___`-.   | | |     | |      | | |   _  | |     | |\n");
	printf("| |  |`\\____) |  | | |    _| |_     | | |  | |_' |     | |\n");
	printf("| |  |_______.'  | | |   |_____|    | | |  `.___.'     | |\n");
	printf("| |              | | |              | | |              | |\n");
	printf("| '--------------' | '--------------' | '--------------' |\n");
	printf(" '----------------' '----------------' '----------------' \n\n");
	printf("\t Authors: TAHRI Ahmed@Ousret\n");
	printf("\t Project: Free HTML Parser in C\n");
	printf("\t Link: http://www.github.com/Ousret for new release\n\n");
	printf("\t Command: ./htmlparser [-g, -d, -s] -u 'url' -b '<balise>' -i indice\n\n");
	printf("\t Code: %i\n", code); //Switch code..
	printf("\t -g: Get data from specific balise\n");
	printf("\t -d: Delete specific balise\n");
	printf("\t -i [integer]: Apply action to specific indice\n");
	printf("\t -s [integer]: Set the start indice\n");
	printf("\t -e [integer]: Set the end indice\n");
	printf("\t -k [Filename]: Custom filename destination, default dest.html\n\n");
	
}

int getcommand(int argc, char * argv[], char command, int * indice) {

	int i = 0;
	
	for (i = 1; i < argc; i++) {
		if (argv[i][1] == command) {
			*indice = i;
			return 1;
		}
	}
	
	return 0;

}