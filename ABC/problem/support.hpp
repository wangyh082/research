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

void exchange(double *x, double *y)
// exchange the values between the two arguments
//
// input arguments:
// x = integer
// y = integer
{
	double temp = *x;
	*x = *y;
	*y = temp;
} //exchange

void exchange1(int *x, int *y)
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
