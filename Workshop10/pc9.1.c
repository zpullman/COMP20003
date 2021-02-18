#include <stdio.h>
#include <stdlib.h>
#define UNTRAVERSABLE '#'
#define START 'S'
#define CASTLE 'C'
#define XSIZE 6
#define YSIZE 6

/* Prints the path from the S symbol in the map
    to the C symbol which doesn't ever stop on
    any # symbols. The map given, of size xSize by
    ySize can be modified freely and needn't be
    kept in any way consistent with the original
    map. */
void printPath(char map[XSIZE][YSIZE + 1], int xSize, int ySize);

void printPath(char map[XSIZE][YSIZE + 1], int xSize, int ySize){
    int i, j;
    struct coordinatePair {
        int x;
        int y;
    };
    struct coordinatePair startPair = { .x = -1, .y = -1 };
    
    for(i = 0; i < XSIZE; i++){
        for(j = 0; j < YSIZE; j++){
            if(map[i][j] == START){
                startPair.x = i;
                startPair.y = j;
                /* Could also just let the loops
                    run, but may as well break
                    out of both. */
                break;
            }
        }
        if(startPair.x != -1){
            break;
        }
    }
    /* FILL IN */

}

int main(int argc, char **argv){
    char map[XSIZE][YSIZE + 1] = {
        "     C",
        "  #  #",
        "# # ##",
        "#  # #",
        "# #   ",
        " S    "
    };
    
    printPath(map, XSIZE, YSIZE);
    
    return 0;
}