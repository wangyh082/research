#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#define NP 30/* The number of colony size (employed bees+onlooker bees)*/
#define FoodNumber NP/2 /*The number of food sources equals the half of the colony size*/
#define limit 100 /*A food source which could not be improved through "limit" trials is abandoned by its employed bee*/
#define maxCycle 5000 /*The number of cycles for foraging {a stopping criteria}*/
#define runtime 10

struct po
{
    double number;
    int pos;
};
int J;
int S;
int   sm[10];
int   ub[200],lb[200];
int   num[10][10]; //the number of jobs of the machines  on the stages 
int proreq[10][200];
int protime[10][200];
int order[10][10][200]; 
double  f[FoodNumber+5];  /*f is a vector holding objective function values associated with food sources */
double fitness[FoodNumber+5]; /*fitness is a vector holding fitness (quality) values associated with food sources*/
double trial[FoodNumber+5]; /*trial is a vector holding trial numbers through which solutions can not be improved*/
double prob[FoodNumber+5]; /*prob is a vector holding probabilities of food sources (solutions) to be chosen*/
po     temp[10][1000];
double  solution[10][1000]; /*New solution (neighbour) produced by v_{ij}=x_{ij}+\phi_{ij}*(x_{kj}-x_{ij}) j is a randomly chosen parameter and k is a randomlu chosen solution different from i*/
double ObjValSol; /*Objective function value of new solution*/
double FitnessSol; /*Fitness value of new solution*/
int neighbour, param2change; /*param2change corrresponds to j, neighbour corresponds to k in equation v_{ij}=x_{ij}+\phi_{ij}*(x_{kj}-x_{ij})*/
double GlobalMin; /*Optimum solution obtained by ABC algorithm*/
double GlobalParams[1000]; /*Parameters of the optimum solution*/
double GlobalMins[runtime+5]; /*GlobalMins holds the GlobalMin of each run in multiple runs*/
double r; /*a random number in the range [0,1)*/
double foods[FoodNumber+5][2000];


int cmp(const void *a,const void *b)
{
    po l1=*(po*)a;
    po l2=*(po*)b;
    double t=l1.number-l2.number;
    if(t>0)  return 1;
    else
      if(t<0) return -1;
    else
      {
              t=l1.pos-l2.pos;
              if(t>0) return 1;
              else return -1;
      }
}

int main()
{
    int S,J;
    srand(time(NULL));
    int i,j,k,ii;
  	FILE *f1,*file;
    file=fopen("result\\outt1.txt","w");
	if((f1=fopen("input\\P20S5T09.dat","r"))==NULL)
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
	 for(i=1;i<=S;i++)
    {
         ub[i]=sm[i]+1;
         lb[i]=1;
    }
    int kk;
    for(i=1;i<=J*S;i++)
       foods[1][i]=0.0;
    int num1=1;
    for(kk=1;kk<=S;kk++)
    {
        //for(ii=1;ii<=J;ii++)
           //Foods[index][kk][ii].number=0.0;
        for(ii=1;ii<=10;ii++)
           num[kk][ii]=1;
        for (j=1;j<=J;j++)
        {          
                r = ( (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                //fprintf(file,"r=%f\n",r);
                foods[1][num1]=r*(ub[kk]-lb[kk])+lb[kk];
                solution[kk][j]=foods[1][num1];
                num1++;
        }
        for(j=1;j<=J;j++)
        {
           temp[kk][j].number=solution[kk][j];
           temp[kk][j].pos=j;
           fprintf(file,"pos=%d number=%f\n",temp[kk][j].pos,temp[kk][j].number);
        }
        qsort(temp[kk],J+1,sizeof(temp[kk][1]),cmp);//***使用快速排序 
        fprintf(file,"temp\n");
        for(k=1;k<=J;k++)
          fprintf(file,"sort pos=%d number=%f\n",temp[kk][k].pos,temp[kk][k].number);
        for(k=1;k<=J;k++)
        {
            for(j=1;j<=sm[kk];j++)
            {
              if((int)(temp[kk][k].number)==j)
              {
                order[kk][j][num[kk][j]]=temp[kk][k].pos;
                num[kk][j]++;
                break;
              }
            }              
        }
    }
        fprintf(file,"initial\n");
         for(i=1;i<=S;i++)
        {
            fprintf(file,"stages=%d\n",i);
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
    system("pause");
    return 0;
}
