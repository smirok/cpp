#include "str.h"
#include "test_str.h"
#include <assert.h>
#include <string.h>
#include <stddef.h>

void test_mystrcpy()
{
	char ForCopy[10];
	char CurrentStr[10] = "fufufu";
	const char * OurAnswer = my_strcpy(ForCopy,CurrentStr);
	assert(strcmp(OurAnswer,CurrentStr) == 0);
}

void test_mystrlen()
{
	char TestStringNotEmpty[]="eshkereee";
	assert(my_strlen(TestStringNotEmpty) == 9);
	char TestStringEmpty[]=  ""; 
	assert(my_strlen(TestStringEmpty) == 0);
}

void test_mystrcat()
{
	char FirstStr[15]="uznali";
	char SecondStr[15]="soglasni";
	const char * OurAnswer = my_strcat(FirstStr,SecondStr);
	char TrueAnswer[30] = "uznalisoglasni";
	assert(strcmp(TrueAnswer,OurAnswer)==0);
}

void test_mystrcmp()
{
	char Test1[40]="big";
	char Test2[40]="small";
	char Test3[40]="small";
	assert(my_strcmp(Test3,Test2)==0);
	assert(my_strcmp(Test1,Test2)<0);
}
