double evaldis(int n,int *order,double *p1)//evaluate the distances over the tsp problem
{
     /*fprintf(file,"*********************\n");
     	for(int i=0;i<N;i++)
	{
	 for(int j=0;j<N;j++)
	   fprintf(file,"%lf ",og[i][j]);
	   fprintf(file,"\n");
    }*/
      double d=0.0;
      for(int i=0;i<n-1;i++)
      {
         // d+=*(p2+order[i]*n+order[i+1]);
         d+=sqrt((*(p1+order[i])-*(p1+order[i+1]))*(*(p1+order[i])-*(p1+order[i+1]))+(*(p1+N+order[i])-*(p1+N+order[i+1]))*(*(p1+N+order[i])-*(p1+N+order[i+1])));
         //d+=og[order[i]][order[i+1]];
      }
      //d+=*(p2+order[n-1]*n+order[0]);
      d+=sqrt((*(p1+order[n-1])-*(p1+order[0]))*(*(p1+order[n-1])-*(p1+order[0]))+(*(p1+N+order[n-1])-*(p1+N+order[0]))*(*(p1+N+order[n-1])-*(p1+N+order[0])));
      //d+=og[order[n-1]][order[0]];
      return d;
}

void proc(int n,int *order,int k,double *p1)
{
    double sum11=0;//初始的序列和
    double sum2[2000];//比较的和 
    double sum22;
    int i,j,ii,jj,kk;
    int p;
    int temp;
    memset(reorder,0,sizeof(reorder));
    memset(rereorder,0,sizeof(rereorder));
    memset(reorder1,0,sizeof(reorder1));
    for(i=k-2;i<k-1;i++)
    {
          for(kk=0;kk<n;kk++)
             reorder[kk]=0;
          sum11=evaldis(i+2,order,p1);
          //fprintf(file,"sum11=*%lf*\n",sum11);
          temp=order[i+1];
          sum22=10000000000.0;
          for(j=0;j<=i;j++)
          {             
              for(kk=0;kk<=j;kk++)
                sum2[kk]=0;
              reorder[j]=temp;
              if(j==0) jj=0;
              else
              {
                for(jj=0;jj<=j-1;jj++)
                   reorder[jj]=order[jj];
              }
                p=j;
              for(ii=0;ii<=i-jj;ii++)
              {
                 ++p;
                 reorder[p]=order[p-1];
              }
             /* for(kk=0;kk<=i+1;kk++)
              {
                 fprintf(file," %d ",reorder[kk]);
              }
                fprintf(file,"\n");*/
                //reorder数组的长度是i+2;
               sum2[j]=evaldis(i+2,reorder,p1);
               //fprintf(file,"sum2[%d]=%lf\n",j,sum2[j]);
               if(sum2[j]<sum22)
               {
                  sum22=sum2[j];
                  for(kk=0;kk<=i+1;kk++)
                    reorder1[kk]=reorder[kk];
               }  
           }               
           if(sum22<sum11)
           {
                for(kk=0;kk<i+2;kk++) 
                      rereorder[kk]=reorder1[kk];
                  sum11=sum22;
           }
           else
           {
                for(kk=0;kk<i+2;kk++) 
                      rereorder[kk]=order[kk];
           }
          for(kk=0;kk<i+2;kk++) 
             order[kk]=rereorder[kk];         
    }
  /*  fprintf(file,"final order:\n");
    for(int i=0;i<k;i++)
     fprintf(file," %d ",order[i]);//最后的序列 
     fprintf(file,"\n");*/
}

void induce(int n,int *order)
{
      int i,temp;
      int flag[N];
      for(i=0;i<n;i++)
     {
       order[i]=0;
       flag[i]=0;//表示这个数未生成 
     }
     for(i=0;i<n;i++)
     {     
        temp=rand()%n;
        while(flag[temp]==1)
         temp=rand()%n;
        order[i]=temp;
        flag[temp]=1;
     } 
}

/*void BR(int n,int *ini,double *p2)
{
             int cityA,cityB,temp;
             int city1,city2;
             double diss=100000000.0;
             double y,df;
          for(int j=0;j<n*(n-1);j++)
          {
                cityA=rand()%(n-2)+1;
loopC:	;
				cityB=rand()%(n-2)+1;
				if(cityA==cityB)
					goto loopC;
				if(cityA>cityB)
				{
					temp=cityA;
					cityA=cityB;
					cityB=temp;
				}
				df=*(p2+ini[cityA-1]*n+ini[cityB])
					+*(p2+ini[cityA]*n+ini[cityB+1])
					-*(p2+ini[cityA-1]*n+ini[cityA])
					-*(p2+ini[cityB]*n+ini[cityB+1]);
				if(df<diss)
				{
					diss=df;
					city1=cityA;
					city2=cityB;
				}
                if(diss<0)
                {
                   //fprintf(file,"good\n");
                   if((city1+1)==city2)
            		{
            			temp=ini[city1];
            			ini[city1]=ini[city2];
            			ini[city2]=temp;
            		}
            		else 
            		{
            			for(int i=city1;i<=(city1+city2)/2;i++)
            			{
            				temp=ini[i];
            				ini[i]=ini[city2-i+city1];
            				ini[city2-i+city1]=temp;
            			}
            		}
                }
           }
           //return diss;
}*/
