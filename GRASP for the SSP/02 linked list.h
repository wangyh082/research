void llinitialization(int s, int *f, int *l, int *v, int *n, int *p)
// initializes the linked list
//
// input arguments:
// s = size of linked list
//
// output arguments:
// f = first element of the list
// l = last element of the list
// v = array of valid elements
// n = array of "next" pointers
// p = array of "previous" pointers
{
	*f = 0;
	*l = s*s-1;

	int i;
	for (i = 0; i < s*s; i++)
	{
		n[i] = i+1;
		p[i] = i-1;
		v[i] = 1;
	} //for
	n[s*s-1] = -1;
	p[0] = -1;
} //llinitialization

/******************************************************************************/

void llremove(int x, int *f, int *l, int *v, int *n, int *p)
// removes the x-th element from the linked list
//
// input arguments:
// x = element to remove from linked list
// f = first element of the list
// l = last element of the list
//
// input and output arguments:
// v = array of valid elements
// n = array of "next" pointers
// p = array of "previous" pointers
{
	// if the element to be removed is valid (it has not already removed) and
	// the linked list is not empty
	if (v[x] == 1 && *f != *l)
	{
		// if the element is the last of the linked list
		if (x == *l)
		{
			n[p[x]] = n[x];
			*l = p[*l];
		} //if
		// if the element is the first of the linked list
		else if (x == *f)
		{
			p[n[x]] = p[x];
			*f = n[*f];
		} //else if
		// if the element is not the first or the last of the linked list
		else
		{
			n[p[x]] = n[x];
			p[n[x]] = p[x];
		} //else
		v[x] = 0;
	} //if
} //llremove
