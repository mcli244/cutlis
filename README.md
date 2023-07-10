# cutlis
Some small tools written in C language

// api list

/******************** File operation *****************************/
extern char *cutil_freadAll(char *filename);
extern int cutil_fwriteAll(char *filename, char *content, int length);
extern int cutil_getFileSize(char *filename, long *out);
extern int cutil_getFileNameBySuffix(const char *directory, char *suffix, char *outFileName, int outPathBufSize);
extern int cutil_getFilePath(const char *inFileName, char *outPathBuf, int outPathBufSize);


/******************** String processing **************************/
extern char* cutil_stringFormat(char *format, ...);
// extern char** string_split(char* s, char* delim, int* out);
extern char* cutil_stringRepeat(char* s, int count);
extern char* cutil_stringJoin(char** arr, char* sep, size_t length);
extern int cutil_stringEndsWith(char* str, char* suffix);
extern int cutil_stringStartsWith(char* str, char* prefix);

/******************** array processing **************************/
#define CUTIL_ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))
extern int cutil_arrayMax(int* array, size_t length);
extern int cutil_arrayMin(int* array, size_t length);

/************************* other  ******************************/
extern char cutil_randomChar(char* str, size_t str_length);
extern int cutil_randomInt(int min, int max);
extern void cutil_simpleFree(void *__ptr);
extern void *cutil_simpleMalloc(size_t size);
extern char *cutil_simpleStrdup(const char *str);




