void grasp_rp(int **og,  int n,  double a,  int mi,int *gto, int *gso, int *git)
{
   	// compute a GRASP_PR solution
	// construction phase total overlap
	int cpTO;
	// construction phase string order
	int *cpSO = (int *) malloc(n * sizeof(int));
	//  local search total overlap
	int lsTO;
	//  local search string order
	int *lsSO = (int *) malloc(n * sizeof(int));

	*gto = -1;
    int iteration;
	// iterations of grasp
	for (iteration = 1; iteration <= 1; iteration++)
	{
		constructionPhase(og, n, a,&cpTO,cpSO);
	   //	localSearch(og, n, cpTO, cpSO, &lsTO, lsSO);

		// if a better solution has been found, the best solution is updated
		if (*gto < cpTO)
		{
            int i;
			*gto = cpTO;
			for (i = 0; i < n; i++)
				gso[i] = cpSO[i];
			*git = iteration;
		}
	}
}
