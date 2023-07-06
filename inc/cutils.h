/* ============================================================================
 * 
 * Copyright (c) 2023 LXJ
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * ============================================================================
*/

#ifndef __CUTILS_H__
#define __CUTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdarg.h>
#include <setjmp.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************
Thanks for the following items
base on:
    https://github.com/thechampagne/utils.h.git
******************************************************************/

/******************** File operation *****************************/
extern char *cutil_freadAll(char *filename);
extern int cutil_fwriteAll(char *filename, char *content, int length);
extern int cutil_getFileSize(char *filename, long *out);

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

#ifdef __cplusplus
}
#endif






#endif /*__CUTILS_H__*/