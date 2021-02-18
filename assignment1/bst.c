#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define ATH_PROPS 15
#define ATH_NAME 2

//struct for node
struct node {
    char *value;
    struct node *p_left;
    struct node *p_right;
};

//use typedef to make calling the compare function easier
typedef int (*compare)(const char *, const char *);

//inserts elements into the tree
void insert(char* key, struct node** child, compare cmpre)
{
    int res;
    if( *child == NULL ) {
        *child = (struct node*) malloc( sizeof( struct node ) );
        (*child)->value = malloc( strlen (key) +1 );     // memory for key
        strcpy ((*child)->value, key);                   // copy the key
        (*child)->p_left = NULL;
        (*child)->p_right = NULL;
        //printf(  "\nnew node for %s" , key);
    } else {
        res = cmpre (key, (*child)->value);
        if( res < 0)
            insert( key, &(*child)->p_left, cmpre);
        else if( res > 0)
            insert( key, &(*child)->p_right, cmpre);
        else   // key already exists
            //need this for stage 2 point send left for now
            insert( key, &(*child)->p_left, cmpre);
    }
}

//compares value of the new node against the previous node
int cmpStr(const char *a, const char *b)
{
    return (strcasecmp (a, b));     // string comparison case insensitive
}

//the in order recursive function to print out the tree inorder
void in_order(struct node *root)
{
    if( root != NULL ) {
        in_order(root->p_left);
        printf("   %s\n", root->value);
        in_order(root->p_right);
    }
}

//searches elements in the tree
void search(char* key, struct node* child, compare cmpre)
{
    int res;
    if( child != NULL ) {
        res = cmpre(key, child->value);
        if( res < 0) {
            search(key, child->p_left, cmpre);
          } else if( res > 0) {
            search(key, child->p_right, cmpre);
          } else if (res == 0) {
            printf("\n'%s' found!\n", key);
            search(key, child->p_left, cmpre);
          }
    }
    else printf("\nNot in tree\n");
    return;
}

//free the tree for free
void delete_tree(struct node** child)
{
    if( *child != NULL ) {
        delete_tree(&(*child)->p_left);
        delete_tree(&(*child)->p_right);
        free( (*child)->value );         // free the key
        free( (*child) );
    }
}

int main() {
  struct node *p_root = NULL;
//  char* value;

//test thre code
// insert (root, value);
  insert("Sam", &p_root, (compare)cmpStr);
  insert("Zac",&p_root, (compare)cmpStr);
  insert("a", &p_root, (compare)cmpStr);
  insert("Craig",&p_root, (compare)cmpStr);
  insert("Craig",&p_root, (compare)cmpStr);
  insert("Alex", &p_root, (compare)cmpStr);
  insert("Sue", &p_root, (compare)cmpStr);
  insert("Zac",&p_root, (compare)cmpStr);
  insert("Chris", &p_root, (compare)cmpStr);
  insert("A", &p_root, (compare)cmpStr);
  insert("Craig",&p_root, (compare)cmpStr);
  insert("Zac",&p_root, (compare)cmpStr);

  search("Craig", p_root, (compare)cmpStr);
  search("Zac", p_root, (compare)cmpStr);


  in_order(p_root);
}
