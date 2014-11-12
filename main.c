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

#include "includes/main.h"
#include "includes/commands.h"

/**
 * \fn int main(int argc, char * argv[])
 * \brief Get input to process parsing
 *
 * \param argc Number of arguments
 * \param argv String args 
 * \return 0 - Program went fine; 1 bad command; -1 Something wrong
 */
int main(int argc, char * argv[])
{
	char url[256], balise_search[25], file[256];
	int needed_occ = 0, local_file = 0, start_occ = 0, end_occ = 0;
	int com_indice = 0, i = 0;
	
	if (getcommand(argc, argv, 'h', &com_indice)) {
	
		display_help(0);
		return 0;
		
	}
	
	if (getcommand(argc, argv, 'u', &com_indice)) { //Online
		
		if ((argc-1) < (com_indice+1)) {
			display_help(1); 
			return 1;
		}
		
		strcpy(url, argv[com_indice+1]);
		strcpy(file, "get.in");
		
	}else if(getcommand(argc, argv, 'f', &com_indice)) { //Offline
	
		if ((argc-1) < (com_indice+1)) {
			display_help(2); 
			return 1;
		}
		
		strcpy(file, argv[com_indice+1]);
		local_file = 1;
		
	}else{
		
		display_help(12);
		return 1;
		
	}
	
	//Get markup..
	if (getcommand(argc, argv, 'm', &com_indice)) {
	
		if ((argc-1) < (com_indice+1)) {
			display_help(3); 
			return 1;
		}
		
		strcpy(balise_search, argv[com_indice+1]);
	
	}else{
	
		display_help(4); 
		return 1;
		
	}
	
	//Get indice or range indice
	if (getcommand(argc, argv, 'i', &com_indice)) {
	
		if ((argc-1) < (com_indice+1)) {
			display_help(5); 
			return 1;
		}
		
		needed_occ = atoi(argv[com_indice+1]);
		
		if (needed_occ == 0) {
		
			display_help(6);
			return 1;
			
		}
		
	}else if(getcommand(argc, argv, 's', &com_indice)) {
	
		if ((argc-1) < (com_indice+1)) {
			display_help(7); 
			return 1;
		}
		
		start_occ = atoi(argv[com_indice+1]);
		
		if (start_occ == 0) {
		
			display_help(8);
			return 1;
			
		}
		
		if (getcommand(argc, argv, 'e', &com_indice)) {
		
			if ((argc-1) < (com_indice+1)) {
				display_help(9); 
				return 1;
			}
			
			end_occ = atoi(argv[com_indice+1]);
			
		}
		
	}else {
	
		display_help(10); 
		return 1;
		
	}
	
	//If it's okay we can start the process
	if (local_file == 0) {
		stj_savehtml(url, file);
	}
	
	if ((start_occ != 0) && (end_occ != 0)) {
		
		for (i = 1; i < end_occ; i++) {
			fprintf(stdout, "%s\n", stj_getbalisecontent(file, balise_search, i));
		}
		
	}else{
	
		fprintf(stdout, "%s\n", stj_getbalisecontent(file, balise_search, needed_occ));
		
	}
	
	return 0;
}
