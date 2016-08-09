void constructionPhase(int **og, int *sl, int n, double a,
                       int *h, int *hi, int *hir,
					   int *cpto, int *cpso)
// implements the construction phase of the GRASP (see the papar for details)
//
// input arguments:
// og  = overlap graph that describes the problem instance
// sl  = string lengths
// n   = instance size
// a   = value of parameter alpha (greediness / randomness)
// h   = array with the elements of the og in decreasing order
// hi  = array with the corresponding indexes of the elements of the array h
// hir = the reverse array of hi (hir[hi[i]] = hi[hir[i]] = i)
//
// output arguments:
// cpto = construction phase total overlap
// cpso = construction phase string order
{
	// the arrays h, hi and hir are computed in function grasph and sended hear
	// as arguments, because it is redundant to caclulate them in each iteration
	// of the GRASP method

	int n2 = n*n;
	// initialize the linked list, that comprise the candidate list
	int i,j,k;
	// linked list first element
	int llfirst;
	// linked list last element
	int lllast;
	int *valid = (int *) malloc(n2 * sizeof(int));
	int *next = (int *) malloc(n2 * sizeof(int));
	int *previous = (int *) malloc(n2 * sizeof(int));

	llinitialization(n, &llfirst, &lllast, valid, next, previous);//链表元素都是指针 
	for (i = 0; i < n2; i++)
		if (h[i] == -1)
			llremove(i, &llfirst, &lllast, valid, next, previous);

	// find a greedy, random and adaptive solution
	int *pairs = (int *) malloc(n * sizeof(int));
	int *pairsr = (int *) malloc(n * sizeof(int));
	int *first = (int *) malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
	{
		pairs[i] = -1;
		pairsr[i] = -1;
		first[i] = 1;
	}

	int *substrings = (int *) malloc(n * sizeof(int));
	int *substringsO = (int *) malloc(n * sizeof(int));

	*cpto = 0;
	int sub;
	int ss;
	int e;
	int cl;
	int rcl;
	int x;
	int row;
	int column;
	int selections;
	for (selections = 0; selections < n-1; selections++)
	{
		cl = (n-selections)*(n-selections-1);
		rcl = (int)(a*cl);
		if (rcl == 0)
			e = 0;
		else
			e = rand() % rcl;//生成0~(rcl-1)中的随机数 

		i = llfirst;
		for (j = 0; j < e; j++)
			i = next[i];

		row = hi[i] / n;
		column = hi[i] % n;

		// estimate the number of the strings, that are substrings of the new
		// merge string
		ss = 0;
		for (k = 0; k < n; k++)
		{
			if (pairs[k] == -1 && pairsr[k] == -1)
			{
				if (sl[k] <= og[row][k] + og[k][column] - og[row][column])
				{
					substrings[ss] = k;
					substringsO[ss] = og[row][k];
					ss++;
				}
			}
		}
		sort(substringsO, substrings, ss);

		// if there is even one substring
		if (ss > 0)
		{
			// merge the first initial string with the first of the substrings
			*cpto = *cpto + og[row][substrings[0]];

			pairs[row] = substrings[0];
			pairsr[substrings[0]] = row;
			first[substrings[0]] = 0;

			for (i = 0; i < n; i++)
			{
				x = hir[i*n+substrings[0]];
				llremove(x, &llfirst, &lllast, valid, next, previous);

				x = hir[row*n+i];
				llremove(x, &llfirst, &lllast, valid, next, previous);
			}

			i = row;
			while (pairs[i] != -1)
				i = pairs[i];
			j = substrings[0];
			while (pairsr[j] != -1)
				j = pairsr[j];
			x = hir[i*n+j];
			llremove(x, &llfirst, &lllast, valid, next, previous);

			// merge all the substrings in the sorted order
			for (sub = 0; sub < ss-1; sub++)
			{
				*cpto = *cpto + og[substrings[sub]][substrings[sub+1]];

				pairs[substrings[sub]] = substrings[sub+1];
				pairsr[substrings[sub+1]] = substrings[sub];
				first[substrings[sub+1]] = 0;

				for (i = 0; i < n; i++)
				{
					x = hir[i*n+substrings[sub+1]];
					llremove(x, &llfirst, &lllast, valid, next, previous);

					x = hir[substrings[sub]*n+i];
					llremove(x, &llfirst, &lllast, valid, next, previous);
				}

				i = substrings[sub];
				while (pairs[i] != -1)
					i = pairs[i];
				j = substrings[sub+1];
				while (pairsr[j] != -1)
					j = pairsr[j];
				x = hir[i*n+j];
				llremove(x, &llfirst, &lllast, valid, next, previous);
			}

			// merge the last substring with the second initial string
			*cpto = *cpto + og[substrings[ss-1]][column];

			pairs[substrings[ss-1]] = column;
			pairsr[column] = substrings[ss-1];
			first[column] = 0;

			for (i = 0; i < n; i++)
			{
				x = hir[i*n+column];
				llremove(x, &llfirst, &lllast, valid, next, previous);

				x = hir[substrings[ss-1]*n+i];
				llremove(x, &llfirst, &lllast, valid, next, previous);
			}

			i = substrings[ss-1];
			while (pairs[i] != -1)
				i = pairs[i];
			j = column;
			while (pairsr[j] != -1)
				j = pairsr[j];
			x = hir[i*n+j];
			llremove(x, &llfirst, &lllast, valid, next, previous);

			selections = selections + ss;
		}
		// if there is not any substring
		else
		{
			// merge the initial strings
			pairs[row] = column;
			pairsr[column] = row;
			first[column] = 0;
			*cpto = *cpto + h[i];

			for (i = 0; i < n; i++)
			{
				x = hir[i*n+column];
				llremove(x, &llfirst, &lllast, valid, next, previous);

				x = hir[row*n+i];
				llremove(x, &llfirst, &lllast, valid, next, previous);
			}

			i = row;
			while (pairs[i] != -1)
				i = pairs[i];
			j = column;
			while (pairsr[j] != -1)
				j = pairsr[j];

			x = hir[i*n+j];
			llremove(x, &llfirst, &lllast, valid, next, previous);
		} //if ss
	} //for selections

	// compute the permutation that corresponds to the pairs induced from the
	// construction phase
	i = 0;
	while (first[i] != 1)
		i++;
	cpso[0] = i;
	for (i = 1; i < n; i++)
		cpso[i] = pairs[cpso[i-1]];

	// free memory
	free(substrings);
	free(substringsO);

	free(valid);
	free(next);
	free(previous);

	free(pairs);
	free(pairsr);
	free(first);
} //construction phase

/******************************************************************************/

void localSearch2e(int **og, int n, int too, int *soo, int *ton, int *son)
// implements the local search phase of the GRASP with respect to the 2-exchange
// neighborhood (see the papar for details)
//
// input arguments:
// og = overlap graph that describes the problem instance
// n = instance size
// too = total overlap (old) of the construction phase
// soo = string order (old) of the construction phase
//
// output arguments:
// ton = total overlap (new) of the 2-exchange local search phase
// son = string order (new) of the 2-exchange local search phase
{
	int i,j;
	bool keepon = true;

	*ton = too;
	for (i = 0; i < n; i++)
		son[i] = soo[i];

	int difference;
	// while a local optimum with respect to the 2-exchange neighborhood is not
	// found
	while (keepon)
	{
		keepon = false;
		// for each pair of strings (elements of the permutation)
		for (i = 0; i < n-1; i++)
		{
			for (j = i+1; j < n; j++)
			{
				// compute the difference in the cost function (in the total
				// overlap) when these two strings exchange their position
				if (i+1 == j)
				{
					difference = - og[son[i]] [son[j]]
								 + og[son[j]] [son[i]];
				}
				else
				{
					difference = - og[son[i]]  [son[i+1]]
								 - og[son[j-1]][son[j]]
								 + og[son[j]]  [son[i+1]]
								 + og[son[j-1]][son[i]];
				}
				if (i != 0)
				{
					difference = difference - og[son[i-1]][son[i]]
											+ og[son[i-1]][son[j]];
				}
				if (j != n-1)
				{
					difference = difference - og[son[j]][son[j+1]]
											+ og[son[i]][son[j+1]];
				}

				// if the difference causes gain to the total overlap then the
				// exchange is made permanent
				if (difference > 0)
				{
					exchange(&son[i], &son[j]);
					*ton = *ton + difference;
					keepon = true;
					i = n+1;
					j = n+1;
				}
			} //for j
		} //for i
	} //while
} //localSearch2e

/******************************************************************************/

void localSearchShift(int **og, int n, int too, int *soo, int *ton, int *son)
// implements the local search phase of the GRASP with respect to the shift
// neighborhood (see the papar for details)
//
// input arguments:
// og = overlap graph that describes the problem instance
// n = instance size
// too = total overlap (old) of the 2-exchange local search phase
// soo = string order (old) of the 2-exchange local search phase
//
// output arguments:
// ton = total overlap (new) of the shift local search phase
// son = string order (new) of the shift local search phase
{
	int i;
	int difference;
	int maxpos = -1;
	int maxdiff = -1;

	// find the shift that causes the greater gain to the cost function
	for (i = 0; i < n-1; i++)
	{
		difference = - og[soo[i]][soo[i+1]]
					 + og[soo[n-1]][soo[0]];

		if (difference > 0)
		{
			if (maxdiff == -1)
			{
				maxdiff = difference;
				maxpos = i;
			}
			else
			{
				if (maxdiff < difference)
				{
					maxdiff = difference;
					maxpos = i;
				}
			}
		}
	}

	// make the appropriate changes to the permutation
	if (maxdiff != -1)
	{
		for (i = 0; i < n; i++)
		{
			son[i] = soo[(i + maxpos + 1) % n];
		}
		*ton = too + maxdiff;
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			son[i] = soo[i];
		}
		*ton = too;
	}
} //localSearchShift
