void grasp(int **og, int *sl, int n, double a, int mi,
            int *gto, int *gso, int *git)// 用指针做函数参数的好处 
// GRASP. estimates a solution to the ssp instance described by the adjacency
// matrix og (see the papar for details)
//
// input arguments:
// og = overlap graph that describes the problem instance
// sl = string lengths
// n  = instance size
// a  = value of parameter a (greediness / randomness)
// mi = maximum iterations
//
// output arguments:
// gto = total overlap achieved by GRASP
// gso = string order returned from GRASP
// git = GRASP iterations for its best solution
{
	int n2 = n*n;
	// sort the elements of the overlap graph og in **decreasing order
	int *h = (int *) malloc(n2 * sizeof(int));
	int *hi = (int *) malloc(n2 * sizeof(int));

	int i,j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			h[i*n+j] = og[i][j];
			hi[i*n+j] = i*n+j;
		}
	sort(h,hi,n2);

	int *hir = (int *) malloc(n2 * sizeof(int));
	for (i = 0; i < n2; i++)
		hir[hi[i]] = i;

	// compute a GRASP solution
	// construction phase total overlap
	int cpTO;
	// construction phase string order
	int *cpSO = (int *) malloc(n * sizeof(int));
	// 2-exchange local search total overlap
	int ls2eTO;
	// 2-exchange local search string order
	int *ls2eSO = (int *) malloc(n * sizeof(int));
	// shift local search total overlap
	int lsShTO;
	// shift local search string order
	int *lsShSO = (int *) malloc(n * sizeof(int));

	*gto = -1;
	int iteration;
	// iterations of grasp
	for (iteration = 1; iteration <= mi; iteration++)
	{
		constructionPhase(og, sl, n, a, h, hi, hir, &cpTO, cpSO);
		localSearch2e(og, n, cpTO, cpSO, &ls2eTO, ls2eSO);
		localSearchShift(og, n, ls2eTO, ls2eSO, &lsShTO, lsShSO);

		// if a better solution has been found, the best solution is updated
		if (*gto < lsShTO)
		{
			*gto = lsShTO;
			for (i = 0; i < n; i++)
				gso[i] = lsShSO[i];
			*git = iteration;
		}
	}

	// free memory** 
	free(cpSO);
	free(ls2eSO);
	free(lsShSO);

	free(h);
	free(hi);
	free(hir);
} //grasp
