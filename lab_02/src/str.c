#include <stddef.h>
#include "str.h"

char *my_strcpy(char * restrict CopyRes,const char * restrict CopyString)
{
	char * restrict CurrCopy = CopyRes;
	const char * restrict TestS = CopyString;
	
	while (*TestS != '\0') {
		*CurrCopy = *TestS;
		CurrCopy++;
		TestS++;
	}

	*CurrCopy = '\0';

	return CopyRes;
}

char *my_strcat(char * restrict FirstS,const char * restrict SecondS)
{
	char * restrict TestS1 = FirstS;
	const char * restrict TestS2 = SecondS;

	while(*TestS1){
		++TestS1;
	}

	while (*TestS2){
		*TestS1 = *TestS2;
		++TestS1;
		++TestS2;
	}

	*TestS1 = '\0';

	return FirstS;
}

int my_strcmp(const char *restrict FirstS,const char *restrict SecondS)
{
	while(*SecondS== *FirstS && *FirstS != '\0' && *SecondS != '\0'){
		FirstS++;
		SecondS++;
	}

	return *FirstS - *SecondS;
}

size_t my_strlen(const char *StringForLen)
{
	const char * Delta = StringForLen;

	while (*Delta != '\0')
		Delta++;

	return Delta - StringForLen;	
}
