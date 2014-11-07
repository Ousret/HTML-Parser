#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

char * stj_getbalisecontent(char * src_html, char balise[25], int indice) {

	unsigned int occ_balise = 0;
	int i = 0, stage = 0;
	
	char * read_tmp;
	char read_c_tmp = 0;
	
	char * capture;
	
	FILE * src_html_input = NULL;
	
	src_html_input = fopen(src_html, "r");
	
	if (!src_html_input) return "Unable to read input html";
	
	while (fscanf(src_html_input, "%c", read_c_tmp) == 1) {
	
		if (read_c_tmp == balise[stage]) stage++;
		
		if (stage == strlen(balise)) {
			occ_balise++;
			
			if (occ_balise == indice) {
				break;
			}else{
				stage = 0;
			}
			
		}
		
	}
	
	while (fscanf(src_html_input, "%c", read_c_tmp) == 1) {
	
		if (read_c_tmp != '<') {
		
			capture[i] = read_c_tmp;
		
		}else{
		
			break;
			
		}
		
	}
	
	return capture;

}
