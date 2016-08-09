void grasp_rp( int n, double a, int mi,int &gto, int *gso, int &git)
{
   	// compute a GRASP_PR solution
	// construction phase result
	int cpTO;
	// construction phase string order
	int *cpSO = (int *) malloc(n * sizeof(int));
	//  local search total overlap
	int lsTO;
	//  local search string order
	int *lsSO = (int *) malloc(n * sizeof(int));
    //the array we need to proceed the pathrelinking
    int *r = (int *) malloc(n * sizeof(int));
    memset(elite,0,sizeof(elite));
	gto = -1;
    int iteration;
	// iterations of grasp_pr
	int count=0;
	int d=0;
	int dd;
	int min=99999999;
	for (iteration = 1; iteration <= mi; iteration++)
	{
        fprintf(file,"iteration=%d\n",iteration);
	  to:cpTO=constructionPhase(n,a,cpSO);
		/* fprintf(file,"cpSO:\n");
 	    for(int i=0;i<n;i++)
 	      fprintf(file,"%d ",cpSO[i]);
 	      fprintf(file,"\n");*/
	  	lsTO=localSearch(n,cpSO,lsSO);
 	    //fprintf(file,"P=%d\n",P);
 	   /*fprintf(file,"lsSO:\n");
 	    for(int i=0;i<n;i++)
 	      fprintf(file,"%d ",lsSO[i]);
 	      fprintf(file,"\n");*/
	  	if(count<P)
	   {
           if(compare(elite,lsSO,count,n))
           {  
             for(int i=0;i<n;i++)
               elite[count][i]=lsSO[i]; 
              count++;              
           }           
           else
           {
               goto to;
           }
           /* fprintf(file,"count=%d\n",count);
            fprintf(file,"elite1:\n");
            for(int i=0;i<count;i++)
            {
              for(int j=0;j<n;j++)
                fprintf(file,"%d ",elite[i][j]);
                fprintf(file,"\n");
            }*/
       }       
       else
       {
           int e;
           e=rand()%count;
           int value;          
           int minpo;//find the worst solution
       /* fprintf(file,"elite1:\n");
        for(int i=0;i<count;i++)
        {
          for(int j=0;j<n;j++)
            fprintf(file,"%d ",elite[i][j]);
            fprintf(file,"\n");
        }*/
           for(int i=0;i<count;i++)
           {
              value= evaldis(n,elite[i]);
              if(value<min)
              {
                  min=value;
                  minpo=i;
              }
           }
           
           fprintf(file,"min=%d minpo=%d\n",min,minpo);
           for(int i=0;i<count;i++)
           d+=dis(elite[i],lsSO,n);
           double ran;
           ran=rand()%10/10.0;//produce one decimal between 0 and 1 randomly
          // ran=0.0;
           fprintf(file,"ran=%lf\n",ran);
          
           double ran1;
           ran1=dis(elite[e],lsSO,n)/(d*1.0);
           fprintf(file,"ran1=%lf\n",ran1);
           int dis1;
          /* fprintf(file,"elite[%d]:\n",e);
           for(int i=0;i<n;i++)
             fprintf(file,"%d ",elite[e][i]);
             fprintf(file,"\n");
             fprintf(file,"lsSO:\n");
 	        for(int i=0;i<n;i++)
 	        fprintf(file,"%d ",lsSO[i]);
 	        fprintf(file,"\n");*/
           if(ran>ran1) //select it with a probability???more or less??
           {
              dis1=pathrelinking(n,lsSO,elite[e],r);
              fprintf(file,"dis1=%d \n",dis1);
              for(int i=0;i<n;i++)
                fprintf(file,"**%d** ",r[i]);
                fprintf(file,"\n");
              int ddd;//the value of the elite solutions
              int ddis;//the distance between the elite and r 
              int count1=0;
              int minddis=100;//the dis of the most similar solution
              int dpo=0;//the position of the most similar solution
              fprintf(file,"dis1=%d min=%d\n",dis1,min);
              if(compare(elite,r,count,n)&&dis1>min)
              {
                     for(int i=0;i<count;i++)
                     {
                        ddd=evaldis(n,elite[i]);
                        if(ddd<dis1)
                        {
                          ddis=dis(elite[i],r,n);
                          if(ddis<minddis)
                          {
                               minddis=ddis;
                               dpo=i;
                          }
                        }
                     }
                     fprintf(file,"dpo=%d\n",dpo);
                     for(int i=0;i<n;i++)
                        elite[dpo][i]=r[i];
              }
           }           
       }
        int max=0;
        int temp;
        int maxpo;
        fprintf(file,"elite2:\n");
        for(int i=0;i<count;i++)
        {
          for(int j=0;j<n;j++)
            fprintf(file,"%d ",elite[i][j]);
            fprintf(file,"\n");
        }
        for(int i=0;i<count;i++)
        {
                temp=evaldis(n,elite[i]);
                if(temp>max)
                {
                    max=temp;
                    maxpo=i;
                }
        }
        fprintf(file,"max= %d maxpo= %d\n",max,maxpo);
		// if a better solution has been found, the best solution is updated
		if (gto < max)
		{
            int i;
			gto = max;
			for (i = 0; i < n; i++)
				gso[i] = elite[maxpo][i];
			git = iteration;
		}
	}
}
