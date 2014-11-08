/**
 * \file main.c
 * \brief Parser processing and output result OR get input to process
 * \author TAHRI Ahmed, SIMON Jérémy
 * \version 0.1
 * \date 8th november 2014
 *
 * Handle request and process them in order to send the result to stdout
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "parser.h"

CURL *curl_handle;
CURLcode res;

/**
 * \fn int main(int argc, char * argv[])
 * \brief Get input to process parsing
 *
 * \param argc Number of arguments
 * \param argv String args 
 * \return 0 - Program went fine; -1 Something wrong
 */
int main(int argc, char * argv[])
{
	char url[256], balise_search[25];
	int needed_occ = 0;
	
	if (argc == 4) {
	
		//Auto-Process
		printf("Auto-Process\n");
		
		if ( strlen(argv[1]) < 256) {
		
			strcpy(url, argv[1]);
			
		}else{
			printf("<Us> Your url link is too long !\n");
			return -1;
		}
		
		if (strlen(argv[2]) < 25) {
		
			strcpy(balise_search, argv[2]);
			
		}else{
		
			printf("<Us> Your balise is too long !\n");
			return -1;
			
		}
		
		needed_occ = atoi(argv[3]); 
		
		if (needed_occ <= 0) {
			
			printf("<Us> Your occ is not correct !\n");
			return -1;
		
		}
		stj_savehtml(url, "dest.html");
		fprintf(stdout ,"%s\n", stj_getbalisecontent("dest.html", balise_search, needed_occ));
		
	}else{
	
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
		printf("\t Authors: TAHRI Ahmed@Ousret; SIMON Jeremy@Jokoast\n");
		printf("\t Project: Free HTML Parser in C\n");
		printf("\t Link: http://www.github.com/Jokoast for new release\n\n");
		printf("\t Command: ./htmlparser 'url' '<balise>' indice\n\n");
		printf("<You> Type the url you need to parse: ");
		scanf("%s", url);
		
		printf("<You> What balise do we need to look for :");
		scanf("%s", balise_search);
		
		printf("<You> What occurrence ? :");
		scanf("%i", &needed_occ);
		
		stj_savehtml(url, "dest.html");
		printf("<Us> What we found:\n> %s\n", stj_getbalisecontent("dest.html", balise_search, needed_occ));
	}
	
	//stj_cleanup(); //Free Curl from his duty
	
	return 0;
}
 
 

