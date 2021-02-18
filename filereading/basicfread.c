#include <stdio.h>
#include <stdlib.h>

int main() {

FILE *file = fopen("C:\\Users\\61422\\Documents\\COMP20003\\filereading\\test.csv", "r");


while(!feof(file)){

printf("%c",fgetc(file));
}

fclose(file);
return 0;

}
