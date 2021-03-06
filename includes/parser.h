/**
 * \file parser.h
 * \brief Header for our parser
 * \author TAHRI Ahmed, SIMON Jérémy
 * \version 0.1
 * \date 8th november 2014
 *
 */

/* F Defs */
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
char * stj_savehtml(char url[256], char dest_file[256]);
int stj_getbalisecontent(char * src_html, char balise[50], int indice);
void stj_cleanup();

/**
 * \struct MemoryStruct
 * \brief Contain downloaded data
 *
 * Just in order to keep downloaded data during download ^^
 */
struct MemoryStruct {
	char *memory; /*!< HTML data downloaded in there */
	size_t size; /*!< The size of memory var */
};

extern FILE * temp;

extern CURL *curl_handle;
extern CURLcode res;
