/*
 * @Author: lixiangjun.michael@foxmial.com
 * @Date: 2023-07-06 09:58:41
 * @FilePath: cutils.h
 * @Description: Description
 */
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

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const char hex_asc[];
#define hex_asc_lo(x)	hex_asc[((x) & 0x0f)]
#define hex_asc_hi(x)	hex_asc[((x) & 0xf0) >> 4]
#define max(x,y) (x > y ? x : y) 
#define min(x,y) (x < y ? x : y)

enum {
	DUMP_PREFIX_NONE,
	DUMP_PREFIX_ADDRESS,
	DUMP_PREFIX_OFFSET
};

/* Descriptions of the types of units to
 * print in */
enum string_size_units {
	STRING_UNITS_10,	/* use powers of 10^3 (standard SI) */
	STRING_UNITS_2,		/* use binary powers of 2^10 */
};


/*****************************************************************
Thanks for the following items
base on:
    https://github.com/thechampagne/utils.h.git
******************************************************************/

/******************** File operation *****************************/
extern char *cutil_freadAll(char *filename);
extern int cutil_fwriteAll(char *filename, char *content, int length);
extern int cutil_getFileSize(char *filename, long *out);
extern int cutil_getFileNameBySuffix(const char *directory, char *suffix, char *outFileName, int outPathBufSize);
extern int cutil_getFilePath(const char *inFileName, char *outPathBuf, int outPathBufSize);
extern bool cutil_isExist(const char *file);
extern const char* cutil_getSuffix(const char* file_name);
extern char* cutil_rmSuffix(char* file_name);
extern char* cutil_getFileAbsolutePath(const char *file);

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
extern int cutil_stringGetSize(uint64_t size, const enum string_size_units units,char *buf, int len);
extern void cutils_printHexDumpBytes(const char *prefix_str, int prefix_type, const void *buf, size_t len);
extern char* cutils_get_timestamp(void);
extern size_t cutils_get_ms(void);
extern size_t cutils_get_us(void);

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) ({			\
			const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
			(type *)( (char *)__mptr - offsetof(type,member) );})

#ifdef __cplusplus
}
#endif






#endif /*__CUTILS_H__*/