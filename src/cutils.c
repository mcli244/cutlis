#include "cutils.h"

/******************** File operation *****************************/
/**
 * @description: read file all
 * @param {char} *filename
 * @return {char *} dynamically allocated
 */
char *cutil_freadAll(char *filename)
{
  FILE *file;
  int ch;
  if ((file = fopen(filename, "r")) == NULL)
    return NULL;
  if (fseek(file, 0L, SEEK_END))
    return NULL;
  long size = ftell(file);
  if (fseek(file, 0L, SEEK_SET))
    return NULL;
  char *content = (char *)malloc((size + 1) * sizeof(char));
  if (content == NULL)
    return NULL;
  int i = 0;
  while ((ch = getc(file)) != EOF)
  {
    content[i] = (char)ch;
    i++;
  }
  if (fclose(file))
    return NULL;
  return content;
}

/**
 * Write a file
 *
 * @param filename file name to write
 * @param content content
 * @param length length of the content
 * @return 0 on success and non zero value on failure
 */
int cutil_fwriteAll(char *filename, char *content, int length)
{
  FILE *file;
  if ((file = fopen(filename, "w")) == NULL)
    return -1;
  for (int i = 0; i < length; i++)
  {
    fprintf(file, "%c", content[i]);
  }
  if (fclose(file))
    return -1;
  return 0;
}

/**
 * File size
 *
 * @param filename file name
 * @param out a long type variable to store the size
 * @return 0 on success and non zero value on failure
 */
int cutil_getFileSize(char *filename, long *out)
{
  FILE *file;
  if ((file = fopen(filename, "r")) == NULL)
  {
    return -1;
  }
  if (fseek(file, 0L, SEEK_END))
    return -1;
  *out = ftell(file);
  if (fclose(file))
    return -1;
  return 0;
}

int cutil_getFilePath(const char *inFileName, char *outPathBuf, int outPathBufSize)
{
    if(!inFileName || !outPathBuf || !outPathBufSize)
        return -1;

    strncpy(outPathBuf, inFileName, outPathBufSize);

    char *p = strrchr(outPathBuf, '/');;
    if (p != NULL) {
            *p = '\0';
    }
    else
        return -1;
    return 0;
}

int cutil_getFileNameBySuffix(const char *directory, char *suffix, char *outFileName, int outPathBufSize)
{
    DIR * dir;
    char* extension;

    if(!directory || !suffix || !outFileName || !outPathBufSize)
        return -1;
    
    struct dirent * ptr;
    dir = opendir(directory);
    while((ptr = readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0||strcmp(ptr->d_name,"..")==0)
        {
            continue;
        }
        if(ptr->d_type == DT_REG)
        {
            extension = strrchr(ptr->d_name, '.');
            if (extension != NULL && 0 == strcmp(extension+1, suffix)) {
                strncpy(outFileName, ptr->d_name, outPathBufSize);
                goto exit;
            }
        }
        
    }
    closedir(dir);
    return -1;

exit:
    closedir(dir);
    return 0;
}

/******************** String processing **************************/

/**
 * String format like "sprintf" but it
 * returns the formatted string and it's
 * dynamically allocated
 *
 * @param format formatted string
 * @return dynamic string
 */
char *cutil_stringFormat(char *format, ...)
{
  va_list arg;
  int len;
  va_start(arg, format);

  len = vsnprintf(0, 0, format, arg);
  char *str = (char *)malloc((len + 1) * sizeof(char));
  if (str == NULL)
  {
    return NULL;
  }
  va_start(arg, format);
  vsnprintf(str, (len + 1), format, arg);
  va_end(arg);
  return str;
}

/**
 * Split string to array of strings
 * by delimiters string
 *
 * @param s string to split
 * @param delim delimiters string
 * @param out array length
 * @return dynamic array of dynamic strings
 */
char **cutil_stringSplit(char *s, char *delim, int *out)
{
  char *str = (char *)malloc((strlen(s) + 1) * sizeof(char));
  if (str == NULL)
  {
    return NULL;
  }

  strncpy(str, s, strlen(s));

  char **array = (char **)malloc(sizeof(char *));
  memset(array, 0, sizeof(char *));
  if (array == NULL)
  {
    free(str);
    return NULL;
  }
  char *token = strtok(str, delim);

  int i = 0;
  while (token != NULL)
  {
    if (i != 0)
    {
      array = (char **)realloc(array, (i + 1) * sizeof(char *));
      if (array == NULL)
      {
        free(str);
        return NULL;
      }
    }
    array[i] = (char *)malloc((strlen(token) + 1) * sizeof(char));
    memset(array[i], 0, (strlen(token) + 1) * sizeof(char));
    if (array[i] == NULL)
    {
      free(str);
      return NULL;
    }
    strncpy(array[i], token, strlen(token));
    token = strtok(NULL, delim);
    i++;
  }
  *out = i;
  free(str);
  return array;
}

/**
 * Repeat string with specified count
 *
 * @param s string to repeat
 * @param count number to repeat
 * @return dynamic string
 */
char *cutil_stringRepeat(char *s, int count)
{
  if (count <= 0)
  {
    return s;
  }
  char *str = (char *)malloc((strlen(s) * count) + 1 * sizeof(char));
  if (str == NULL)
  {
    return NULL;
  }
  for (int i = 0; i < count; i++)
  {
    strcat(str, s);
  }
  return str;
}

/**
 * Array to string with specified separator
 *
 * @param arr array to separate
 * @param sep separator string
 * @param length array length
 * @return dynamic string
 */
char *cutil_stringJoin(char **arr, char *sep, size_t length)
{
  char *str = (char *)malloc(sizeof(char));
  if (str == NULL)
  {
    return NULL;
  }
  for (int i = 0; i < length; i++)
  {
    if (i != 0)
    {
      if(sep == NULL)
        str = (char *)realloc(str, (strlen(arr[i])) * sizeof(char));
      else
        str = (char *)realloc(str, (strlen(arr[i]) + strlen(sep)) * sizeof(char));
      if (str == NULL)
      {
        return NULL;
      }
    }
    strcat(str, arr[i]);
    if ((i + 1 < length))
    {
      if(sep != NULL)
        strcat(str, sep);
    }
  }
  return str;
}

/**
 * Check if string starts with the specified prefix
 *
 * @param str the string
 * @param prefix the prefix
 * @return 1 if the character sequence represented by the argument
 * is a prefix of the character sequence represented by the string;
 * 0 otherwise
 */
int cutil_stringStartsWith(char *str, char *prefix)
{
  return memcmp(prefix, str, strlen(prefix)) == 0;
}

/**
 * Check if string ends with the specified suffix
 *
 * @param str the string
 * @param suffix the suffix
 * @return 1 if the character sequence represented by the argument
 * is a suffix of the character sequence represented by the string;
 * 0 otherwise
 */
int cutil_stringEndsWith(char *str, char *suffix)
{
  int suffix_len = strlen(suffix);
  return memcmp(str + strlen(str) - suffix_len, suffix, suffix_len) == 0;
}

/******************** array processing **************************/
/**
 * Get the max number in array
 *
 * @param array array of integers
 * @param length array size
 * @return max number
 */
int cutil_arrayMax(int *array, size_t length)
{
  int max = array[0];

  for (int i = 0; i < length; i++)
  {
    if (array[i] > max)
    {
      max = array[i];
    }
  }
  return max;
}

/**
 * Get the minimum number in array
 * @param array array of integers
 * @param length array size
 * @return minimum number
 */
int cutil_arrayMin(int *array, size_t length)
{
  int min = array[0];

  for (int i = 0; i < length; i++)
  {
    if (array[i] < min)
    {
      min = array[i];
    }
  }
  return min;
}

/************************* other  ******************************/
/**
 * Generate random number between range
 *
 * @param min minimum number
 * @param max maximum number
 * @return random number
 */
int cutil_randomInt(int min, int max)
{
  srand((unsigned int)time(NULL));
  return ((rand() % ((max) - (min) + 1)) + (min));
}

/**
 * Random character from the given string
 *
 * @param str string
 * @param str_length string length
 * @return random character
 */
char cutil_randomChar(char *str, size_t str_length)
{
  srand((unsigned int)time(NULL));
  return str[rand() % str_length];
}

char *cutil_simpleStrdup(const char *str)
{
  if (NULL == str)
    return NULL;
  return strdup(str);
}

void cutil_simpleFree(void *__ptr)
{
  if (NULL != __ptr)
  {
    free(__ptr);
    __ptr = NULL;
  }
}

void *cutil_simpleMalloc(size_t size)
{
  void *ptmp = NULL;

  ptmp = malloc(size);
  if (NULL == ptmp)
  {
    return NULL;
  }
  memset(ptmp, 0, size);

  return ptmp;
}
