/* pqueue.h */
struct pqueue;

/* Creates an empty priority queue. */
struct pqueue *makeQueue();

/* Adds an item to a priority queue. */
void enqueue(struct pqueue *queue, int priority, void *data);

/* Takes the highest priority item from the queue. */
void *dequeue(struct pqueue *queue);

/* Updates the position of the given data item. 
    Note: if you were writing this generally, you
    might like to include a priority data update 
    function in your pqueue creation (like the
    hash table exercise) that allows you to read
    and update priority information and set and
    retrieve heap position information from
    an auxillary data structure (there's a lot
    of options here which are all fairly reasonable
    choices).
    For now, presume this does nothing (or make it 
    read through the array and update priorities,
    it depends on your dequeue implementation). */
void update(struct pqueue *queue, int index);

/* Returns 1 if the queue is empty, 0 otherwise. */
int empty(struct pqueue *queue);

/* Frees all memory allocated by the queue given. */
void freeQueue(struct pqueue *queue);
    
/* pqueue.c */
#include <stdlib.h>
#include <assert.h>
/* #include "pqueue.h" */
struct pqueue {
    /* FILL IN THIS PART */

};

struct pqueue *makeQueue(){
    /* Write this */
    
    
    return NULL;
}

void enqueue(struct pqueue *queue, int priority, void *data){
    /* Write this */
    
    
    
}

void *dequeue(struct pqueue *queue){
    /* Write this */
    
    return NULL;
}

void update(struct pqueue *queue, int index){
    /* Do whatever is appropriate. */
    return;
}

int empty(struct pqueue *queue){
    /* Write this. */
    return 0;
}

void freeQueue(struct pqueue *queue){
    
}

/* main.c */
#include <stdio.h>
#include <stdlib.h>
/* #include "pqueue.h" */
#define SIZE 10
#define ARBITRARYTAKE 3

int main(int argc, char **argv){
    int inputs[SIZE] = {7, 1, 3, 5, 6, 8, 4, 2, 9, 11};
    int i;
    
    struct pqueue *queue = makeQueue();
    
    printf("Adding all items to priority queue\n");
    for(i = 0; i < SIZE; i++){
        printf("%d ",inputs[i]);
        enqueue(queue, inputs[i], &(inputs[i]));
    }
    printf("\n");
    if(empty(queue)){
        printf("ERROR: Queue empty after all items added\n");
    }
    
    printf("Removing first three items from priority queue\n");
    for(i = 0; i < ARBITRARYTAKE; i++){
        printf("%d ",*(int *) (dequeue(queue)));
    }
    printf("\n");
    
    printf("Updating priority 11 item to 1\n");
    inputs[SIZE - 1] = 1;
    /* Normally you'd find this information from somewhere that
        the priority queue will update, but as the update function
        doesn't do anything anything with this information, that
        doesn't really matter. */
    update(queue, SIZE - ARBITRARYTAKE - 1);
    printf("Taking rest of items from priority queue.\n");
    for(i = 0; i < SIZE - ARBITRARYTAKE; i++){
        if(!empty(queue)){
            printf("%d ",*(int *) (dequeue(queue)));
        }
    }
    printf("\n");
    
    if(! empty(queue)){
        printf("ERROR: Queue not empty after all items dequeued\n");
    }
    
    freeQueue(queue);
    
    return 0;
}
