FILE *file;
double func_LB(int J,int S,int sm[20],int proreq[10][200],int protime[10][200])
{
   double max=0.0;
   double min1,sum1,min2,sum2,sum3;
   for(int i=1;i<=S;i++)
   {
      double sum=0.0; 
      min1=10000000000.0;
      for(int j=1;j<=J;j++)
      {        
        sum1=0;
        for(int k=1;k<=i-1;k++)
         sum1+=protime[k][j];
         if(sum1<min1)
         min1=sum1;
      }
      sum+=min1;
      sum3=0;
      for(int k=1;k<=J;k++)
      sum3+=protime[i][k]*1;
      sum+=sum3*1.0/sm[i]*1.0;
      min2=10000000000.0;
      for(int j=1;j<=J;j++)
      {        
        sum2=0;
        for(int k=i+1;k<=S;k++)
         sum2+=protime[k][j];
         if(sum2<min2)
         min2=sum2;
      }
      sum+=min2;
      if(sum>max)
        max=sum;
   }
   return max;
}

double PD(double bestcmax,double lowerbound)
{
       double pd;
       pd=(bestcmax-lowerbound)*1.0*100/lowerbound*1.0;
       return pd;
}

int c[10][200];//the completed time of one job on the stages

void procetime1(int i,int J,int sm[20],int protime[10][200],int order[10][10][200],int num[10][10])//the first stage
{
    /*for(int j=1;j<=J;j++)
	fprintf(file,"%d ",protime[i][j]);
	fprintf(file,"\n");*/
    for(int j=1;j<=sm[i];j++)
    {
      //fprintf(file,"num=%d\n",num[i][j]);
      if(num[i][j]>=2)
      {
          c[i][order[i][j][1]]=protime[i][order[i][j][1]];
          if(num[i][j]>2)
          {
            for(int k=2;k<num[i][j];k++)
            c[i][order[i][j][k]]=c[i][order[i][j][k-1]]+protime[i][order[i][j][k]];
          }
      }
    }  
   /* for(int j=1;j<=J;j++)
    {
        fprintf(file,"%d ",c[i][j]);
        
    }
    fprintf(file,"\n");  */  
}

void  procetime2(int stage,int J,int sm[20],int protime[10][200],int order[10][10][200],int num[10][10])//the other stage
{
   /* for(int j=1;j<=J;j++)
		fprintf(file,"%d ",protime[stage][j]);
		fprintf(file,"\n");*/
    for(int j=1;j<=sm[stage];j++)
    {
        //fprintf(file,"num=%d\n",num[stage][j]);
        if(num[stage][j]>=2)
        {
            c[stage][order[stage][j][1]]=c[stage-1][order[stage][j][1]]+protime[stage][order[stage][j][1]];
            if(num[stage][j]>2)
            {
              for(int k=2;k<num[stage][j];k++)
              c[stage][order[stage][j][k]]=max(c[stage-1][order[stage][j][k]],c[stage][order[stage][j][k-1]])+protime[stage][order[stage][j][k]];
            }
        }
    }
    /*for(int j=1;j<=J;j++)
    {
        fprintf(file,"%d ",c[stage][j]);
    }
      fprintf(file,"\n"); */
}

int  procetime(int stage,int J,int sm[20],int protime[10][200],int order[10][10][200],int num[10][10])
{
    memset(c,0,sizeof(c));
    procetime1(1,J,sm,protime,order,num);
    for(int i=2;i<=stage;i++)
    {
        procetime2(i,J,sm,protime,order,num);
    }
    int max=0;
    for(int i=1;i<=J;i++)
    {
        //fprintf(file,"%d ",c[stage][i]);
        if(c[stage][i]>max)
         max=c[stage][i];
    }
    return max;
}
