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
extern char *file_read(char *filename);
extern int file_write(char *filename, char *content, int length);
extern int file_size(char *filename, long *out);
// extern int dir_read(dir_read_t *dir_read, char *dirname);
// extern void dir_read_clean(dir_read_t *dir_read);

/******************** String processing **************************/
extern char* string_format(char *format, ...);
// extern char** string_split(char* s, char* delim, int* out);
extern char* string_repeat(char* s, int count);
extern char* string_join(char** arr, char* sep, size_t length);
extern int string_ends_with(char* str, char* suffix);
extern int string_starts_with(char* str, char* prefix);

/******************** array processing **************************/
#define GET_ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))
extern int array_max(int* array, size_t length);
extern int array_min(int* array, size_t length);

/************************* other  ******************************/
extern char random_char(char* str, size_t str_length);
extern int random_int(int min, int max);
extern void simple_free(void *__ptr);
extern void *simple_malloc(size_t size);
extern char *strdup_safe(const char *str);

#ifdef __cplusplus
}
#endif






#endif /*__CUTILS_H__*/