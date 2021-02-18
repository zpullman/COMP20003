#include <stdio.h>
#include <stdlib.h>
#define GRUDGECOUNT 5
#define NATIONS 8
#define PARTNERS 2
#define GROUPS NATIONS/PARTNERS

int main(int argc, char **argv){
    int grudges[GRUDGECOUNT][PARTNERS];
    int pairs[GROUPS][PARTNERS];
    int i, j;
    
    /* 
        Grudges are:
        3 and 4
        5 and 6
        1 and 3
        2 and 3
        3 and 6
        Where, for sanity, indices start from 0
    */
    
    grudges[0][0] = 3; grudges[0][1] = 4;
    grudges[1][0] = 5; grudges[1][1] = 6;
    grudges[2][0] = 1; grudges[2][1] = 3;
    grudges[3][0] = 2; grudges[3][1] = 3;
    grudges[4][0] = 3; grudges[4][1] = 6;
    
    /* Find pairs using some algorithm. */
    
    
    /* -------------------------------- */
    for(i = 0; i < GROUPS; i++){
        printf("Partners %d: ",i);
        for(j = 0; j < PARTNERS; j++){
            if(j != 0){
                printf(" and ");
            }
            printf("%d",pairs[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}