void proc2(int n,int *order)
{
    int reorder[2000];//每次插入后的序列 
    int reorder1[2000];//中间对比序列 
    int rereorder[2000];//最好的序列； 
    int sum11;//初始的序列和
    int sum2[2500];//比较的和 
    int sum22;
    int i,j,ii,jj,kk;
    int p;
    int temp;
    for(i=1;i<n;i++)
    {
          for(kk=0;kk<n-1;kk++)
             reorder[kk]=0;
          sum11= evaldis(i+1,order,og);  
         // printf("sum11=%d\n",sum11);
          temp=order[i+1];
          sum22=0;
          for(j=0;j<i;j++)
          {             
              for(kk=0;kk<j;kk++)
                sum2[kk]=0;
              reorder[j]=temp;
              if(j==0) jj=0;
              else
              {
                for(jj=0;jj<j-1;jj++)
                   reorder[jj]=order[jj];
              }
                p=j;
              for(ii=0;ii<i-jj;ii++)
              {
                 ++p;
                 reorder[p]=order[p-1];
              }
              for(kk=0;kk<i+1;kk++)
              {
                 fprintf(file," %d ",reorder[kk]);
              }
                printf("\n")
                //reorder数组的长度是i+1;
               sum2[j]=evaldis(i+1,reorder,og);
               fprintf(file,"sum2[%d]=%d\n",j,sum2[j]);
               if(sum2[j]>sum22)
               {
                  sum22=sum2[j];
                  for(kk=1;kk<=i+1;kk++)
                    reorder1[kk]=reorder[kk];
               }  
           }               
           if(sum22>sum11)
           {
                for(kk=0;kk<i+1;kk++) 
                      rereorder[kk]=reorder1[kk];
                  sum11=sum22;
           }
           else
           {
                for(kk=0;kk<i+1;kk++) 
                      rereorder[kk]=order[kk];
           }
          for(kk=0;kk<i+1;kk++) 
             order[kk]=rereorder[kk];         
    }
    /*fprintf(file,"final order:\n");
    for(int i=0;i<n;i++)
     fprintf(file," %d ",order[i]);//最后的序列 
     fprintf(file,"\n");*/
}
void constructionPhase(int **og, int n, double a,int *ct,int *co)
{
     
      int pairor[2000][n];
      int h[N];
      int hi[N];
      int  cl=n*(n-1);
      int temp[2000];
      int flag[500];
      
      int d;
      //to flag the number we use or not "0": not used "1" :used
      memset(flag,0,sizeof(flag));
      //the temp order we need to assemble the next order we need 
      memset(temp,0,sizeof(temp));
      //the orders we need to caculate the rcl set
      memset(pairor,0,sizeof(pairor));
      //the distance
      memset(h,0,sizeof(h));
      //the position
      memset(hi,0,sizeof(hi));
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
               // pairor[k][0]=i;
               // pairor[k][1]=j;  
                k++;
            }
      }
      fprintf(file,"k=%d\n",k);
      sort(h,hi,k-1);   
      int rcl = (int)(a*cl);
      for(int i=0;i<rcl;i++)
      {
             // fprintf(file,"%d %d %d %d\n",h[i],hi[i],pairor[hi[i]][0],pairor[hi[i]][1]);
              fprintf(file,"%d %d \n",h[i],hi[i]);
              int t=(hi[i]+1)%(n-1);
              int t1=(hi[i]+1)/(n-1);
              if(t==0)
                pairor[i][0]=t1-1;
              else
                 pairor[i][0]=t1;
              if(t<pairor[i][0])
              pairor[i][1]=t-1;
              else
              pairor[i][1]=t;
              fprintf(file,"%d %d \n",pairor[i][0],pairor[i][1]);
      }
		if (rcl == 0)
			e = 0;
		else
			e = rand() % rcl; 
		temp[0]=pairor[i][0];
		temp[1]=pairor[i][1];
		//proc2(n,temp);
		flag[temp[0]]=1;
		flag[temp[1]]=1;
		for(int i=0;i<n;i++)
        {
              if(flag[i]==0)
                
        }  
      
}


/*void localSearch(int **og, int n, int too, int *soo, int *ton, int *son)
{
     
}*/
