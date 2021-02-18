#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bst1.h"

//make the nodes for the bst
struct node {

char* ID;
char* name;
char* sex;
char* age;
char* height;
char* weight;
char* team;
char* noc;
char* games;
char* year;
char* season;
char* city;   /*Worlds longest name of town + 3*/
char* sport;
char* event;
char* medal;

struct node *p_left;
struct node *p_right;
};

//use typedef to make calling the compare function easier
//typedef int (*compare)(const char *, const char *);

//splits string and gets ready to put into nodes

char ** strsplit(const char * src, const char * delim) {

    char * pbuf = NULL;
    char * ptok = NULL;
    int count = 0;
    int srclen = 0;
    char ** ppar = NULL;

    srclen = strlen( src );

    pbuf = (char*) malloc( srclen + 1 );

    if( !pbuf )
        return NULL;

    strcpy( pbuf, src );

    ptok = strtok( pbuf, delim );

    while( ptok )
    {
        ppar = (char**) realloc( ppar, (count+1) * sizeof(char*) );
        *(ppar + count) = strdup(ptok);

        count++;
        ptok = strtok( NULL, delim );
    }

    ppar = (char**) realloc( ppar, (count+1) * sizeof(char*) );
    *(ppar + count) = NULL;

    free(pbuf);
    free(ptok);

    return ppar;
}

//free the temp variable
void strsplitfree(char ** str) {

    int i = 0;

    while(str[i])
        free(str[i++]);

    free(str);
}

//the insertion function
struct node * insert_data( char * key, struct node* parent, compare cmp) {

  struct node ** insertlocation = &parent;
  char ** pp = NULL;
  pp = strsplit( key, "," );
//split line into elements and insert into pointer pointer to put data in

  while (*insertlocation) {

    int res = cmp(pp[1], (*insertlocation)->name);

    if  (res <= 0) {
      insertlocation = &((*insertlocation)->p_left);
    } else  {
      insertlocation = &((*insertlocation)->p_right);
    }
  }

      *insertlocation = (struct node*) malloc( sizeof(struct node) );
      if (*insertlocation == NULL) {
        printf("couldn't allocate memory");
      }


    //  printf("%s\n", pp[1]);
      (*insertlocation) -> p_left = NULL;
      (*insertlocation) -> p_right = NULL;
      (*insertlocation) -> ID = strdup(pp[0]);
      (*insertlocation) -> name = strdup(pp[1]);
      (*insertlocation) -> sex = strdup(pp[2]);
      (*insertlocation) -> age = strdup(pp[3]);
      (*insertlocation) -> height = strdup(pp[4]);
      (*insertlocation) -> weight = strdup(pp[5]);
      (*insertlocation) -> team = strdup(pp[6]);
      (*insertlocation) -> noc = strdup(pp[7]);
      (*insertlocation) -> games = strdup(pp[8]);
      (*insertlocation) -> year = strdup(pp[9]);
      (*insertlocation) -> season = strdup(pp[10]);
      (*insertlocation) -> city = strdup(pp[11]);
      (*insertlocation) -> sport = strdup(pp[12]);
      (*insertlocation) -> event = strdup(pp[13]);
      (*insertlocation) -> medal = strdup(pp[14]);

      strsplitfree( pp );
      freetree(*insertlocation);
      return parent;
  }

//compares value of the new node against the previous node
//comparison should be case insensitive
int cmpstr(char const *a, char const *b) {
  while (*a) {
    int d = tolower(*a) - tolower(*b);
    if (d) {
        return d;
    }
    a++;
    b++;
  }
  return 0;
}

//prints the node values
/*
void print_data(struct node * node, char filename) {
  if (node != NULL) {
    FILE * ptrfw;
    ptrfw = fopen(filename, "a");

    fprintf(ptrfw, "%s --> ", node->name);
    fprintf(ptrfw, "ID %s ", node->ID);
    fprintf(ptrfw, "SEX %s ||", node->sex);
    fprintf(ptrfw, "AGE %s ||", node->age);
    fprintf(ptrfw, "HEIGHT %s ||", node->height);
    fprintf(ptrfw, "WEIGHT %s ||", node->weight);
    fprintf(ptrfw, "TEAM %s ||", node->team);
    fprintf(ptrfw, "NOC %s ||", node->noc);
    fprintf(ptrfw, "GAMES %s ||", node->games);
    fprintf(ptrfw, "YEAR %s ||", node->year);
    fprintf(ptrfw, "SEASON %s ||", node->season);
    fprintf(ptrfw, "CITY %s ||", node->city);
    fprintf(ptrfw, "SPORT %s ||", node->sport);
    fprintf(ptrfw, "EVENT %s ||", node->event);
    fprintf(ptrfw, "MEDAL %s ||\n", node->medal);

    fclose(ptrfw);
  }
}
*/

void writeToFile(struct node * root, char fileName[]) {
  FILE *fp;
  fp = fopen(fileName, "a");

  fprintf(fp , "%s --> ID: %s Sex: %s || Age: %s || Height: %s || Weight: %s || Team: %s || NOC: %s || Games: %s || Year: %s || Season: %s || City: %s || Sport: %s || Event: %s || Medal: %S ||\n",
          root->name, root->ID, root->sex, root->age, root->height, root->weight,
          root->team, root->noc, root->games, root->year, root->year,
          root->season, root->city, root->sport, root->event, root->medal);
}

void print_data(struct node * node) {
  if (node != NULL) {

    printf("\nNAME %s ||", node->name);
    printf("ID %s ||", node->ID);
    printf("SEX %s ||", node->sex);
    printf("AGE %s ||", node->age);
    printf("HEIGHT %s ||", node->height);
    printf("WEIGHT %s ||", node->weight);
    printf("TEAM %s ||", node->team);
    printf("NOC %s ||", node->noc);
    printf("GAMES %s ||", node->games);
    printf("YEAR %s ||", node->year);
    printf("SEASON %s ||", node->season);
    printf("CITY %s ||", node->city);
    printf("SPORT %s ||", node->sport);
    printf("EVENT %s ||", node->event);
    printf("MEDAL %s ||\n\n", node->medal);
  }
}

//search for the key i.e name
struct node * search(struct node * root, const char * key, int count, compare cmp, char filename[]) {

    if(root == NULL) {
    printf("null search node");
    }

    int res;
    int found = 0;
    struct node * cursor = root;

    while(cursor) {

        count++;
        res = cmp(key, cursor->name);
        if (res < 0) {
            cursor = cursor->p_left;
        } else if (res > 0) {
            cursor = cursor->p_right;

          //else found it but need to keep going check left has stuff to search
          // no need to check right as insert sends equality left
        } else {
           found = 1;
           print_data(cursor);
            writeToFile(cursor, *filename);

            cursor = cursor->p_left;
          }

        }

        if ((cursor == NULL) && !found) {
          fprintf(stdout,"%s --> NOT FOUND\n", key);
        }
          printf("%i\n", count);
          //fprintf(stdout, "%i\n", count);
          return cursor;
}

//free the nodes recursively
void freetree(struct node * root)
  {
      if(root != NULL)
      {
          freetree(root->p_left);
          freetree(root->p_right);
          free(root->ID);
          free(root->name);
          free(root->sex);
          free(root->age);
          free(root->height);
          free(root->weight);
          free(root->team);
          free(root->noc);
          free(root->games);
          free(root->year);
          free(root->season);
          free(root->city);
          free(root->sport);
          free(root->event);
          free(root->medal);
          free(root);
      }
  }

//actually run the file
int main( int argc, char * argv[] ) {

  char* buf = malloc(LINE_MAX_LEN + 1);
  struct node  * p_root = NULL;
  FILE * fp = NULL;

  char search_key[MAX_DATA+1];

  fp = fopen( argv[1], "r" );

  if(fp == NULL) {
    printf("no file or file couldn't be read");
    exit(1);
    }

  while( fgets( buf, LINE_MAX_LEN + 1, fp ) != NULL ) {

    if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n')) {
          buf[strlen (buf) - 1] = '\0';
        }

    p_root = insert_data( buf, p_root, (compare)cmpstr );
  }

  while (scanf(" %[^\n]", search_key) != EOF) {

  search(p_root, search_key, COUNT, (compare)strcmp, argv[2]);

}

FILE *fwp;
fwp = fopen("fileName", "a");
fprintf(fwp, "write to file in dictionary");
fclose(fwp);
fclose(fwp);
freetree(p_root);
free(buf);

  return 0;
}
