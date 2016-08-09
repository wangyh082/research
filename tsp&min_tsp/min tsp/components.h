double constructionPhase(int n, double a,int *co,double *p2)
{
     
               
      int flag[n];
      
      double d;
      //the planar array to store the solutions in which we find the next temp order
      memset(temp1,0,sizeof(temp1));
      //to flag the number we use or not "0": not used "1" :used
      memset(flag,0,sizeof(flag));
      //the temp order we need to assemble the next order we need 
      memset(temp,0,sizeof(temp));
      //the orders we need to caculate the rcl set
      memset(pairor,0,sizeof(pairor));
      //the distance,update dynamically
      memset(h,0,sizeof(h));
      //the position
      memset(hi,0,sizeof(hi));
      //the result distance we obtain
      double ct=0.0;
      int k=0;
      int e;//the random number we choose
     /* for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
      {
                if(i!=j)
                {
                    d=og[i][j]+og[j][i];
                    h[k]=d;
                    hi[k]=k;              
                    pairor[k][0]=i;
                    pairor[k][1]=j;  
                    k++;
                }
      }*/
     // fprintf(file,"k=%d\n",k);
      //qsort(h,k,sizeof(h[0]),cmp);
      int aa;
      aa=rand()%n;
      flag[aa]=1; 
      for(int i=0;i<n;i++)
      {
        if(flag[i]==0)
        {
              pairor[k][1]=i;
              flag[i]=1;
              k++;
        }        
      }
      for(int i=0;i<k;i++)
      {
         pairor[i][0]=aa;
         d=*(p2+pairor[i][0]*n+pairor[i][1])+*(p2+pairor[i][1]*n+pairor[i][0]);
        // d+=og[pairor[i][0]][pairor[i][1]]+og[pairor[i][1]][pairor[i][0]];
         h[i]=d;
         hi[i]=i;
      }
      sort(h,hi,k);
      memset(flag,0,sizeof(flag)); 
      int rcl;
      rcl = (int)(a*k);
		if (rcl == 0)
			e = 0;
		else
			e = rand() % rcl; 
        //fprintf(file," e=%d %d %d %d %d\n",e,h[e],hi[e],pairor[hi[e]][0],pairor[hi[e]][1]);
		temp[0]=pairor[hi[e]][0];//to use the proc function ,we use the index from 0
		temp[1]=pairor[hi[e]][1];
		flag[temp[0]]=1;
		flag[temp[1]]=1;		
		int j=2;
		int ii;
      memset(h,0,sizeof(h));
      memset(hi,0,sizeof(hi));
       while(j<n)
     { 
        memset(temp1,0,sizeof(temp1));
        int numl=0;
		int i;
		j++; 
		for(i=0;i<n;i++)
        {
              if(flag[i]==0)
              {
                    temp[j-1]=i;
                    temp[j]='\0';
                    /*fprintf(file,"temp:\n");
                    for(int k=0;k<j;k++)
                      fprintf(file,"%d ",temp[k]);
                      fprintf(file,"\n");*/
                    proc(n,temp,j,p2);
                    int jj;
                    for(jj=0;jj<j;jj++)
                      temp1[numl][jj]=temp[jj];
                     numl++;
                     flag[i]=1;
              }                            
        } 
       // fprintf(file,"numl=%d\n",numl);
          for(int i=0;i<numl;i++)
         {
           h[i]=evaldis(j,temp1[i],p2);
           hi[i]=i;
         }
           sort(h,hi,numl);
          /* for(int i=0;i<numl;i++)
            fprintf(file,"%d %d\n",h[i],hi[i]);*/
           rcl = (int)(a*numl);
          // fprintf(file,"rcl=%d\n",rcl);
           if (rcl == 0)
			e = 0;
		   else
			e = rand() % rcl; 
			//fprintf(file,"e=%d\n",e);
           for(int i=0;i<j;i++)
             temp[i]=temp1[hi[e]][i];
           for(int i=0;i<n;i++)
             flag[i]=0; 
             ct=h[e];
           for(int i=0;i<j;i++)
           { 
            // fprintf(file,"%d ",temp[i]);
             flag[temp[i]]=1;
             //fprintf(file,"v=%d\n",h[e]); 
           }
            // fprintf(file,"\n");
       }
         for(int i=0;i<n;i++)
           co[i]=temp[i]; 
       /*  for(int i=0;i<n;i++)
           fprintf(file,"%d ",co[i]);
           fprintf(file,"\n"); 
           fprintf(file,"ct=%d\n",ct); */  
         return ct;        
}
