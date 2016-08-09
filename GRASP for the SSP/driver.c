/*
 * A Greedy Randomized Adaptive Search Procedure (GRASP) for the Shortest
 * Superstring Problem (SSP)
 * 
 * Authors: Theodoros P. Gevezes
 *             [theogev@gen.auth.gr]
 *          Leonidas S. Pitsoulis
 *             [pitsouli@gen.auth.gr]
 *             Department of Mathematical, Physical and Computational Sciences
 *             Faculty of Engineering
 *             Aristotle University of Thessaloniki
 * 
 * corresponding paper: Theodoros Gevezes and Leonidas Pitsoulis. A greedy
 * randomized adaptive search procedure with path relinking for the shortest
 * superstring problem. Journal of Combinatorial Optimization, 2013.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define true 1
#define false 0
#define bool int
#define file stdout //±ê×¼Êä³ö 

#include "01 support.h"
#include "02 linked list.h"
#include "03 heap sort.h"
#include "04 overlap.h"
#include "05 input output.h"
#include "06 components.h"
#include "07 grasp.h"

/******************************************************************************/

int main(int argc, char *argv[])
// input arguments:
// argv[1] = the name of the input file
{
	// check the number of the input arguments
	if (argc < 2)
	{
		fprintf(file, "not an input file\n");
		return 1;
	} //if

	// initialize the seed for the randomization
	srand((unsigned) time(NULL));

	int i;
	// number of strings - size of the instance
	int n;
	// parameter alpha of GRASP
	double a;
	// maximum number of iterations of GRASP
	int mi = 128;

	// open input file
	FILE *f;
	f = fopen(argv[1], "r");
	if (f == NULL)
	{
		printf("can't open input file\n");
		return 2;
	}
	// read the instance size
	fscanf(f, "%d", &n);
	// overlap graph (in all functions the overlap graph is represented by its
	// adjacency matrix with -1 in the main diagonal)
	int **og = (int **) malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		og[i] = (int *) malloc(n * sizeof(int));
	// string lengths
	int *sl = (int *) malloc(n * sizeof(int));
	// read the data from the input file
	input(f, n, og, sl);
	fclose(f);

	// total overlap achieved by GRASP
	int gto;
	// string order returned from GRASP
	int *gso = (int *) malloc(n * sizeof(int));
	// GRASP iterations for its best solution
	int git;

	// compute the appropriate value for the parameter alpha according to the
	// instance size (see first computational experiment in the paper)
	a = n2a(n);
	// compute a GRASP solution
	grasp(og, sl, n, a, mi, &gto, gso, &git);
	// print the GRASP solution
	output(n, a, mi, sl, git, gto, gso);

	// free memory
	free(sl);
	for (i = 0; i < n; i++)
		free(og[i]);
	free(og);
	free(gso);

	return 0;
} //main
