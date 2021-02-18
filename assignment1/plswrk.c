#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_LEN    (128 * 15)

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

char ** strsplit( const char * src, const char * delim )
{
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

void strsplitfree( char ** strlist )
{
    int i = 0;

    while( strlist[i])
        free( strlist[i++] );

    free( strlist );
}

node_t * insert_data( char * buf )
{
    char ** pp = NULL;
    node_t * node = NULL;

    //split line into elements and insert into pointer pointer to put data in
    pp = strsplit( buf, "," );

    //allocate memory
    node = (node_t*) malloc( sizeof(node_t) );

    node -> ID = strdup(pp[0]);
    node -> name = strdup(pp[1]);
    node -> sex = strdup(pp[2]);
    node -> age = strdup(pp[3]);
    node -> height = strdup(pp[4]);
    node -> weight = strdup(pp[5]);
    node -> team = strdup(pp[6]);
    node -> noc = strdup(pp[7]);
    node -> games = strdup(pp[8]);
    node -> year = strdup(pp[9]);
    node -> season = strdup(pp[10]);
    node -> city = strdup(pp[11]);
    node -> sport = strdup(pp[12]);
    node -> event = strdup(pp[13]);
    node -> medal = strdup(pp[14]);

    strsplitfree( pp );

return node;
}

void print_data(node_t * node) {
  printf("\n %s ||", node->ID);
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

int main( int argc, char * argv[] )
{
    char* buf = malloc(LINE_MAX_LEN + 1);
    node_t  * node = NULL;
    FILE * fp = NULL;

    //fp = fopen( argv[1], "r" );
    fp = fopen("C:\\Users\\61422\\Documents\\COMP20003\\assignment1\\test.csv", "r");

  //  if(fp == NULL) {
    //  printf("no file or file couldn't be read");
    //}

    while( fgets( buf, LINE_MAX_LEN, fp ) != NULL )
    {
      if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n')) {
          buf[strlen (buf) - 1] = '\0';
        }


      node = insert_data( buf );
      print_data(node);
    }

    fclose(fp);

    return 0;
}
