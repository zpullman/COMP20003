/* adjmatrix.h */
/* NOTE: this could be made a lot more robust, 
    but it's easier not to. */
#include <limits.h>
#define NOPATH INT_MAX/2
/* Allocates space for a size * size array
    and sets all values to the NOPATH value. */
int **newMatrix(int size);

/* Adds an edge between one given index and another. */
void addEdge(int **adjMatrix, int src, int dst, int weight);

/* Frees a matrix allocated with the newMatrix function. */
void freeMatrix(int **matrix, int size);

/* adjmatrix.c */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
/* #include "adjmatrix.h" */

int **newMatrix(int size){
    int **retMatrix;
    int i, j;
    retMatrix = (int **) malloc(sizeof(int *)*size);
    assert(retMatrix);
    for(i = 0; i < size; i++){
        retMatrix[i] = (int *) malloc(sizeof(int)*size);
        assert(retMatrix[i]);
        for(j = 0; j < size; j++){
            retMatrix[i][j] = NOPATH;
        }
    }
    return retMatrix;
}

void addEdge(int **adjMatrix, int src, int dst, int weight){
    adjMatrix[src][dst] = weight;
}

void freeMatrix(int **matrix, int size){
    if(!matrix){
        return;
    }
    int i;
    for(i = 0; i < size; i++){
        free(matrix[i]);
    }
    free(matrix);
}

/* fw.h */
/* Finds shortest paths between all nodes and all other nodes.
    Allocates space for path matrix and stores this in the space pointed
    to by pathMatrix. 
    size is the dimension of the matrix. */
void fw(int **adjMatrix, int ***pathMatrix, int size);

/* Prints the path from the source node given to the destination node
    given using the given path matrix. The path printed is new line 
    terminated. */
void printPath(int **pathMatrix, int src, int dest);

/* Frees a path matrix and all the values within it. */
void freePathMatrix(int **pathMatrix, int size);

/* fw.c */
void fw(int **adjMatrix, int ***pathMatrix, int size){
    /* FILL IN */
}

void printPath(int **pathMatrix, int src, int dest){
    /* FILL IN */
}

void freePathMatrix(int **pathMatrix, int size){
    /* Fill in */
}

/* main.c */
#include <stdio.h>
#include <stdlib.h>
/* #include "adjmatrix.h" */
/* #include "fw.h" */

#define SIZE 10

int main(int argc, char **argv){
    
    int **graph = newMatrix(SIZE);
    int **pathMatrix = NULL;
    int i, j;
    
    addEdge(graph, 0, 4, 2);
    addEdge(graph, 1, 2, 2);
    addEdge(graph, 1, 3, 5);
    addEdge(graph, 1, 4, 10);
    addEdge(graph, 2, 3, 2);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 3, 5, 6);
    addEdge(graph, 4, 5, 2);
    addEdge(graph, 6, 7, 5);
    addEdge(graph, 6, 8, 9);
    addEdge(graph, 7, 8, 6);
    addEdge(graph, 8, 9, 3);
    
    printf("Running Floyd-Warshall\n");
    fw(graph, &pathMatrix, SIZE);
    
    printf("Shortest path distances:\n");
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            if(graph[i][j] == NOPATH){
                printf("N/A ");
            } else {
                printf("%3d ",graph[i][j]);
            }
        }
        printf("\n");
    }
    for(i = 0; i < SIZE; i++){
        printf("Shortest path from %d:\n",i);
        for(j = 0; j < SIZE; j++){
            printf("to %d: ",j);
            printPath(pathMatrix, i, j);
        }
    }
    
    freeMatrix(graph, SIZE);
    freePathMatrix(pathMatrix, SIZE);
    
    return 0;
}
