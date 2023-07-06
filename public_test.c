#include <stdio.h>
#include <unistd.h>
#include "cutils.h"

int main(int argc, char **argv)
{
    int ret = -1;
    long fileSize = 0;
    char *str = NULL;

    ret = file_write("./test.txt", "This is a test file", strlen("This is a test file"));
    printf("file_write ret:%d\n", ret);

    ret = file_size("./test.txt", &fileSize);
    printf("file_size:%ld ret:%d\n", fileSize, ret);

    str = file_read("./test.txt");
    printf("file_read:[%s]\n", str);
    simple_free(str);

    str = string_format("This is test %d %s %f", 123, "string", 3.14);
    printf("string_format:[%s]\n", str);
    simple_free(str);

    str = string_repeat("Hello World ", 3);
    printf("%s\n", str);
    simple_free(str);

    char* test_arr[] = {"Hello", "Hola", "Bonjour"};
    char* test_str = string_join(test_arr, ", ", GET_ARRAY_LEN(test_arr));
    printf("%s\n", test_str);
    free(test_str);

    char *test_arr1[] = {"Hello", "Hola", "Bonjour"};
    char *test_str1 = string_join(test_arr1, NULL, GET_ARRAY_LEN(test_arr1));
    printf("%s\n", test_str1);
    free(test_str1);

    char* test_str2 = "Hello World";
    int ends = string_ends_with(test_str2, "World");
    printf("%d\n", ends);

    char* test_str3 = "/home/workspace/exDisk_1/test/cutils/test.txt";
    ends = string_ends_with(test_str3, "txt");
    printf("%d\n", ends);

    char* test_str4 = "AppPkg_8eb93bf502414fc7ae7d4a3a6a1b316c_2.0.0.zip";
    ends = string_starts_with(test_str4, "AppPkg");
    printf("%d\n", ends);

    int test_array[]={
            9,4,7,2,0,
            1,7,11,22,99
            };
    printf("test_array size:%ld max:%d min:%d\n", 
        GET_ARRAY_LEN(test_array), 
        array_max(test_array, GET_ARRAY_LEN(test_array)), 
        array_min(test_array, GET_ARRAY_LEN(test_array)));

    char *random_testchar = "Hello World";
    char rand = random_char(random_testchar, strlen(random_testchar));
    printf("%c\n", rand);

    // base on time
    printf("random_int:%d\n", random_int(0, 100));
    sleep(1);
    printf("random_int:%d\n", random_int(0, 100));
    

    return 0;
}