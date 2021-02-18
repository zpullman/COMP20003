#ifndef BST3
#define BST3

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
void print_data(struct node * node);
struct node * search(struct node * root, const char * key, int count, compare cmp);
void freetree(struct node * root);

#endif
