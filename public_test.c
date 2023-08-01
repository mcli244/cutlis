/*
 * @Author: lixiangjun.michael@foxmial.com
 * @Date: 2023-07-06 09:58:41
 * @FilePath: public_test.c
 * @Description: Description
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "cutils.h"

int main(int argc, char **argv)
{
    char *str = NULL;

    str = cutil_stringFormat("This is test %d %s %f", 123, "string", 3.14);
    printf("string_format:[%s]\n", str);
    cutil_simpleFree(str);

    str = cutil_stringRepeat("Hello World ", 3);
    printf("%s\n", str);
    cutil_simpleFree(str);

    char* test_arr[] = {"Hello", "Hola", "Bonjour"};
    char* test_str = cutil_stringJoin(test_arr, ", ", CUTIL_ARRAY_LEN(test_arr));
    printf("%s\n", test_str);
    cutil_simpleFree(test_str);

    char *test_arr1[] = {"Hello", "Hola", "Bonjour"};
    char *test_str1 = cutil_stringJoin(test_arr1, NULL, CUTIL_ARRAY_LEN(test_arr1));
    printf("%s\n", test_str1);
    cutil_simpleFree(test_str1);

    char* test_str2 = "Hello World";
    int ends = cutil_stringEndsWith(test_str2, "World");
    printf("%d\n", ends);

    char* test_str3 = "/home/workspace/exDisk_1/test/cutils/test.txt";
    ends = cutil_stringEndsWith(test_str3, "txt");
    printf("%d\n", ends);

    char* test_str4 = "AppPkg_8eb93bf502414fc7ae7d4a3a6a1b316c_2.0.0.zip";
    ends = cutil_stringStartsWith(test_str4, "AppPkg");
    printf("%d\n", ends);

    int test_array[]={
            9,4,7,2,0,
            1,7,11,22,99
            };
    printf("test_array size:%ld max:%d min:%d\n", 
        CUTIL_ARRAY_LEN(test_array), 
        cutil_arrayMax(test_array, CUTIL_ARRAY_LEN(test_array)), 
        cutil_arrayMin(test_array, CUTIL_ARRAY_LEN(test_array)));

    char *random_testchar = "Hello World";
    char rand = cutil_randomChar(random_testchar, strlen(random_testchar));
    printf("%c\n", rand);

    // base on time
    printf("random_int:%d\n", cutil_randomInt(0, 100));
    // sleep(1);
    // printf("random_int:%d\n", cutil_randomInt(0, 100));
    
    char buf[100];

    cutil_stringGetSize(123, STRING_UNITS_2, buf, sizeof(buf));
    printf("buf[%s]\n", buf);

    cutil_stringGetSize(123456789, STRING_UNITS_2, buf, sizeof(buf));
    printf("buf[%s]\n", buf);

    cutil_stringGetSize(0xFFFFFFFF, STRING_UNITS_2, buf, sizeof(buf));
    printf("buf[%s]\n", buf);

    cutil_stringGetSize(0xFFFFFFFF, STRING_UNITS_10, buf, sizeof(buf));
    printf("buf[%s]\n", buf);

    cutil_stringGetSize(0xFFFFFFFFFFFFFFFF, STRING_UNITS_2, buf, sizeof(buf));
    printf("buf[%s]\n", buf);

    cutil_stringGetSize(0xFFFFFFFFFFFFFFFF, STRING_UNITS_10, buf, sizeof(buf));
    printf("buf[%s]\n", buf);
    
    uint8_t dat[256];
    for(int i=0; i<sizeof(dat); i++)
        dat[i] = i;
        
    cutils_printHexDumpBytes("this is prefix ", DUMP_PREFIX_NONE, dat, sizeof(dat));
    cutils_printHexDumpBytes("this is prefix ", DUMP_PREFIX_ADDRESS, dat, sizeof(dat));
    cutils_printHexDumpBytes("this is prefix ", DUMP_PREFIX_OFFSET, dat, sizeof(dat));

    int ret = -1;
    long fileSize = 0;
    

    char *testFile = "../../test.txt";
    ret = cutil_fwriteAll(testFile, "This is a test file", strlen("This is a test file"));
    printf("file_write ret:%d\n", ret);

    ret = cutil_getFileSize(testFile, &fileSize);
    printf("file_size:%ld ret:%d\n", fileSize, ret);

    str = cutil_freadAll(testFile);
    printf("file_read:[%s]\n", str);
    cutil_simpleFree(str);

    char *FileAbsolutePath = NULL;
    if(cutil_isExist(testFile))
    {
        FileAbsolutePath = cutil_getFileAbsolutePath(testFile);
        printf("cutil_getSuffix(FileAbsolutePath):[%s]\n", cutil_getSuffix(FileAbsolutePath));
        printf("cutil_rmSuffix(FileAbsolutePath):[%s]\n", cutil_rmSuffix(FileAbsolutePath));
        cutil_simpleFree(FileAbsolutePath);
    }

    return 0;
}