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

/* main.c */
#include <stdio.h>
#include <stdlib.h>
/* #include "adjmatrix.h" */

#define SIZE 10

int main(int argc, char **argv){
    
    int **graph = newMatrix(SIZE);
    int **pathMatrix = NULL;
    int home        = 0;
    int firstPoint  = 1;
    int secondPoint = 6;
    int thirdPoint  = 9;
    int i, j, k;
    
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
    
    /* Add reversed edges. */
    addEdge(graph, 4, 0, 2);
    addEdge(graph, 2, 1, 2);
    addEdge(graph, 3, 1, 5);
    addEdge(graph, 4, 1, 10);
    addEdge(graph, 3, 2, 2);
    addEdge(graph, 4, 3, 2);
    addEdge(graph, 5, 3, 6);
    addEdge(graph, 5, 4, 2);
    addEdge(graph, 7, 6, 5);
    addEdge(graph, 8, 6, 9);
    addEdge(graph, 8, 7, 6);
    addEdge(graph, 9, 8, 3);
    
    /* 
        Find the ordering of points that
        gives the maximum distance using the
        shortest paths between each sequential
        point.
    */
    
    
    printf("The maximum ordering is %d (home) to #%d to #%d to #%d and back to %d\n",
        home, firstPoint, secondPoint, thirdPoint, home);
    
    freeMatrix(graph,SIZE);
    
    return 0;
}