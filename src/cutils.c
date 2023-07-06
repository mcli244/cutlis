#include "cutils.h"

/******************** File operation *****************************/
/**
 * Read a file
 *
 * Example:
 * * *
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   char* content = file_read("note.txt");
 *   printf("%s", content);
 *   free(content);
 *   return 0;
 * }
 * * *
 *
 * @param filename file name to read
 * @return dynamic string holds file content
 */
char *file_read(char *filename)
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
 * Example:
 * * *
 * #include <stdio.h>
 * #include <string.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   char* content = "This is my note";
 *   file_write("note.txt", content, strlen(content));
 *   return 0;
 * }
 * * *
 *
 * @param filename file name to write
 * @param content content
 * @param length length of the content
 * @return 0 on success and non zero value on failure
 */
int file_write(char *filename, char *content, int length)
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
 * Example:
 * * *
 * #include <stdio.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   long size;
 *   file_size("note.txt", &size);
 *   printf("note.txt size: %ld", size);
 *   return 0;
 * }
 * * *
 *
 * @param filename file name
 * @param out a long type variable to store the size
 * @return 0 on success and non zero value on failure
 */
int file_size(char *filename, long *out)
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

#if 0
/**
 * Read directory
 *
 * Example:
 * * *
 * #include <stdio.h>
 * #include "utils.h"
 * 
 * int main() 
 * {
 *   dir_read_t dir;
 *   dir_read(&dir,".");
 *   for (int i = 0; i < dir.size; i++)
 *   {
 *     printf("%s: %u\n", dir.names[i], dir.types[i]);
 *   }
 *   dir_read_clean(&dir);
 *   return 0;
 * }
 * * *
 *
 * @param dir_read pointer to dir_read_t
 * @param dirname directory name
 * @return 0 on success and non zero value on failure
 */
int dir_read(dir_read_t *dir_read, char *dirname) {
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(dirname)) == NULL) {
        return -1;
    }
    char **names = (char **) malloc(sizeof(char *));
    if (names == NULL) {
        return -1;
    }
#ifdef _DIRENT_HAVE_D_TYPE
    unsigned char *types = (unsigned char *) malloc(sizeof(unsigned char));
    if (types == NULL) {
        return -1;
    }
#endif
    int i = 0;
    int size = 1;
    while ((ent = readdir(dir)) != NULL) {
        names = (char **) realloc(names, size * sizeof(char *));
        if (names == NULL) {
            return -1;
        }
        names[i] = (char *) malloc((strlen(ent->d_name) + 1) * sizeof(char));
        if (names[i] == NULL) {
            return -1;
        }
        strncpy(names[i], ent->d_name, strlen(ent->d_name));
#ifdef _DIRENT_HAVE_D_TYPE
        types = (unsigned char*) realloc(types,size * sizeof(unsigned char));
            if (types == NULL)
            {
                return -1;
            }
          types[i] = ent->d_type;
#endif
        size++;
        i++;
    }
    dir_read->names = names;
#ifdef _DIRENT_HAVE_D_TYPE
    dir_read->types = types;
#endif
    dir_read->size = i;
    if (closedir(dir))
        return -1;
    return 0;
}

/**
 * function to free the memory after using dir_read
 *
 * @param dir_read pointer to dir_read
 */
void dir_read_clean(dir_read_t *dir_read) {
    if (dir_read != NULL) {
        if (dir_read->names != NULL) {
            for (int i = 0; i < dir_read->size; i++)
            {
                if (dir_read->names[i] != NULL)
                {
                    free(dir_read->names[i]);
                }
            }
            free(dir_read->names);
        }
#ifdef _DIRENT_HAVE_D_TYPE
        if (dir_read->types != NULL) {
            free(dir_read->types);
        }
#endif
    }
}
#endif

/******************** String processing **************************/

/**
 * String format like "sprintf" but it
 * returns the formatted string and it's
 * dynamically allocated
 *
 * Example:
 * * *
 * #include <stdio.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   char* str = string_format("Hello %s", "World");
 *   printf("%s\n", str);
 *   free(str);
 *   return 0;
 * }
 * * *
 *
 * @param format formatted string
 * @return dynamic string
 */
char *string_format(char *format, ...)
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
 * Example:
 * * *
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   char* str = "Collection of utility for C.";
 *   int length;
 *
 *   char** arr = string_split(str, " ", &length);
 *
 *   for(int i = 0; i < length; i++)
 *   {
 *     printf("%s\n", arr[i]);
 *   }
 *
 *   for(int i = 0; i < length; i++)
 *   {
 *     free(arr[i]);
 *   }
 *   free(arr);
 *
 *   return 0;
 * }
 * * *
 *
 * @param s string to split
 * @param delim delimiters string
 * @param out array length
 * @return dynamic array of dynamic strings
 */
char **string_split(char *s, char *delim, int *out)
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
 * Example:
 * * *
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   char* str = string_repeat("Hello World ", 3);
 *   printf("%s", str);
 *   free(str);
 *   return 0;
 * }
 * * *
 *
 * @param s string to repeat
 * @param count number to repeat
 * @return dynamic string
 */
char *string_repeat(char *s, int count)
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
 * Example:
 * * *
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   char* arr[] = {"Hello", "Hola", "Bonjour"};
 *   char* str = string_join(arr, ", ", sizeof(arr) / sizeof(arr[0]));
 *   printf("%s", str);
 *   free(str);
 *   return 0;
 * }
 * * *
 *
 * @param arr array to separate
 * @param sep separator string
 * @param length array length
 * @return dynamic string
 */
char *string_join(char **arr, char *sep, size_t length)
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
 * Example:
 * * *
 * #include <stdio.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   char* str = "Hello World";
 *   int starts = string_starts_with(str, "Hello");
 *   printf("%d", starts);
 *   return 0;
 * }
 * * *
 *
 * @param str the string
 * @param prefix the prefix
 * @return 1 if the character sequence represented by the argument
 * is a prefix of the character sequence represented by the string;
 * 0 otherwise
 */
int string_starts_with(char *str, char *prefix)
{
  return memcmp(prefix, str, strlen(prefix)) == 0;
}

/**
 * Check if string ends with the specified suffix
 *
 * Example:
 * * *
 * #include <stdio.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   char* str = "Hello World";
 *   int ends = string_ends_with(str, "World");
 *   printf("%d", ends);
 *   return 0;
 * }
 * * *
 *
 * @param str the string
 * @param suffix the suffix
 * @return 1 if the character sequence represented by the argument
 * is a suffix of the character sequence represented by the string;
 * 0 otherwise
 */
int string_ends_with(char *str, char *suffix)
{
  int suffix_len = strlen(suffix);
  return memcmp(str + strlen(str) - suffix_len, suffix, suffix_len) == 0;
}

/******************** array processing **************************/
/**
 * Get the max number in array
 *
 * Example:
 * * *
 * #include <stdio.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   int arr[] = {
 *     25,
 *     69,
 *     34,
 *     57,
 *     11
 *   };
 *   int max = array_max(arr, sizeof(arr) / sizeof(arr[0]));
 *   printf("Max number: %d", max);
 *   return 0;
 * }
 * * *
 *
 * @param array array of integers
 * @param length array size
 * @return max number
 */
int array_max(int *array, size_t length)
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
 *
 * Example:
 * * *
 * #include <stdio.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   int arr[] = {
 *     25,
 *     69,
 *     34,
 *     57,
 *     11
 *   };
 *   int max = array_min(arr, sizeof(arr) / sizeof(arr[0]));
 *   printf("Minimum number: %d", max);
 *   return 0;
 * }
 * * *
 *
 * @param array array of integers
 * @param length array size
 * @return minimum number
 */
int array_min(int *array, size_t length)
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
 * Example:
 * * *
 * #include <stdio.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   int rand = random_int(1,10);
 *   printf("%d", rand);
 *   return 0;
 * }
 * * *
 *
 * @param min minimum number
 * @param max maximum number
 * @return random number
 */
int random_int(int min, int max)
{
  srand((unsigned int)time(NULL));
  return ((rand() % ((max) - (min) + 1)) + (min));
}

/**
 * Random character from the given string
 *
 * Example:
 * * *
 * #include <stdio.h>
 * #include <string.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   char* str = "Hello World";
 *   char rand = random_char(str, strlen(str));
 *   printf("%c", rand);
 *   return 0;
 * }
 * * *
 *
 * @param str string
 * @param str_length string length
 * @return random character
 */
char random_char(char *str, size_t str_length)
{
  srand((unsigned int)time(NULL));
  return str[rand() % str_length];
}

char *strdup_safe(const char *str)
{
  if (NULL == str)
    return NULL;
  return strdup(str);
}

void simple_free(void *__ptr)
{
  if (NULL != __ptr)
  {
    free(__ptr);
    __ptr = NULL;
  }
}

void *simple_malloc(size_t size)
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