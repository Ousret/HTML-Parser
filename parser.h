/* F Defs */
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
char * stj_savehtml(char url[256], char dest_file[256]);
char * stj_getbalisecontent(char * src_html, char balise[50], int indice);
void stj_cleanup();

struct MemoryStruct {char *memory; size_t size; };

extern FILE * temp;
extern FILE * parsed;
extern FILE * final;

extern CURL *curl_handle;
extern CURLcode res;
extern struct MemoryStruct chunk;