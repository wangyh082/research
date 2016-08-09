void insertHeap(int *heap, int *heapi, int n, int s, int v, int vi)
// inserts the element (v, vi) into the priority heap (heap, heapi) of size s
// and of maximum size n
//
// input arguments:
// n  = maximum size of the heap
// s  = size of the heap (number of its current elements)
// v  = value of the new element
// vi = index of the new element
//
// input and output arguments:
// heap  = the heap of element values
// heapi = the heap of element indexes
{
	if (s >= 0 && s < n)
	{
		// insert the new element at the end of the heap
		heap[s] = v;
		heapi[s] = vi;

		// shift up procedure
		while (s > 0 && heap[s] > heap[(s-1)/2])
		{
			// changes are applied in both heaps (values and indexes) such that
			// the correspondence to be conserved
			exchange(&heap[s], &heap[(s-1)/2]);
			exchange(&heapi[s], &heapi[(s-1)/2]);
			s = (s-1)/2;
		} //while
	} //if
} //insertHeap

/******************************************************************************/

void removeHeap(int *heap, int *heapi, int n, int s, int *v, int *vi)
// removes the maximum element (v, vi) from the priority heap (heap, heapi) of
// size s and of maximum size n
//
// input arguments:
// n  = maximum size of the heap
// s  = size of the heap (number of its current elements)
//
// input and output arguments:
// heap  = the heap of element values
// heapi = the heap of element indexes
//
// output arguments:
// v  = value of the new element
// vi = index of the new element
{
	if (s > 0)
	{
		// return the first element of the heap which is the maximum one //从大到小 
		*v = heap[0];
		*vi = heapi[0];

		// insert the last element of the heap to the root of the heap
		heap[0] = heap[s-1];
		heapi[0] = heapi[s-1];

		// shift down procedure
		int k = 0;
		int maxChild;
		if (heap[k*2+1] > heap[k*2+2])
		{
			maxChild = k*2+1;
		} //if
		else
		{
			maxChild = k*2+2;
		} //else

		while (maxChild < s-1 && heap[k] < heap[maxChild])
		{
			// changes are applied in both heaps (values and indexes) such that
			// the correspondence to be conserved
			exchange(&heap[k], &heap[maxChild]);
			exchange(&heapi[k], &heapi[maxChild]);
			k = maxChild;

			if (k*2+1 < s-1)
			{
				if (heap[k*2+1] > heap[k*2+2])
				{
					maxChild = k*2+1;
				} //if
				else
				{
					maxChild = k*2+2;
				} //else
			} //if
			else
			{
				maxChild = s;
			} //else
		} //while
	} //if s
} //removeHeap

/******************************************************************************/

void sort(int *h, int *hi, int n)
// sorts the elements of the arrays h and hi according to the values of h using
// the heap sort procedure
//
// input arguments:
// n = size of the arrays
//
// input and output arguments:
// h  = array of values
// hi = array of indexes (represents the initial positions of the elements)
{
	// heaps
	int *heap = (int *) malloc(n * sizeof(int));
	int *heapi = (int *) malloc(n * sizeof(int));

	// insert elements to heaps
	int i;
	for (i = 0; i < n; i++)
	{
		insertHeap(heap,heapi,n,i,h[i],hi[i]);
	} //for

	// remove elements from heaps
	for (i = 0; i < n; i++)
	{
		removeHeap(heap,heapi,n,n-i,&h[i],&hi[i]);
	} //for

	free(heap);
	free(heapi);
} //sort
