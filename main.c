#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "parser.h"

CURL *curl_handle;
CURLcode res;
struct MemoryStruct chunk;

int main(void)
{
	char url[256], balise_search[25];
	
	printf("<Source HTML> url:");
	scanf("%s", url);
	
	printf("<Result> %s\n", stj_savehtml(url, "dest.html"));
	
	printf("<Balise> code:");
	scanf("%s", balise_search);
	
	printf("<Result> %s\n", stj_getbalisecontent("dest.html", balise_search, 1));
	
	stj_cleanup();
	
	return 0;
}
 
 

