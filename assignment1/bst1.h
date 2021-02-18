#ifndef BST1
#define BST1

#define LINE_MAX_LEN    512
#define MAX_DATA 128
#define DEBUG 0
#define COUNT 0

struct node;
typedef int (*compare)(const char *, const char *);

char ** strsplit(const char * src, const char * delim);
void strsplitfree(char ** str);
struct node * insert_data( char * key, struct node* parent, compare cmp);
int cmpstr(char const *a, char const *b);
//void print_data(struct node * node, char filename[]);
struct node * search(struct node * root, const char * key, int count, compare cmp, char filename[]);
void freetree(struct node * root);
void writeToFile(struct node * root, char fileName[]);

#endif
