void proc1(int n,int *order,double *p2)
{    
    double sum11;//初始的序列和
    double sum2[n];//比较的和 
    double sum22;
    int i,j,ii,jj,kk;
    int p;
    int temp;
    memset(reorder,0,sizeof(reorder));
    memset(rereorder,0,sizeof(rereorder));
    memset(reorder1,0,sizeof(reorder1));
    for(i=0;i<n-1;i++)
    {
          for(kk=0;kk<n;kk++)
             reorder[kk]=0;
          sum11=evaldis(i+2,order,p2);
         // fprintf(file,"sum11=*%lf*\n",sum11);
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
              /*for(kk=0;kk<=i+1;kk++)
              {
                 fprintf(file," %d ",reorder[kk]);
              }
                fprintf(file,"\n");*/
                //reorder数组的长度是i+2;
               sum2[j]=evaldis(i+2,reorder,p2);
              // fprintf(file,"sum2[%d]=%lf\n",j,sum2[j]);
               if(sum2[j]<sum22)
               {
                  sum22=sum2[j];
                  for(kk=0;kk<=i+1;kk++)
                    reorder1[kk]=reorder[kk];
               }  
           } 
           //fprintf(file,"sum22=%lf\n",sum22);              
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
   /* fprintf(file,"final order:\n");
    for(int i=0;i<n;i++)
     fprintf(file," %d ",order[i]);//最后的序列 
     fprintf(file,"\n");*/
}

void insert(int *a,int n,int c,int d)//insert c position's value into the d position 
{
    int temp;
    temp=a[c];
    for(int i=c;i>=d;i--)
       a[i+1]=a[i];
       a[d]=temp;
       //printf("%d ",b[i]);
      // printf("\n");
}

