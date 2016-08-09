int reorder[1000];//每次插入后的次序
int rereorder[1000];//最好的序列；
int reorder1[1000]; 

int  evaldis(int n,int *order)//evaluate the distances over the tsp problem
{
      int d=0;
      for(int i=0;i<n-1;i++)
      {
          d+=og[order[i]][order[i+1]];
      }
      d+=og[order[n-1]][order[0]];
      return d;
}

void proc(int n,int *order,int k)
{
    int sum11;//初始的序列和
    int sum2[2000];//比较的和 
    int sum22;
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
          sum11=evaldis(i+2,order);
          //fprintf(file,"sum11=*%d*\n",sum11);
          temp=order[i+1];
          sum22=0;
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
               sum2[j]=evaldis(i+2,reorder);
             //  fprintf(file,"sum2[%d]=%d\n",j,sum2[j]);
               if(sum2[j]>sum22)
               {
                  sum22=sum2[j];
                  for(kk=0;kk<=i+1;kk++)
                    reorder1[kk]=reorder[kk];
               }  
              // for(kk=1;kk<=i+1;kk++)
                 // reorder[kk]=reorder1[kk];  
           }               
           if(sum22>sum11)
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
