#ifndef COMMON_STRING_H
#define COMMON_STIRNG_H

#include <common/generic.h>


// STRING FUNCTIONS (similiar to the string.h C standard library)

int strcmp(const char *s1, const char *s2);
char *strcat(char *dest, const char *src);
char *strcpy(char *dest, const char *src);
size_t strlen(const char * str);
char* substr(char* src, size_t start, size_t len);



#endif