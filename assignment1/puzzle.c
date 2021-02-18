#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
int blank_pos;

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

/*
 * Helper arrays for the applicable function
 * applicability of operators: 0 = left, 1 = right, 2 = up, 3 = down
 */
int ap_opLeft[]  = { 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1 };
int ap_opRight[]  = { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0 };
int ap_opUp[]  = { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int ap_opDown[]  = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 };
int *ap_ops[] = { ap_opLeft, ap_opRight, ap_opUp, ap_opDown };

// elements in an array
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

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
	 initially we set x position and then loop again to get y position*/
int manhattan( int* state )
{
	int sum = 0;
	int x1[16], x2[16], y2[16], y1[16], i,j;
	for ( i = 0; i < 16; i++) {
		x1[i] = i%4;
		x2[i] = state[i]%4;
		for ( j = 0; j <= 4; j++ ) {
			if ( j*4 <= i && i < j*4 + 4) {
				y1[i] = j;
			}
			if ( j*4 <= state[i] && state[i] < j*4 + 4) {
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

/* Recursive IDA */
node_s* ida( node_s* node, int threshold, int* newThreshold )
{
int a;
node_s* next = NULL;

for (a = 0 ; a < 4 ; a ++) {
	if (applicable(a)) {
	//	next = (node_s*)malloc(sizeof(node_s));
		next = node;				// make equal to node so can use apply func
		print_state(next->state);
		apply(next , a);
		//print_state(next->state);
		next->g = node->g + 1;// printf("%i\n", node->g);
		next->f = next->g + manhattan(next->state);// printf("%i \n", node->f);

		if (next->f > threshold) {
			threshold = min(next->f , *newThreshold);
		//	printf("IN THRESHOLD IF STATEMENT \n");
		} else {
			if (manhattan(next->state) == 0) {
				printf("GOAL STATE \n");
				return next;
			}
			if (ida(next, threshold, newThreshold) != NULL) {
				return ida(next, threshold, newThreshold);
			}
		//	free(next);
		}
	}
}
	return( NULL );
}


/* main IDA control loop */
int IDA_control_loop(  ){
	node_s* r = NULL;

	int threshold;
	int large = 42;
	int* newThreshold = &large;
	/* initialize statistics */
	generated = 0;
	expanded = 0;

	/* compute initial threshold B */
	initial_node.f = threshold = manhattan( initial_node.state );

	printf( "Initial Estimate = %d\nThreshold = ", threshold );

	while (r == NULL) {

		//node_s* node = (node_s*)malloc(sizeof(node_s));
		//node->state = initial_node.state;
	//	memcpy(node->state, initial_node.state, NELEMS(initial_node.state) + 1);
	node_s* node = &initial_node;
		node->g = 0;
		r = ida(node,threshold,newThreshold);
		if (r == NULL) {
			threshold = *newThreshold;
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
