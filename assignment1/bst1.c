#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_MAX_LEN    512
#define DEBUG 0
#define COUNT 0

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
typedef int (*compare)(const char *, const char *);

//splits string and gets ready for parsing
char ** strsplit(const char * src, const char * delim) {

    char * pbuf = NULL;
    char * ptok = NULL;
    int count = 0;
    int srclen = 0;
    char ** pparr = NULL;

    srclen = strlen( src );

    pbuf = (char*) malloc( srclen + 1 );

    if( !pbuf )
        return NULL;

    strcpy( pbuf, src );

    ptok = strtok( pbuf, delim );

    while( ptok )
    {
        pparr = (char**) realloc( pparr, (count+1) * sizeof(char*) );
        *(pparr + count) = strdup(ptok);

        count++;
        ptok = strtok( NULL, delim );
    }

    pparr = (char**) realloc( pparr, (count+1) * sizeof(char*) );
    *(pparr + count) = NULL;

    free(pbuf);

    return pparr;
}

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
  //  printf("%i\n", res);
  //  printf(" %s", (*insertlocation)->name);

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

      return parent;
  }

//compares value of the new node against the previous node
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

//    search for a specific key

struct node * search(struct node * root, const char * key, int count, compare cmp) {

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
            cursor = cursor->p_left;
          }

        }

        if ((cursor == NULL) && !found) {
          printf("%s NOT FOUND\n", key);
        }

          printf("%i\n", count);
          return cursor;
}


  /*
      recursively remove all nodes of the tree
  */
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

void printinorder(struct node * node) {
      if (node == NULL) {
          return;
      }
      printinorder(node->p_left);
      printf(" %s   ||", node->name);
      printinorder(node->p_right);
  }

int main( int argc, char * argv[] ) {

    char* buf = malloc(LINE_MAX_LEN + 1);
    struct node  * p_root = NULL;
    FILE * fp = NULL;

//  fp = fopen( argv[1], "r" );
  fp = fopen("C:\\Users\\61422\\Documents\\COMP20003\\assignment1\\test.txt", "r");
//  fp = fopen("C:\\Users\\61422\\Documents\\COMP20003\\assignment1\\athlete_events_filtered_alternative.csv", "r");
//  fp = fopen("C:\\Users\\61422\\Documents\\COMP20003\\assignment1\\athlete_events_filtered.csv", "r");
//  fp = fopen("C:\\Users\\61422\\Documents\\COMP20003\\assignment1\\athlete_events_filtered_alternative2.csv", "r");


  if(fp == NULL) {
    printf("no file or file couldn't be read");
    }

    while( fgets( buf, LINE_MAX_LEN + 1, fp ) != NULL )
    {
      if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n')) {
          buf[strlen (buf) - 1] = '\0';
        }
        p_root = insert_data( buf, p_root, (compare)cmpstr );
      //  printf("%s\n\n\n",buf );
      //  print_data(p_root);
    }

    search(p_root, "Otto Greter", COUNT, (compare)strcmp);
    fclose(fp);
    freetree(p_root);

    return 0;
}
