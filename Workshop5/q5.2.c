/* hashT.h */
struct hashTable;

/* Insert the given key into the given hash table comparing the
    hash of the given key to the keys in the table already,
    placing it at the next free spot after where it should
    have otherwise been placed. If used >= size, the function 
    returns, doing nothing. */
void insertLP(struct hashTable *table, int *key, void *value);

/* Calculates the interval of the given key using the equation
    (key % 5) + 1 and then calls insertDH with this value. */
void insertDH5(struct hashTable *table, int *key, void *value);

/* Insert the given key into the given hash table comparing the
    hash of the given key to the keys in the table already,
    trying to place it at the next interval hash2key distance away 
    from where it would otherwise have been placed,
    continuing this process until a free spot is found and then
    the value is placed in this location. If used >= size, 
    the function returns doing nothing. */
void insertDH(struct hashTable *table, int *key, void *value, int hash2key);

/* Allocates space for a hash table and assigns its hash, insert
    and print (for a single data item) functions. */
struct hashTable *create(int tableSize, int *(*hash)(void *), 
    void (*insert)(struct hashTable *, int *, void *), 
    void (*print)(void *));

/* 
    Insert the item in the hash table.
*/
void insert(struct hashTable *table, void *value);

/* Prints the given hash table. */
void printTable(struct hashTable *table);

/* hashT.c */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct hashTable {
    int size;
    int used;
    void **data;
    int *(*hash)(void *);
    void (*insert)(struct hashTable *, int *, void *);
    void (*print)(void *);
};

void insertLP(struct hashTable *table, int *key, void *value){
    /* Write this. NOTE: if you have already written insertDH,
        this is one line of code. */
        
}

void insertDH5(struct hashTable *table, int *key, void *value){
    /* Write code to calculate the interval from the key and 
        then call insertDH with this value. */
    
    insertDH(table, key, value, interval);
}

void insertDH(struct hashTable *table, int *key, void *value, int hash2key){
    /* Write this. */
    
    
    
    
}

struct hashTable *create(int tableSize, int (*hash)(void *), 
    void (*insert)(struct hashTable *, void *, void *), void (*print)(void *)){
    int i;
    struct hashTable *returnTable = (struct hashTable *) malloc(sizeof(struct hashTable));
    assert(returnTable);
    
    returnTable->size = tableSize;
    returnTable->used = 0;
    returnTable->hash = hash;
    returnTable->insert = insert;
    returnTable->print = print;
    returnTable->data = (void **) malloc(sizeof(void *)*tableSize);
    assert(returnTable->data);
    
    /* Set all elements to NULL, so we know which elements
        are used. */
    for(i = 0; i < tableSize; i++){
        (returnTable->data)[i] = NULL;
    }
    
    return returnTable;
}

void insert(struct hashTable *table, void *value){
    int key;
    key = table->hash(value);
    table->insert(table, key, value);
    free(key);
}

void printTable(struct hashTable *table){
    int i;
    printf("|");
    for(i = 0; i < table->size; i++){
        if(table->data[i]){
            table->print(table->data[i]);
        } else {
            printf(" ");
        }
        printf("|");
    }
    printf("\n");
}

/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* #include "hashT.h" */

#define TABLESIZE 13
#define INPUTSIZE 7

int *hashFunc(void *val){
    int *retVal = (int *) malloc(sizeof(int));
    assert(retVal);

    *retVal = *((int *)val) % TABLESIZE;

    printf("Hashing %d: %d\n",*((int *)val), *retVal);

    return retVal;
}

void print(void *val){
    if(val){
        printf("%d",*((int *) val));
    }
}

int main(int argc, char **argv){
    
    int inputs[INPUTSIZE] = {14, 30, 17, 55, 31, 29, 16};
    
    struct hashTable *DH5Table;
    struct hashTable *LPTable;
    int i;
    
    LPTable = create(TABLESIZE, &hashFunc, &insertLP, &print);
    printf("Created Linear Probing hash table of size 13\n");
    printTable(LPTable);
    
    for(i = 0; i < INPUTSIZE; i++){
        printf("Inserting %d into Linear Probing hash table\n",inputs[i]);
        insert(LPTable, &(inputs[i]));
        printTable(LPTable);
    }
    printf("Finished inserting items into Linear Probing hash table\n\n");
    
    DH5Table = create(TABLESIZE, &hashFunc, &insertDH5, &print);
    printf("Created Double Hashing table of size 13 using hash2(x) = (key %% 5) + 1\n");
    printTable(DH5Table);
    
    for(i = 0; i < INPUTSIZE; i++){
        printf("Inserting %d into Double Hashing hash table\n",inputs[i]);
        insert(DH5Table, &(inputs[i]));
        printTable(DH5Table);
    }
    printf("Finished inserting items into Double Hashing hash table\n");
    
    return 0;
}
