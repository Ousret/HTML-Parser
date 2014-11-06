#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>
 
struct MemoryStruct {

  char *memory;
  size_t size;
  
};

FILE * temp = NULL;
FILE * parsed = NULL;
FILE * final = NULL;
 
 
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
 
 
int main(void)
{
  CURL *curl_handle;
  CURLcode res;
  char url[100]={};
  char word[1000];
  int opened = 0;
  strcpy(url,"http://porterplainte.info/carte-complete-police.php");
  struct MemoryStruct chunk;
  temp = fopen("temp.txt","w");
 
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
 
  /* some servers don't like requests that are made without a user-agent
     field, so we provide one */ 
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
  /* get it! */ 
  res = curl_easy_perform(curl_handle);
 
  /* check for errors */ 
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }
  else {
    /*
     * Now, our chunk.memory points to a memory block that is chunk.size
     * bytes big and contains the remote file.
     *
     * Do something nice with it!
     */ 
    printf("%lu bytes retrieved\n", (long)chunk.size);
  }
  
  int i = 0;
  printf("\n======== \nTaille du chunk : %zu\n========\n",chunk.size);
  
  //Ecrit dans temp le code HTML brute
  for (i = 0 ; i < chunk.size ; i++){
  	fprintf(temp,"%c",chunk.memory[i]);
  }
  
  fclose(temp); //Ferme le fichier temp
  
  parsed = fopen("temp2.txt","w"); //Sauver le code des lignes <li></li>
  temp = fopen("temp.txt","r"); //Ouvrir le fichier HTML brute
  
  i=0; //
  
  //fscanf(temp, "%*s<%s>", word)
  
  char capture[10];
  //int n = 0;
  
  do {
  
  	
  	fscanf(temp,"%9c", capture);
  	capture[9] = '\0';
  	//n++;
  	
  	//printf("Soyons fou\n");
  	
  	
  	sscanf(capture, "<%s>", word);
  	printf("DEBUG : %s %s",word,capture);
  
  	//printf("%i", i);
  	//fscanf(temp, "%", word);
  	
  	if(strcmp(word,"li") == 0){
  		i = 1;
  	}
  		
  } while (i != 1);
  
  while (i == 1) {
  
  	if(!fscanf(temp,"%s</li>",word)) break;
  	
  	fprintf(parsed,"%s",word);
  	i--;
  	
  	printf("\n -- %i : %s",i,word);
  	
  }
  
  fprintf(parsed,"%c",'%');
  fclose(temp);
  fclose(parsed);
  parsed=fopen("temp2.txt","r");
  final=fopen("commissariat.txt","w");
  char key = 0;
  opened=0;
  while(key!='%'){
  	fscanf(parsed,"%c",&key);
  	if(key=='<') opened = 1;
  	else if(key=='>') opened = 0;
  	if (opened) fprintf(final," ");
  	else fprintf(final,"%c",key);
  }
  fclose(parsed);
  fclose(final);
  //
  
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle); 
  if(chunk.memory) free(chunk.memory); 
  /* we're done with libcurl, so clean it up */ 
  curl_global_cleanup();
  return 0;
}
 
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}