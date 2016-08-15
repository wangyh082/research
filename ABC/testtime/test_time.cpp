#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <time.h>
int sm[10];
int proreq[10][200];
int protime[10][200];
int order[10][10][200];
int num[10][10];
int c[10][200];
FILE *file;
int max(int x, int y)
// returns the maximum of the two arguments
//
// input arguments:
// x = integer
// y = integer
{
	if (x > y)
		return x;
	else
		return y;
} //max
void procetime1(int i,int J,int sm[20],int protime[10][200],int order[10][10][200],int num[10][10])//the first stage
{
    for(int j=1;j<=J;j++)
	fprintf(file,"%d ",protime[i][j]);
	fprintf(file,"\n");
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
   for(int j=1;j<=J;j++)
    {
        fprintf(file,"%d ",c[i][j]);
        
    }
    fprintf(file,"\n");   
}

void  procetime2(int stage,int J,int sm[20],int protime[10][200],int order[10][10][200],int num[10][10])//the other stage
{
    for(int j=1;j<=J;j++)
		fprintf(file,"%d ",protime[stage][j]);
		fprintf(file,"\n");
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
    for(int j=1;j<=J;j++)
    {
        fprintf(file,"%d ",c[stage][j]);
    }
      fprintf(file,"\n"); 
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
        fprintf(file,"%d ",c[stage][i]);
        if(c[stage][i]>max)
         max=c[stage][i];
    }
    return max;
}

int main()
{
    int J;
    int S;
    
    //the arrangement of jobs of the machines on one stage
    //int sorder[10][200];
    int i,j,k,ii;
    //po s[200];
  	FILE *f1;
    //FILE *file;
  	srand((unsigned) time(NULL));
  	file=fopen("out.txt","w");
	if((f1=fopen("P10S2T01.dat","r"))==NULL)
	{
		exit(0);
	}
	fscanf(f1,"jobs %d\n",&J);
	fscanf(f1,"stage %d\n",&S);
	fscanf(f1,"machines %d",&sm[1]);
	for(i=2;i<=S-1;i++)
	fscanf(f1," %d",&sm[i]);
	fscanf(f1," %d\n",&sm[S]);
	fscanf(f1,"*Pro_req*\n");
	for(i=1;i<=S;i++)
	{
        for(j=1;j<=J;j++)
		fscanf(f1,"%d ",&proreq[i][j]);
		fscanf(f1,"\n");
	}
	fscanf(f1,"*Pro_time*\n");
	for(i=1;i<=S;i++)
	{
        for(j=1;j<=J;j++)
		fscanf(f1,"%d ",&protime[i][j]);
		fscanf(f1,"\n");
	}
	//fclose(f1);
    fprintf(file,"stages=%d jobs=%d\n",S,J);
    fprintf(file,"machines:\n");
    for(i=1;i<=S;i++)
      fprintf(file,"%d\n",sm[i]);
   	/*for(i=1;i<=S;i++)
	{
        for(j=1;j<=J;j++)
		fprintf(file,"%d ",proreq[i][j]);
		fprintf(file,"\n");
	}
	for(i=1;i<=S;i++)
	{
        for(j=1;j<=J;j++)
		fprintf(file,"%d ",protime[i][j]);
		fprintf(file,"\n");
	}
	for(i=1;i<=S;i++)
	{
	  induce(J,order[i]);
	  norder(J,sm[i],sorder[i]);
	  for(j=1;j<=J;j++) //the job is from 1 to J
       fprintf(file,"%d ",order[i][j]);
       fprintf(file,"\n");
      for(j=1;j<=sm[i];j++)//the number is from 0 to J
         fprintf(file,"%d ",sorder[i][j]);
         fprintf(file,"\n");     
    }*/    
     //the number of jobs of the machines  on the stages
    /*for(i=1;i<=S;i++)
    {
       for(ii=1;ii<=J;ii++)
       s[ii].number=0.0;
       for(ii=1;ii<=10;ii++)
       num[i][ii]=1;
       proc(J,sm[i],s);           
       for(k=1;k<=J;k++)
       {
            for(j=1;j<=sm[i];j++)
            {
              if((int)(s[k].number)==j)
              {
                order[i][j][num[i][j]]=s[k].pos;
                num[i][j]++;
                break;
              }
            }
            
        }
    }*/
    for(i=1;i<=S;i++)
    {
      for(j=1;j<=sm[i];j++)
      fscanf(f1,"%d ",&num[i][j]);
    }
    fscanf(f1,"\n");
    for(i=1;i<=S;i++)
    {
        for(j=1;j<=sm[i];j++)
        {     
            for(k=1;k<num[i][j];k++)  
            fscanf(f1,"%d ",&order[i][j][k]);
           // fscanf(f1,"\n");
        }
        //fprintf(file,"\n");
    }
    //fscanf(f1,"\n");  
    for(i=1;i<=S;i++)
    {
        for(j=1;j<=sm[i];j++)
        {     
            fprintf(file,"num=%d ",num[i][j]);     
            fprintf(file,"machines=%d\n",j);
            fprintf(file,"jobs=\n");
            for(k=1;k<num[i][j];k++)  
            fprintf(file,"%d ",order[i][j][k]);
            fprintf(file,"\n");
        }
        fprintf(file,"\n");
    }  
    int max;
    max=procetime(S,J,sm,protime,order,num);
    fprintf(file,"maxspan=%d\n",max);
    //system("pause");
    return 0;
}
