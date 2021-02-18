#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ATHLETES 20
#define MAX_STR_LEN 128
#define DEBUG 0

typedef struct athlete {
  //add extra space to make sure blank spaces don't overflow data
  // assume the 128 for name holds true

    int ID;
    char* name;
    char* sex;
    int age;
    int height;
    int weight;
    char* team;
    char* noc;
    char* games;
    int year;
    char* season;
    char* city;   /*Worlds longest name of town + 3*/

    char* sport;
    char* event;
    char* medal;

} athlete;

int main() {

//FILE *file = fopen("C:\\Users\\61422\\Documents\\COMP20003\\filereading\\test.csv", "r");
FILE *file = fopen("C:\\Users\\61422\\Documents\\COMP20003\\assignment1\\test.csv", "r");


if (file == NULL){
  printf("error empty or no file");
  return 0;
}

char* buf = malloc(90);
char* tmp;

if (buf == NULL) {
  printf("no memory for buf");
  return 0;
}

athlete *athletes = malloc(sizeof(athlete)*NUM_ATHLETES);

int i = 0;
while (fgets(buf, MAX_STR_LEN-1, file) != NULL)
{
    if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n')) {
        buf[strlen (buf) - 1] = '\0';
}

//printf("%s\n\n", buf);

    tmp = strtok(buf, ",");
    athletes[i].ID = atoi(tmp);
if (DEBUG) { printf("%s\n",tmp);}

    tmp = strtok(NULL, ",");
    athletes[i].name = tmp;
    if (DEBUG) { printf("%s\n",tmp);}

    tmp = strtok(NULL, ",");
    athletes[i].sex = tmp;
    if (DEBUG) { printf("%s\n",tmp);}

    tmp = strtok(NULL, ",");
    athletes[i].age = atoi(tmp);
    if (DEBUG) { printf("%s\n",tmp);}

    tmp = strtok(NULL, ",");
    athletes[i].height = atoi(tmp);
    if (DEBUG) { printf("%s\n",tmp);}

    tmp = strtok(NULL, ",");
    athletes[i].weight = atoi(tmp);
    if (DEBUG) { printf("%s\n",tmp);}

    tmp = strtok(NULL, ",");
    athletes[i].team = tmp;
    if (DEBUG) { printf("%s\n",tmp);}

    tmp = strtok(NULL, ",");
    athletes[i].noc = tmp;
    if (DEBUG) { printf("%s\n",tmp);}

    tmp = strtok(NULL, ",");
    athletes[i].games = tmp;
    if (DEBUG) { printf("%s\n",tmp);}

    tmp = strtok(NULL, ",");
    athletes[i].year = atoi(tmp);
    if (DEBUG) { printf("%s\n",tmp);}

    tmp = strtok(NULL, ",");
    athletes[i].season = tmp;
    if (DEBUG) { printf("%s\n",tmp);}

    tmp = strtok(NULL, ",");
    athletes[i].city = tmp;
    if (DEBUG) { printf("%s\n",tmp);}

    tmp = strtok(NULL, ",");
    athletes[i].sport = tmp;
    if (DEBUG) { printf("%s\n",tmp);}

    tmp = strtok(NULL, ",");
    athletes[i].event = tmp;
    if (DEBUG) { printf("%s\n",tmp);}

    tmp = strtok(NULL, ",");
    athletes[i].medal = tmp;
    if (DEBUG) { printf("%s\n",tmp);}

    //printf("%i %i %s %s\n",i, athletes[i].ID , athletes[i].name, athletes[i].season);
    printf("%i  %s %i\n\n", i, athletes[i].name, athletes[i].weight);
i++;

}

fclose(file);
free(athletes);
return 0;

}
