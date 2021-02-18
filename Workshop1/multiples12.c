#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
//%stdin: "1 2 3 4 5 6 7 "
printf("%s\n","1st number");
int A[6];
int i=0;
for ( i = 0; i < 6; i++) {

A[i] = scanf("%d\n", &A[i]);
printf("%s\n","next number");

}

printf("%d\n",A[0]);
printf("%d\n",A[2]);
printf("%d\n",A[5]);

return 0;

}
