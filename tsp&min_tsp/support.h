int min(int x, int y)
// returns the minimum of the two arguments
//
// input arguments:
// x = integer
// y = integer
{
	if (x < y)
		return x;
	else
		return y;
} //min

/******************************************************************************/

int max(int x, int y)
// returns the maximum of the two arguments
//
// input arguments:
// x = integer
// y = integer
{
	if (x > y)
		return x;
	else
		return y;
} //max

/******************************************************************************/

void exchange(int *x, int *y)
// exchange the values between the two arguments
//
// input arguments:
// x = integer
// y = integer
{
	int temp = *x;
	*x = *y;
	*y = temp;
} //exchange

/******************************************************************************/

double n2a(int n)
// computes the most appropriate value for the parameter alpha according to the
// instance size n (see first computational experiment in the paper)
//
// input arguments:
// n = instance size
{
	double a;
	if (n <= 112)
		a = 0.01;
	else
		a = (15*pow(n, 1.3) + 7*pow(n, 1.7)) / (2 * pow(n, 3.0));
	return a;
} //n2a

int  evaldis(int n,int *order,int **og)//evaluate the distances over the tsp problem
{
      int d=0;
      for(int i=0;i<n-1;i++)
      {
          d+=og[order[i]][order[i+1]];
      }
      d+=og[order[n-1]][order[0]];
      return d;
}

