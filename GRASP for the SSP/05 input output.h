void input(FILE *f, int n, int **og, int *sl)
// reads the data of an instance of size n from the input file f and returns the
// overlap graph og and the string lengths sl
//
// input arguments:
// f  = pointer to the input file
// n  = size of the instance
//
// output arguments:
// og = overlap graph
// sl = string lengths
{
	int i,j;
	// the input file can be of the type 1 or 2. these file types are described
	// in the "read me.txt" file
	int type;
	fscanf(f, "%d", &type);
	if (type == 1)
	{
		// read the data of the overlap graph
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				fscanf(f, "%d", &og[i][j]);
			} //for j
		} //for i

		// read the string lengths
		for (i = 0; i < n; i++)
		{
			fscanf(f, "%d", &sl[i]);
		} //for i
	} //if
	else
	{
		// read the maximum string length
		int maxlength;
		fscanf(f, "%d", &maxlength);
		// data structure for strings//the string letters 
		int **string = (int **) malloc(n * sizeof(int *));
		for (i = 0; i < n; i++)
			string[i] = (int *) malloc(maxlength * sizeof(int));

		// read the string data (letters) and compute the length of each one
		int c;
		for (i = 0; i < n; i++)
		{
			sl[i] = 0;
			c = 0;
			while (c != -1)
			{
				fscanf(f, "%d", &c);
				string[i][sl[i]++] = c;
			} //while
			sl[i]--;
		} //for

		// create the overlap graph
		createOverlapGraph(n, sl, string, og);
	} //else 
} //input

/******************************************************************************/

void output(int n, double a, int mi, int *sl, int git, int gto, int *gso)
// prints the details of a GRASP solution
//
// input arguments:
// n   = instance size
// a   = value of the parameter alpha
// mi  = maximum iterations
// sl  = string lengths
// git = GRASP iterations for its best solution
// gto = total overlap achieved by GRASP
// gso = string order returned by GRASP
{
	int i;
	// compute the sum of the string lengths
	int len = 0;
	for (i = 0; i < n; i++)
	{
		len += sl[i];
	};

	// print the output
	fprintf(file, "\nGRASP for the SSP\n");
	fprintf(file, "-----------------\n");
	fprintf(file, "instance size (number of strings)      : %d\n", n);
	fprintf(file, "value of the parameter alpha           : %lf\n", a);
	fprintf(file, "maximun number of iterations           : %d\n\n", mi);
	fprintf(file, "iterations for the best GRASP solution : %d\n", git);
	fprintf(file, "length of the superstring              : %d\n", len - gto);
	fprintf(file, "total overlap in the superstring       : %d\n", gto);
	fprintf(file, "string order                           : ");
	for (i = 0; i < n; i++)
		fprintf(file, "%d ", gso[i]);
	fprintf(file, "\n\n");
} //output
