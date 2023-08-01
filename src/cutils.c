
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdarg.h>
#include <setjmp.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

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

bool cutil_isExist(const char *file)
{
	if (file == NULL)
		return false;

	if (access(file, F_OK) == 0)
		return true;
	return false;
}

const char* cutil_getSuffix(const char* file_name) 
{
    const char* extension = strrchr(file_name, '.');
    if (extension == NULL) {
        return "";
    }
    return extension + 1;
}

char* cutil_rmSuffix(char* file_name) 
{
    char* extension = strrchr(file_name, '.');
    if (extension != NULL) {
        *extension = '\0';
    }
    return file_name;
}

/*It needs to be free after use is not completed*/
char* cutil_getFileAbsolutePath(const char *file)
{
    char *absolute_path = (char *)cutil_simpleMalloc(PATH_MAX);
  
    if (realpath(file, absolute_path) == NULL){
        perror("Failed to get absolute path");
        return NULL;
    }
  
    return absolute_path;
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

/**
 * string_get_size - get the size in the specified units
 * @size:	The size to be converted
 * @units:	units to use (powers of 1000 or 1024)
 * @buf:	buffer to format to
 * @len:	length of buffer
 *
 * This function returns a string formatted to 3 significant figures
 * giving the size in the required units.  Returns 0 on success or
 * error on failure.  @buf is always zero terminated.
 *
 */
int cutil_stringGetSize(uint64_t size, const enum string_size_units units,
		    char *buf, int len)
{
	const char *units_10[] = { "B", "kB", "MB", "GB", "TB", "PB",
				   "EB", "ZB", "YB", NULL};
	const char *units_2[] = {"B", "KiB", "MiB", "GiB", "TiB", "PiB",
				 "EiB", "ZiB", "YiB", NULL };
	const char **units_str[] = {
		[STRING_UNITS_10] =  units_10,
		[STRING_UNITS_2] = units_2,
	};
	const unsigned int divisor[] = {
		[STRING_UNITS_10] = 1000,
		[STRING_UNITS_2] = 1024,
	};
	int i, j;
	uint64_t remainder = 0, sf_cap;
	char tmp[8];

	tmp[0] = '\0';
	i = 0;
	if (size >= divisor[units]) {
		while (size >= divisor[units] && units_str[units][i]) {
			// remainder = do_div(size, divisor[units]);
            remainder = size%divisor[units];
            size /= divisor[units];
			i++;
		}

		sf_cap = size;
		for (j = 0; sf_cap*10 < 1000; j++)
			sf_cap *= 10;

		if (j) {
			remainder *= 1000;
			// do_div(remainder, divisor[units]);
            remainder /= divisor[units];
			snprintf(tmp, sizeof(tmp), ".%03lld",
				 (unsigned long long)remainder);
			tmp[j+1] = '\0';
		}
	}

	snprintf(buf, len, "%lld%s %s", (unsigned long long)size,
		 tmp, units_str[units][i]);

	return 0;
}

const char hex_asc[] = "0123456789abcdef";

/**
 * scnprintf - Format a string and place it in a buffer
 * @buf: The buffer to place the result into
 * @size: The size of the buffer, including the trailing null space
 * @fmt: The format string to use
 * @...: Arguments for the format string
 *
 * The return value is the number of characters written into @buf not including
 * the trailing '\0'. If @size is <= 0 the function returns 0.
 */

int scnprintf(char * buf, size_t size, const char *fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i = vsnprintf(buf, size, fmt, args);
	va_end(args);
	return (i >= size) ? (size - 1) : i;
}

/**
 * hex_dump_to_buffer - convert a blob of data to "hex ASCII" in memory
 * @buf: data blob to dump
 * @len: number of bytes in the @buf
 * @rowsize: number of bytes to print per line; must be 16 or 32
 * @groupsize: number of bytes to print at a time (1, 2, 4, 8; default = 1)
 * @linebuf: where to put the converted data
 * @linebuflen: total size of @linebuf, including space for terminating NUL
 * @ascii: include ASCII after the hex output
 *
 * hex_dump_to_buffer() works on one "line" of output at a time, i.e.,
 * 16 or 32 bytes of input data converted to hex + ASCII output.
 *
 * Given a buffer of uint8_t data, hex_dump_to_buffer() converts the input data
 * to a hex + ASCII dump at the supplied memory location.
 * The converted output is always NUL-terminated.
 *
 * E.g.:
 *   hex_dump_to_buffer(frame->data, frame->len, 16, 1,
 *			linebuf, sizeof(linebuf), 1);
 *
 * example output buffer:
 * 40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f  @ABCDEFGHIJKLMNO
 */
static void hex_dump_to_buffer(const void *buf, size_t len, int rowsize,
			int groupsize, char *linebuf, size_t linebuflen,
			bool ascii)
{
	const uint8_t *ptr = buf;
	uint8_t ch;
	int j, lx = 0;
	int ascii_column;

	if (rowsize != 16 && rowsize != 32)
		rowsize = 16;

	if (!len)
		goto nil;
	if (len > rowsize)		/* limit to one line at a time */
		len = rowsize;
	if ((len % groupsize) != 0)	/* no mixed size output */
		groupsize = 1;

	switch (groupsize) {
	case 8: {
		const uint64_t *ptr8 = buf;
		int ngroups = len / groupsize;

		for (j = 0; j < ngroups; j++)
			lx += scnprintf(linebuf + lx, linebuflen - lx,
				"%16.16llx ", (unsigned long long)*(ptr8 + j));
		ascii_column = 17 * ngroups + 2;
		break;
	}

	case 4: {
		const uint32_t *ptr4 = buf;
		int ngroups = len / groupsize;

		for (j = 0; j < ngroups; j++)
			lx += scnprintf(linebuf + lx, linebuflen - lx,
				"%8.8x ", *(ptr4 + j));
		ascii_column = 9 * ngroups + 2;
		break;
	}

	case 2: {
		const uint16_t *ptr2 = buf;
		int ngroups = len / groupsize;

		for (j = 0; j < ngroups; j++)
			lx += scnprintf(linebuf + lx, linebuflen - lx,
				"%4.4x ", *(ptr2 + j));
		ascii_column = 5 * ngroups + 2;
		break;
	}

	default:
		for (j = 0; (j < rowsize) && (j < len) && (lx + 4) < linebuflen;
		     j++) {
			ch = ptr[j];
			linebuf[lx++] = hex_asc_hi(ch);
			linebuf[lx++] = hex_asc_lo(ch);
			linebuf[lx++] = ' ';
		}
		ascii_column = 3 * rowsize + 2;
		break;
	}
	if (!ascii)
		goto nil;

	while (lx < (linebuflen - 1) && lx < (ascii_column - 1))
		linebuf[lx++] = ' ';
	for (j = 0; (j < rowsize) && (j < len) && (lx + 2) < linebuflen; j++)
		linebuf[lx++] = (isascii(ptr[j]) && isprint(ptr[j])) ? ptr[j]
				: '.';
nil:
	linebuf[lx++] = '\0';
}

/**
 * print_hex_dump - print a text hex dump to syslog for a binary blob of data
 * @level: kernel log level (e.g. KERN_DEBUG)
 * @prefix_str: string to prefix each line with;
 *  caller supplies trailing spaces for alignment if desired
 * @prefix_type: controls whether prefix of an offset, address, or none
 *  is printed (%DUMP_PREFIX_OFFSET, %DUMP_PREFIX_ADDRESS, %DUMP_PREFIX_NONE)
 * @rowsize: number of bytes to print per line; must be 16 or 32
 * @groupsize: number of bytes to print at a time (1, 2, 4, 8; default = 1)
 * @buf: data blob to dump
 * @len: number of bytes in the @buf
 * @ascii: include ASCII after the hex output
 *
 * Given a buffer of uint8_t data, print_hex_dump() prints a hex + ASCII dump
 * to the kernel log at the specified kernel log level, with an optional
 * leading prefix.
 *
 * print_hex_dump() works on one "line" of output at a time, i.e.,
 * 16 or 32 bytes of input data converted to hex + ASCII output.
 * print_hex_dump() iterates over the entire input @buf, breaking it into
 * "line size" chunks to format and print.
 *
 * E.g.:
 *   print_hex_dump(KERN_DEBUG, "raw data: ", DUMP_PREFIX_ADDRESS,
 *		16, 1, frame->data, frame->len, 1);
 *
 * Example output using %DUMP_PREFIX_OFFSET and 1-byte mode:
 * 0009ab42: 40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f  @ABCDEFGHIJKLMNO
 * Example output using %DUMP_PREFIX_ADDRESS and 4-byte mode:
 * ffffffff88089af0: 73727170 77767574 7b7a7978 7f7e7d7c  pqrstuvwxyz{|}~.
 */
static void print_hex_dump(const char *level, const char *prefix_str, int prefix_type,
			int rowsize, int groupsize,
			const void *buf, size_t len, bool ascii)
{
	const uint8_t *ptr = buf;
	int i, linelen, remaining = len;
	unsigned char linebuf[200];

	if (rowsize != 16 && rowsize != 32)
		rowsize = 16;

	for (i = 0; i < len; i += rowsize) {
		linelen = min(remaining, rowsize);
		remaining -= rowsize;
		hex_dump_to_buffer(ptr + i, linelen, rowsize, groupsize,
				linebuf, sizeof(linebuf), ascii);

		switch (prefix_type) {
		case DUMP_PREFIX_ADDRESS:
			printf("%s%s%*p: %s\n", level, prefix_str,
				(int)(2 * sizeof(void *)), ptr + i, linebuf);
			break;
		case DUMP_PREFIX_OFFSET:
			printf("%s%s%.8x: %s\n", level, prefix_str, i, linebuf);
			break;
		default:
			printf("%s%s%s\n", level, prefix_str, linebuf);
			break;
		}
	}
}

/**
 * print_hex_dump_bytes - shorthand form of print_hex_dump() with default params
 * @prefix_str: string to prefix each line with;
 *  caller supplies trailing spaces for alignment if desired
 * @prefix_type: controls whether prefix of an offset, address, or none
 *  is printed (%DUMP_PREFIX_OFFSET, %DUMP_PREFIX_ADDRESS, %DUMP_PREFIX_NONE)
 * @buf: data blob to dump
 * @len: number of bytes in the @buf
 *
 * Calls print_hex_dump(), with log level of KERN_DEBUG,
 * rowsize of 16, groupsize of 1, and ASCII output included.
 */
void cutils_printHexDumpBytes(const char *prefix_str, int prefix_type,
			const void *buf, size_t len)
{
	print_hex_dump("", prefix_str, prefix_type, 16, 1,
			buf, len, 1);
}