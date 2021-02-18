#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_LEN    (512)

struct node_s {

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

struct node_s *p_left;
struct node_s *p_right;
};

typedef struct node_s node_t;

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

node_t * insert_data( char * key, node_t* parent, compare cmpre) {
  printf("insert thing going");

  char ** pp = NULL;
  //split line into elements and insert into pointer pointer to put data in
  pp = strsplit( key, "," );
  printf("\n%s\n", pp[1]);
  int res = cmpre(pp[1], parent->name);
  printf("%i\n\n", res);

  if(parent == NULL) {
    parent = (node_t *)malloc(sizeof(node_t));
    if(parent == NULL){
      printf("failed to allocate memory");
    }
      printf("in the if for insert");
      parent -> p_left = NULL;
      parent -> p_right = NULL;
      parent -> ID = strdup(pp[0]);
      parent -> name = strdup(pp[1]);
      parent -> sex = strdup(pp[2]);
      parent -> age = strdup(pp[3]);
      parent -> height = strdup(pp[4]);
      parent -> weight = strdup(pp[5]);
      parent -> team = strdup(pp[6]);
      parent -> noc = strdup(pp[7]);
      parent -> games = strdup(pp[8]);
      parent -> year = strdup(pp[9]);
      parent -> season = strdup(pp[10]);
      parent -> city = strdup(pp[11]);
      parent -> sport = strdup(pp[12]);
      parent -> event = strdup(pp[13]);
      parent -> medal = strdup(pp[14]);

      printf("key: %s    inserted:  %s\n", pp[1], parent->name);
      strsplitfree( pp );
      return parent;
  } else if (res <= 0) {
      parent->p_left = insert_data(key, parent->p_left, cmpre);
      printf("went to elseif\n");
  } else if (res > 0) {
      parent->p_right = insert_data(key, parent->p_right, cmpre);
      printf("went to else\n");
  } else {
    printf("not working\n");
  }
}
//compares value of the new node against the previous node
int cmpStr(const char *a, const char *b) {

    return (strcasecmp (a, b)-1);     // string comparison case insensitive
}

void print_data(node_t * node) {
  node_t ** pnode = &node;
  printf("\n %s ||", (*pnode)->ID);
  printf(" %s ||", node->name);
  printf(" %s ||", node->sex);
  printf(" %s ||", node->age);
  printf(" %s ||", node->height);
  printf(" %s ||", node->weight);
  printf(" %s ||", node->team);
  printf(" %s ||", node->noc);
  printf(" %s ||", node->games);
  printf(" %s ||", node->year);
  printf(" %s ||", node->season);
  printf(" %s ||", node->city);
  printf(" %s ||", node->sport);
  printf(" %s ||", node->event);
  printf(" %s\n", node->medal);
}

void search(char* key, node_t * node, compare cmpre) {

  node_t ** ptrsearch = &node;

  if (*ptrsearch){
    int res = cmpre(key, (*ptrsearch)->name);
    printf("%s\n", (*ptrsearch)->name);

    if  (res == 0) {
      print_data(*ptrsearch);
    } else if (res < 0) {
      search(key, &((*ptrsearch)->p_left), cmpre);
    } else if (res > 0) {
      search(key, &((*ptrsearch)->p_right), cmpre);
    } else {
      printf("key not found");
    }
  }
}
void in_order(node_t *root) {

  node_t ** ptrprinter = &root;

    if( *ptrprinter != NULL ) {
        in_order(&((*ptrprinter)->p_right));
        print_data(*ptrprinter);
        in_order(&((*ptrprinter)->p_left));

    }
}

int main( int argc, char * argv[] )
{
    char* buf = malloc(LINE_MAX_LEN + 1);
    if (buf == NULL) {
      printf("memory fail for buf");
    }

    node_t  * p_root = NULL;
    FILE * fp = NULL;

    //fp = fopen( argv[1], "r" );
    fp = fopen("C:\\Users\\61422\\Documents\\COMP20003\\assignment1\\test.csv", "r");

  //  if(fp == NULL) {
    //  printf("no file or file couldn't be read");
    //}

    while( fgets( buf, LINE_MAX_LEN + 1, fp ) != NULL )
    {
      if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n')) {
          buf[strlen (buf) - 1] = '\0';
        }
      printf("%s\n\n", buf);
      insert_data( buf, &p_root, (compare)cmpStr );
      printf("%s\n", p_root->name);
      printf("%s\n\n", buf);
      print_data(p_root);
    }
    print_data(&p_root);
    search("Iera Echebarra Fernndez", p_root, (compare)cmpStr);

    fclose(fp);

    return 0;
}
