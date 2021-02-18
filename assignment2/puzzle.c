#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>


/**
 * node data structure: containing state, g, f
 * you can extend it with more information if needed
 */
typedef struct node{
	int state[16];
	int g;
	int f;
} node_s;

/**
 * Global Variables
 */

// used to track the position of the blank in a state,
// so it doesn't have to be searched every time we check if an operator is applicable
// When we apply an operator, blank_pos is updated
// last move keeps track of last move set to 4 as no move is equal to 4
int blank_pos;
int last_move = 4;

// Initial node of the problem, next node
node_s initial_node;

// Statistics about the number of generated and expendad nodes
unsigned long generated;
unsigned long expanded;


/**
 * The id of the four available actions for moving the blank (empty slot). e.x.
 * Left: moves the blank to the left, etc.
 */

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define MOVE_SET 4
#define ELEMENTS 16
#define EDGE_LENGTH 4
#define UPPER_BOUND_OPTIMAL_SOLN  81

/*
 * Helper arrays for the applicable function
 * applicability of operators: 0 = left, 1 = right, 2 = up, 3 = down
 */
int ap_opLeft[]  = { 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1 };
int ap_opRight[]  = { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0 };
int ap_opUp[]  = { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int ap_opDown[]  = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 };
int *ap_ops[] = { ap_opLeft, ap_opRight, ap_opUp, ap_opDown };


/* print state */
void print_state( int* s )
{
	int i;

	for( i = 0; i < 16; i++ )
		printf( "%2d%c", s[i], ((i+1) % 4 == 0 ? '\n' : ' ') );
}

void printf_comma (long unsigned int n) {
    if (n < 0) {
        printf ("-");
        printf_comma (-n);
        return;
    }
    if (n < 1000) {
        printf ("%lu", n);
        return;
    }
    printf_comma (n/1000);
    printf (",%03lu", n%1000);
}

/* return the sum of manhattan distances from state to goal
	 initially we set x position and then loop again to get y position
**/
int manhattan( int* state )
{
	int sum = 0;
	int x1[ELEMENTS], x2[ELEMENTS], y2[ELEMENTS], y1[ELEMENTS], i,j;
	for ( i = 0; i < ELEMENTS; i++) {
		x1[i] = i%EDGE_LENGTH;
		x2[i] = state[i]%EDGE_LENGTH;
		for ( j = 0; j <= EDGE_LENGTH; j++ ) {
			if ( j*EDGE_LENGTH <= i && i < j*EDGE_LENGTH + EDGE_LENGTH) {
				y1[i] = j;
			}
			if ( j*EDGE_LENGTH <= state[i] && state[i] < j*EDGE_LENGTH + EDGE_LENGTH) {
				y2[i] = j;
			}
		}
		// removes blank spaces impact on sum
		if (state[i] == 0) {
			x1[i] = 0;
			y1[i] = 0;
		}
			sum += abs(x1[i] - x2[i]) + abs(y1[i] - y2[i]);
	}

	return( sum );
}


/* return 1 if op is applicable in state, otherwise return 0 */
int applicable( int op )
{
       	return( ap_ops[op][blank_pos] );
}


/* apply operator */
void apply( node_s* n, int op )
{
	int t;

	//find tile that has to be moved given the op and blank_pos
	t = blank_pos + (op == 0 ? -1 : (op == 1 ? 1 : (op == 2 ? -4 : 4)));

	//apply op
	n->state[blank_pos] = n->state[t];
	n->state[t] = 0;

	//update blank pos
	blank_pos = t;
}

// finds the min of two ints
 int min(int x, int y)
 {
  return (x < y) ? x : y;
}

// returns the reverse of the previous move
int reverseMove(int a)
{
	if (a == LEFT) {
		return RIGHT;
	} else if ( a == RIGHT){
		return LEFT;
	} else if (a == UP) {
		return DOWN;
	} else {
		return UP;
	}
}

/* Recursive IDA
 * keep track of old moves then apply new moves. calculate heuristic of new state
 * update evaluation function f, and cost of path g then use IDA again with
 * new state put into it. If the threeshold is less than the evaluation function
 * f. update new threshold to minimum of (f, newThreshold)
 * once a node is found return it. else return to IDA_control_loop and try again
 * with the newThreshold.
 * also not if a move is made without a success we backtrack from that move.
 * also prune duplicate nodes by checking what the previous move was, and doing
 * any move except the reverseMove of move applied.
**/
node_s* ida( node_s* node, int threshold, int* newThreshold )
{
int a;
int tmp = blank_pos;
int old_move = last_move;
node_s* r = NULL;

generated += 1;
for (a = 0 ; a < MOVE_SET ; a ++) {
	if (applicable(a) && !(last_move == reverseMove(a))) {
		last_move = a;
		expanded += 1;
		apply(node,a);
		int h = manhattan(node->state);
		node->g += 1;
		node->f = node->g + h;

		if (node->f > threshold) {
				*newThreshold = min(*newThreshold,node->f);
			}
			else {
					if (h == 0) {
						return node;
					}
					r = ida(node, threshold, newThreshold);
					if (r != NULL) {
						return r;

					}
		}
		apply(node , reverseMove(a));
		blank_pos = tmp;
		last_move = old_move;
		node->g -= 1;
	}
}
	return( NULL );
}


/* main IDA control loop
 * set newThreshold to the upper bound of optimal solution to 15puzzle
 * initialise statistics, thresholds and nodes
 * While the IDA doesn't find a solution keep updating going 'deeper
 * if threshold = 81 no optimal solution can be found and since ida finds all
 * paths there must not be a solution.'
**/
int IDA_control_loop(  ){
	node_s* r = NULL;

	int threshold;
	//int upperBoundOptimalSoln = 81;
	int newThreshold = UPPER_BOUND_OPTIMAL_SOLN;
	/* initialize statistics */
	generated = 0;
	expanded = 0;

	/* compute initial threshold B */
	initial_node.f = threshold = manhattan( initial_node.state );
	printf( "Initial Estimate = %d\nThreshold = ", threshold );

	while (r == NULL) {
		newThreshold = UPPER_BOUND_OPTIMAL_SOLN;
		initial_node.g = 0;
		r = ida(&initial_node,threshold,&newThreshold);
		if (r == NULL) {
			threshold = newThreshold;
			printf("%d ", threshold);
			if (threshold == UPPER_BOUND_OPTIMAL_SOLN) {
				printf("\n No optimal solution found, puzzle not solvable\n");
				break;
			}
		}
	}
	if(r)
		return r->g;
	else
		return -1;
}


static inline float compute_current_time()
{
	struct rusage r_usage;

	getrusage( RUSAGE_SELF, &r_usage );
	float diff_time = (float) r_usage.ru_utime.tv_sec;
	diff_time += (float) r_usage.ru_stime.tv_sec;
	diff_time += (float) r_usage.ru_utime.tv_usec / (float)1000000;
	diff_time += (float) r_usage.ru_stime.tv_usec / (float)1000000;
	return diff_time;
}

int main( int argc, char **argv )
{
	int i, solution_length;

	/* check we have a initial state as parameter */
	if( argc != 2 )
	{
		fprintf( stderr, "usage: %s \"<initial-state-file>\"\n", argv[0] );
		return( -1 );
	}


	/* read initial state */
	FILE* initFile = fopen( argv[1], "r" );
	char buffer[256];

	if( fgets(buffer, sizeof(buffer), initFile) != NULL ){
		char* tile = strtok( buffer, " " );
		for( i = 0; tile != NULL; ++i )
			{
				initial_node.state[i] = atoi( tile );
				blank_pos = (initial_node.state[i] == 0 ? i : blank_pos);
				tile = strtok( NULL, " " );
			}
	}
	else{
		fprintf( stderr, "Filename empty\"\n" );
		return( -2 );

	}

	if( i != 16 )
	{
		fprintf( stderr, "invalid initial state\n" );
		return( -1 );
	}

	/* initialize the initial node */
	initial_node.g=0;
	initial_node.f=0;

	print_state( initial_node.state );


	/* solve */
	float t0 = compute_current_time();

	solution_length = IDA_control_loop();

	float tf = compute_current_time();

	/* report results */
	printf( "\nSolution = %d\n", solution_length);
	printf( "Generated = ");
	printf_comma(generated);
	printf("\nExpanded = ");
	printf_comma(expanded);
	printf( "\nTime (seconds) = %.2f\nExpanded/Second = ", tf-t0 );
	printf_comma((unsigned long int) expanded/(tf+0.00000001-t0));
	printf("\n\n");

	/* aggregate all executions in a file named report.dat, for marking purposes */
	FILE* report = fopen( "report.dat", "a" );

	fprintf( report, "%s", argv[1] );
	fprintf( report, "\n\tSoulution = %d, Generated = %lu, Expanded = %lu", solution_length, generated, expanded);
	fprintf( report, ", Time = %f, Expanded/Second = %f\n\n", tf-t0, (float)expanded/(tf-t0));
	fclose(report);

	return( 0 );
}
