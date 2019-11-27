#include "util.h"
#include "algorithm.h"
#include "io.h"
#include <stdio.h>
void foo(int);

int main(){
int a = doComputation(5, 7.0);
int b = 5;
max(a,b);
foo(2);
logDebug('!');
}
