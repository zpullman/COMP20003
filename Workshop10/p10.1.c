/* digraph.h */
struct digraph;

/* Return type for edges. 
    Linked list concrete data type. */
struct weightedEdge {
    int destIndex;
    int weight;
    struct weightedEdge *next;
};

/* Create a new weighted directed graph containing no edges. */
struct digraph *newDigraph();

/* 
    Add an edge from the source to the destination with the given weight
    to the given graph.
*/
void addEdge(struct digraph *graph, int source, int destination, int weight);

/*
    Returns a list of edges which occur in the given graph, will be in order.
    Nodes without an edge to or from them will not be returned. This list should
    be freed by the caller. Value sent into size will be set to the size of the
    returned list. The final value in the returned list will also be given a value
    of graph->lowIndex - 1, so can be used as a sentinel (the size will exclude 
    this value).
*/
int *getNodes(struct digraph *graph, int *size);

/*
    Returns the list of edges from a particular node in the graph as indices
    into the provided list. (ie a graph with nodes -1, 3, 4 and a list [-1,3,4],
    the edge list [[-1,50],[3,30],[4,20]] will be transformed to 
    [[0,50],[4,30],[5,20]], this is for the purposes of abstracting out some of
    the internal behaviour of the digraph).
    The source index should be the value at the index in the nodeList given (so 0
    would be the index -1).
    The returned array is allocated as a list of weighted edges. This should be
    freed by the calling function.
    The original list is expected to obey the same constraints as that in the getNodes
    function.
*/
struct weightedEdge *getAdjacent(struct digraph *graph, int *nodeList, int sourceIndex);

/*
    Converts a given index to an index in the given node list (linear search). Could be
    binary search, but keeping it simple it should still be fast enough in this case.
*/
int convertIndex(int *list, int originalIndex);

/*
    Frees all the memory used by a particular graph.
*/
void freeDigraph(struct digraph *graph);

/* digraph.c */
/* #include "digraph.h" */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct digraph{
    int lowIndex;
    int highIndex;
    struct weightedEdge **adjacencyList;
    int allocated;
    int used;
};

struct digraph *newDigraph(){
    struct digraph *retDigraph = (struct digraph *) malloc(sizeof(struct digraph));
    assert(retDigraph);
    
    /* Don't initialise until we have at least one edge so we don't go over-allocate. */
    retDigraph->adjacencyList = NULL;
    retDigraph->allocated = 0;
    retDigraph->used = 0;
    
    return retDigraph;
}

void addEdge(struct digraph *graph, int source, int destination, int weight){
    int initialSize;
    int newLow;
    int newHigh;
    int i;
    struct weightedEdge *newEdge;
    if(! graph->allocated){
        initialSize = source - destination;
        if(initialSize < 0){
            initialSize = -initialSize;
        }
        /* Assume initialSize positive now, theoretically it may not be, but
            we needn't worry about that for now. */
        initialSize = initialSize + 1;
        graph->adjacencyList = (struct weightedEdge **) 
            malloc(sizeof(struct weightedEdge *)*initialSize);
        assert(graph->adjacencyList);
        graph->allocated = initialSize;
        /* Initialise edge list. */
        for(i = 0; i < initialSize; i++){
            (graph->adjacencyList)[i] = NULL;
        }
        /* Initialise low and high indices. */
        if(source < destination){
            graph->lowIndex = source;
            graph->highIndex = destination;
        } else {
            graph->lowIndex = destination;
            graph->highIndex = source;
        }
        graph->used = initialSize;
    } else {
        /* Ensure we have space for the new edge */
        if(graph->lowIndex > source || graph->lowIndex > destination){
            if(source < destination){
                newLow = source;
            } else {
                newLow = destination;
            }
        } else {
            newLow = graph->lowIndex;
        }
        if(graph->highIndex < source || graph->highIndex < destination){
            if(source > destination){
                newHigh = source;
            } else {
                newHigh = destination;
            }
        } else {
            newHigh = graph->highIndex;
        }
        if(newHigh != graph->highIndex || newLow != graph->lowIndex){
            /* Wasn't space for edge in current adjacency graph, 
                realloc space, move all edge lists along. */
            graph->allocated = newHigh - newLow + 1;
            graph->adjacencyList = (struct weightedEdge **) 
                realloc(graph->adjacencyList, sizeof(struct weightedEdge *)*graph->allocated);
            assert(graph->adjacencyList);
            /* Move from end of list to start of list to ensure none are overwritten. */
            for(i = graph->highIndex - graph->lowIndex; i >= 0; i--){
                graph->adjacencyList[i - newLow + graph->lowIndex] = graph->adjacencyList[i];
            }
            /* Fill in new low values. */
            for(i = 0; i < (graph->lowIndex - newLow); i++){
                graph->adjacencyList[i] = NULL;
            }
            /* Fill in new high values. */
            for(i = graph->highIndex - newLow + 1; i < (newHigh - newLow + 1); i++){
                graph->adjacencyList[i] = NULL;
            }
            
            graph->lowIndex = newLow;
            graph->highIndex = newHigh;
            graph->used = graph->allocated;
        }
    }
    
    /* Add the edge to the relevant place [prepend the list]. */
    newEdge = (struct weightedEdge *) malloc(sizeof(struct weightedEdge));
    assert(newEdge);
    newEdge->destIndex = destination;
    newEdge->weight = weight;
    newEdge->next = graph->adjacencyList[source - graph->lowIndex];
    graph->adjacencyList[source - graph->lowIndex] = newEdge;
}

int *getNodes(struct digraph *graph, int *size){
    /* A list of active edges, edges will be flipped on as traversed, 
        the bits will then be counted and the exact amount of space needed
        will be allocated. */
    char *bitmask;
    int i, j;
    int count;
    int *returnList;
    struct weightedEdge *current;
    bitmask = (char *) malloc(sizeof(char)*graph->used);
    assert(bitmask);
    for(i = 0; i < graph->used; i++){
        /* This conversion is for clarity, '\0' would have done the trick
            too. */
        bitmask[i] = (char) 0;
    }
    /* Fill in all the bits from the adjacency list. */
    for(i = 0; i < graph->used; i++){
        if(graph->adjacencyList[i]){
            bitmask[i] = (char) 1;
            current = graph->adjacencyList[i];
            while(current){
                bitmask[current->destIndex - graph->lowIndex] = (char) 1;
                current = current->next;
            }
        }
    }
    
    count = 0;
    for(i = 0; i < graph->used; i++){
        if(bitmask[i]){
            count++;
        }
    }
    
    returnList = (int *) malloc(sizeof(int)*(count + 1));
    
    j = 0;
    for(i = 0; i < graph->used; i++){
        if(bitmask[i]){
            returnList[j] = i + graph->lowIndex;
            j++;
        }
    }
    /* Add sentinel value. */
    returnList[j] = graph->lowIndex - 1;
    
    if(size){
        *size = j;
    }
    
    free(bitmask);
    
    return returnList;
}

struct weightedEdge *getAdjacent(struct digraph *graph, int *nodeList, int sourceIndex){
    /* Find length of provided node list. */
    int length = 0;
    while(nodeList[length] >= graph->lowIndex){
        length++;
    }
    
    struct weightedEdge *current = NULL;
    struct weightedEdge *returnList = NULL;
    struct weightedEdge *currentGraph = NULL;
    
    currentGraph = graph->adjacencyList[nodeList[sourceIndex] - graph->lowIndex];
    if(currentGraph){
        while(currentGraph){
            /* Move current to its next value. */
            if(! current){
                returnList = (struct weightedEdge *) malloc(sizeof(struct weightedEdge));
                assert(returnList);
                current = returnList;
            } else {
                current->next = (struct weightedEdge *) malloc(sizeof(struct weightedEdge));
                assert(current->next);
                current = current->next;
            }
            /* Append modified value. */
            current->next = NULL;
            current->weight = currentGraph->weight;
            current->destIndex = convertIndex(nodeList, currentGraph->destIndex);
            currentGraph = currentGraph->next;
        }
        return returnList;
    } else {
        /* No edges for source index. */
        return NULL;
    }
}

int convertIndex(int *list, int originalIndex){
    int i = 0;
    while(list[i] != originalIndex){
        i++;
    }
    return i;
}

void freeDigraph(struct digraph *graph){
    int i;
    struct weightedEdge *current;
    struct weightedEdge *next;
    if(!graph){
        return;
    }
    for(i = 0; i < graph->allocated; i++){
        if(graph->adjacencyList[i]){
            current = graph->adjacencyList[i];
            graph->adjacencyList[i] = NULL;
            while(current){
                next = current->next;
                free(current);
                current = next;
            }
        }
    }
    if(graph->allocated > 0){
        free(graph->adjacencyList);
    }
    free(graph);
}

/* dijkstra.h */
/* #include "digraph.h" */
#include <limits.h>
#define NOPATH INT_MAX
struct dijkstraRes {
    /* The node that all paths originate from, index is into
        indices list. */
    int sourceNode;
    /* The shortest paths from the source node to
        the destination.  */
    int *shortestPaths;
    /* The list of destination indices that the shortest
        paths correspond to. */
    int *indices;
    /* If you like, you can also add an item for 
        predecessors, but the actual path isn't
        being printed, so this isn't too important
        for the moment. Remember to update this in
        the free dijkstra struct function if you
        make memory-related changes to this struct. */
    
    /* The number of items in the index list. */
    int nodeCount;
};

/* Finds the shortest paths from the given source node to all
    other nodes in the graph (which have at least one edge in either
    direction) and returns a structure of these nodes. 
    Assumes that the given source node is actually in the graph. */
struct dijkstraRes *dijkstra(struct digraph *graph, int source);

/* 
    Prints all the shortest paths.
*/
void printDijkstra(struct dijkstraRes *res);

/*
    Frees a dijkstraRes struct and all the memory it
    is responsible for. (In the provided code, this is 
    assumed to be: .shortestPaths and .indices, as well
    as the struct sent).
*/
void freeDijkstraRes(struct dijkstraRes *res);

/* dijkstra.c */
/* #include "digraph.h" */
/* #include "dijkstra.h" */
#include <stdlib.h>
#include <stdio.h>
/* #include "pqueue.h" */
/* NOTE: If you didn't write pqueue.h & pqueue.c last week, consider doing
    so before this exercise. */

struct dijkstraRes *dijkstra(struct digraph *graph, int source){
    /* FILL IN HERE */
    
    
    
    
    
}

void printDijkstra(struct dijkstraRes *res){
    int i;
    printf("Shortest paths from %d\n", res->indices[res->sourceNode]);
    for(i = 0; i < res->nodeCount; i++){
        if ((res->shortestPaths[i]) == NOPATH){
            printf("to %d: NO PATH;\n", res->indices[i]);
        } else {
            printf("to %d: %d;\n", res->indices[i], res->shortestPaths[i]);
        }
    }
}

void freeDijkstraRes(struct dijkstraRes *res){
    if(! res){
        return;
    }
    if(res->shortestPaths){
        free(res->shortestPaths);
    }
    if(res->indices){
        free(res->indices);
    }
    free(res);
}

/* main.c */
#include <stdio.h>
#include <stdlib.h>
/* #include "digraph.h"*/
/* #include "dijkstra.h"*/
#define EDGES 6

int main(int argc, char **argv){
    struct digraph *graph = NULL;
    struct dijkstraRes *res = NULL;
    int src[EDGES];
    int dest[EDGES];
    int weight[EDGES];
    int i = 0;
    src[i] = 1; dest[i] = 2; weight[i] = 200; i++;
    src[i] = 1; dest[i] = 3; weight[i] = 100; i++;
    src[i] = 1; dest[i] = 4; weight[i] = 500; i++;
    src[i] = 2; dest[i] = 3; weight[i] = 150; i++;
    src[i] = 2; dest[i] = 4; weight[i] = 300; i++;
    src[i] = 4; dest[i] = 5; weight[i] = 100;
    
    graph = newDigraph();
    
    for(i = 0; i < EDGES; i++){
        addEdge(graph, src[i], dest[i], weight[i]);
    }
    
    printf("Running Dijkstra's Algorithm on graph\n");
    res = dijkstra(graph, 1);
    
    printf("Results:\n");
    printDijkstra(res);
    
    freeDigraph(graph);
    freeDijkstraRes(res);
    
    return 0;
}

