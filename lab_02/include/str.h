#pragma once
#include <stddef.h>

char *my_strcpy(char * restrict CopyRes,const char * restrict CopyString);

char *my_strcat(char * restrict FirstS,const char * restrict SecondS);

int my_strcmp(const char * restrict FirstS,const char * restrict SecondS);

size_t my_strlen(const char * StringForLen);


