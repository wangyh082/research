int constructionPhase(int n, double a,int *co)
{
     
      int h[N];
      int hi[N];
      int cl=n*(n-1);
            
      int flag[500];
      
      int d;
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
      int ct=0;
      int k=0;
      int e;//the random number we choose
      for(int i=0;i<n;i++)
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
      }
     // fprintf(file,"k=%d\n",k);
      //qsort(h,k,sizeof(h[0]),cmp);  
      sort(h,hi,k); 
      int rcl;
      rcl = (int)(a*cl);
    /*  for(int i=0;i<rcl;i++)
      {
              fprintf(file,"%d %d %d %d\n",h[i],hi[i],pairor[hi[i]][0],pairor[hi[i]][1]);
             // fprintf(file,"%d %d \n",h[i],hi[i]);
              int t=(hi[i]+1)%(n-1);
              int t1=(hi[i]+1)/(n-1);
              if(t==0)
                pairor[i][0]=t1-1;
              else
                 pairor[i][0]=t1;
              if(t<=pairor[i][0])
              pairor[i][1]=t-1;
              else
              pairor[i][1]=t;
             // fprintf(file,"%d %d \n",pairor[i][0],pairor[i][1]); this is wrong
      }*/
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
                   /* fprintf(file,"temp:\n");
                    for(int k=0;k<j;k++)
                      fprintf(file,"%d ",temp[k]);
                      fprintf(file,"\n");*/
                    proc(n,temp,j);
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
           h[i]=evaldis(j,temp1[i]);
           hi[i]=i;
         }
           //qsort(h,numl,sizeof(h[0]),cmp);
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


int localSearch(int n, int *soo, int *son)
{
    memset(cls,0,sizeof(cls));
    int a,b;
    int ton;
    int count=1;
    for(int i=0;i<n;i++)
       son[i]=soo[i];    
    while(count!=0)
    { 
        //count is the number of the cls array
        count=0;
        a=evaldis(n,son);
        ton=a;
        for(int i=0;i<n-1;i++)
        {
                for(int j=i+1;j<n;j++)
                {
                    exchange(&son[i],&son[j]);
                    b=evaldis(n,son);
                    if(b>a)
                    {
                         ton=b;
                         for(int k=0;k<n;k++)
                         cls[count][k]=son[k];
                         count++;//important
                    }
                    exchange(&son[i],&son[j]);
                }
        }
       // fprintf(file,"count=%d \n",count);
        if (count!=0)
        {
             int e;
             e=rand()%count;
             //fprintf(file,"e=%d\n",e);           
             for(int k=0;k<n;k++)
               son[k]=cls[e][k];
        }
    } 
    return  ton;  
}
