#include <stdio.h>
#include <stdlib.h>

int main() {
FILE *fp;
fp = fopen("fileName", "a");
fprintf(fp, "write to file");
fclose(fp);
}
