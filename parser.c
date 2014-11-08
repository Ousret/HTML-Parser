/**
 * \file parser.c
 * \brief Funtions using cURL in order to extract data from HTML file
 * \author TAHRI Ahmed, SIMON Jérémy
 * \version 0.1
 * \date 8th november 2014
 *
 * Useful func. to parse and download HTML data.
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "parser.h"

void stj_cleanup() {

	/* cleanup curl stuff */ 
	curl_easy_cleanup(curl_handle);  
	/* we're done with libcurl, so clean it up */ 
	curl_global_cleanup();
	
}

char * stj_savehtml(char url[256], char dest_file[256]) {


	struct MemoryStruct chunk;
	//strcpy(url,"http://porterplainte.info/carte-complete-police.php");
	FILE * tmp_html = NULL;
	
	char * msg = malloc(100);
	
	tmp_html = fopen(dest_file,"w");

	if (tmp_html == NULL) return "Unable to create dest file !";  

	chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
	chunk.size = 0;    /* no data at this point */ 
 
	curl_global_init(CURL_GLOBAL_ALL);
 
	/* init the curl session */ 
	curl_handle = curl_easy_init();
 
	/* specify URL to get */ 
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
 
	/* send all data to this function  */ 
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
	/* we pass our 'chunk' struct to the callback function */ 
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 
	/* some servers don't like requests that are made without a user-agent field, so we provide one */ 
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-stj-spi/1.0");
 
	/* get it! */ 
	res = curl_easy_perform(curl_handle);
 
	/* check for errors */ 
	if(res != CURLE_OK) {
		sprintf(msg, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		return msg;
	}else{
		/*
     	* Now, our chunk.memory points to a memory block that is chunk.size
     	* bytes big and contains the remote file.
     	*
     	* Do something nice with it!
     	*/ 
    	sprintf(msg, "%lu bytes retrieved\n", (long)chunk.size);
	}
  
	int i = 0;

	//Ecrit dans temp le code HTML brute
	for (i = 0 ; i < (chunk.size) ; i++){
		fprintf(tmp_html, "%c", chunk.memory[i]);
	}
  
	fclose(tmp_html); //Ferme le fichier temp

	return msg;

}

char * stj_getbalisecontent(char * src_html, char balise[50], int indice) {

	unsigned int occ_balise = 0;
	int i = 0, stage = 0;

	long stream_state = 0, stream_last = 0;

	char read_c_tmp = 0;
	
	char * capture = malloc(1);
	
	FILE * src_html_input = NULL;
	
	src_html_input = fopen(src_html, "r");
	
	if (!src_html_input) return "Unable to read input html";
	
	while (fscanf(src_html_input, "%c", &read_c_tmp) == 1) {
	
		stream_state++; //We do have read one char.. counting..
		
		if (read_c_tmp == balise[stage]) {
			
			if (stage == 0) {
			
				stream_last = stream_state;
				stage++;
				fprintf(stdout, "Stage init %c -- Last occ %i -- Stream %i\n", read_c_tmp, stream_last, stream_state);
				
			}else{
			
				if (stream_last == (stream_state-1)) {
					stream_last = stream_state;
					stage++;
					fprintf(stdout, "Stage +1 %c -- Last occ %i -- Stream %i\n", read_c_tmp, stream_last, stream_state);
				}else{
			
					stage = 0;
					fprintf(stdout, "Stage reset %c -- Last occ %i -- Stream %i\n", read_c_tmp, stream_last, stream_state);
				}	
			
			}
			
		}
		
		
		if (stage == (strlen(balise)-1)) {
			occ_balise++;
			
			if (occ_balise == indice) {
				break;
			}else{
				stage = 0;
			}
			
		}
		
		
	}
	//strcpy(url,"http://porterplainte.info/carte-complete-police.php");
	
	// avoid some common problems with this, website change from one to another one..
	// some use for exemple <li>, other <li style="sample" ... >
	// Hope you could understood why ^^
	
	while (fscanf(src_html_input, "%c", &read_c_tmp) == 1) {
		
		stream_state++;
		
		if (read_c_tmp == '>') {
			fprintf(stdout, "Complete search %c -- Last occ %i -- Stream %i\n", read_c_tmp, stream_last, stream_state);
			break;
		}else{
			fprintf(stdout, "Complete search %c -- Last occ %i -- Stream %i\n", read_c_tmp, stream_last, stream_state);
		}
	
	}
	
	//Reset stage because we need to find the end balise
	stage = 0;
	
	//Need to transform <li> to </li> for exemple
	for (i = strlen(balise)+1; i > 0; i--) {
	
		balise[i+1] = balise[i];
		
	}
	
	balise[1] = '/'; 
	
	// While we can read some char in the input file
	while (fscanf(src_html_input, "%c", &read_c_tmp) == 1) {
	
		stream_state++; //We do have read one char.. counting..
		
		//Checking if we hit the end
		if (read_c_tmp == balise[stage]) {
			
			if (stage == 0) {
			
				stream_last = stream_state;
				stage++;
				
			}else{
			
				if (stream_last == (stream_state-1)) {
					
					stream_last = stream_state;
					stage++;

				}else{
			
					stage = 0;

				}	
			
			}
			
		}
		
		if (stage == strlen(balise)) break; //If we find all char, if we match balise var
		
		realloc(capture, sizeof(capture)+1); //We need to expend the capture var in order to write more..
		
		capture[i] = read_c_tmp;
		capture[i+1] = '\0';
		
		i++;
		
	}
	
	if (strlen(capture) > 0) {
		
		return capture;
		
	}else{
		
		return "Nothing found here, end of file.. Sorry !";
		
	}

}


static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
	mem->memory = realloc(mem->memory, mem->size + realsize + 1);
	
	if(mem->memory == NULL) {
		/* out of memory! */ 
    	printf("<ABRT> Not enough memory (realloc returned NULL)\n");
    	exit(-1);
	}
 
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
 
	return realsize;
}