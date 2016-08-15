#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <time.h>
#include "construction.hpp"
#include "support.hpp"
#include "fitness.hpp"
#define it 10000
int main()
{
    int J;
    int S;
    int sm[10];
    int proreq[10][200];
    int protime[10][200];
    int order[10][10][200];
    //the arrangement of jobs of the machines on one stage
    //int sorder[10][200];
    int i,j,k,ii;
    po s[200];
  	FILE *f1;
    //FILE *file;
  	srand((unsigned) time(NULL));
  	file=fopen("result\\out.txt","w");
	if((f1=fopen("input\\P10S2T01.dat","r"))==NULL)
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
	fclose(f1);
	double lower;
    lower=func_LB(J,S,sm,proreq,protime);
    fprintf(file,"lower=%lf",lower);
    /*fprintf(file,"stages=%d jobs=%d\n",S,J);
    fprintf(file,"machines:\n");
    for(i=1;i<=S;i++)
      fprintf(file,"%d\n",sm[i]);
   	for(i=1;i<=S;i++)
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
    int num[10][10]; //the number of jobs of the machines  on the stages  
    int itt;
    for(int tt=1;tt<=it;tt++)
    {     
        for(i=1;i<=S;i++)
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
        }
       /* for(i=1;i<=S;i++)
        {
            fprintf(file,"stages=%d\n",i);
            for(j=1;j<=sm[i];j++)
            {     
                //fprintf(file,"num=%d ",num[i][j]);     
                fprintf(file,"machines=%d\n",j);
                fprintf(file,"jobs=\n");
                for(k=1;k<num[i][j];k++)  
                fprintf(file,"%d ",order[i][j][k]);
                fprintf(file,"\n");
            }
            fprintf(file,"\n");
        } */ 
        int max;        
        max=procetime(S,J,sm,protime,order,num);
        fprintf(file,"maxspan=%d\n",max);
        if(lower==max)
        {
            itt=tt;
            break;
        }
        
    }
    fprintf(file,"it=%d",itt);  
    //fprintf(file,"maxspan=%d\n",max);    
    //system("pause");
    return 0;
}
