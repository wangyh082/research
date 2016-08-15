/* ABC algorithm coded using C programming language */

/* Artificial Bee Colony (ABC) is one of the most recently defined algorithms by Dervis Karaboga in 2005, 
motivated by the intelligent behavior of honey bees. */

/* Referance Papers*/

/*D. Karaboga, AN IDEA BASED ON HONEY BEE SWARM FOR NUMERICAL OPTIMIZATION,TECHNICAL REPORT-TR06, Erciyes University, Engineering Faculty, Computer Engineering Department 2005.*/

/*D. Karaboga, B. Basturk, A powerful and Efficient Algorithm for Numerical Function Optimization: Artificial Bee Colony (ABC) Algorithm, Journal of Global Optimization, Volume:39, Issue:3,pp:459-171, November 2007,ISSN:0925-5001 , doi: 10.1007/s10898-007-9149-x */

/*D. Karaboga, B. Basturk, On The Performance Of Artificial Bee Colony (ABC) Algorithm, Applied Soft Computing,Volume 8, Issue 1, January 2008, Pages 687-697. */

/*D. Karaboga, B. Akay, A Comparative Study of Artificial Bee Colony Algorithm,  Applied Mathematics and Computation, 214, 108-132, 2009. */

/*Copyright ? 2009 Erciyes University, Intelligent Systems Research Group, The Dept. of Computer Engineering*/

/*Contact:
Dervis Karaboga (karaboga@erciyes.edu.tr )
Bahriye Basturk Akay (bahriye@erciyes.edu.tr)
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "support.hpp"
#include "fitness.hpp"



/* Control Parameters of ABC algorithm*/
#define NP 30/* The number of colony size (employed bees+onlooker bees)*/
#define FoodNumber NP/2 /*The number of food sources equals the half of the colony size*/
#define limit 100 /*A food source which could not be improved through "limit" trials is abandoned by its employed bee*/
#define maxCycle 1 /*The number of cycles for foraging {a stopping criteria}*/

/* Problem specific variables*/ 
//#define D 50 /*The number of parameters of the problem to be optimized*/
//#define lb -5.12 /*lower bound of the parameters. */
//#define ub 5.12 /*upper bound of the parameters. lb and ub can be defined as arrays for the problems of which parameters have different bounds*/


#define runtime 1  /*Algorithm can be run many times in order to see its robustness*/
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
po    Foods[FoodNumber][10][1000]; /*Foods is the population of food sources. Each row of Foods matrix is a vector holding D parameters to be optimized. The number of rows of Foods matrix equals to the FoodNumber*/
double   f[FoodNumber];  /*f is a vector holding objective function values associated with food sources */
double fitness[FoodNumber]; /*fitness is a vector holding fitness (quality) values associated with food sources*/
double trial[FoodNumber]; /*trial is a vector holding trial numbers through which solutions can not be improved*/
double prob[FoodNumber]; /*prob is a vector holding probabilities of food sources (solutions) to be chosen*/
po  solution[10][1000]; /*New solution (neighbour) produced by v_{ij}=x_{ij}+\phi_{ij}*(x_{kj}-x_{ij}) j is a randomly chosen parameter and k is a randomlu chosen solution different from i*/
double ObjValSol; /*Objective function value of new solution*/
double FitnessSol; /*Fitness value of new solution*/
int neighbour, param2change; /*param2change corrresponds to j, neighbour corresponds to k in equation v_{ij}=x_{ij}+\phi_{ij}*(x_{kj}-x_{ij})*/
double GlobalMin; /*Optimum solution obtained by ABC algorithm*/
//double GlobalParams[1000]; /*Parameters of the optimum solution*/
double GlobalMins[runtime]; /*GlobalMins holds the GlobalMin of each run in multiple runs*/
double r; /*a random number in the range [0,1)*/

/*a function pointer returning double and taking a D-dimensional array as argument */
/*If your function takes additional arguments then change function pointer definition and lines calling "...=function(solution);" in the code*/
//typedef void (*FunctionCallback)(int n,int m,po s[200]); 

/*benchmark functions 
double sphere(double sol[D]);
double Rosenbrock(double sol[D]);
double Griewank(double sol[D]);
double Rastrigin(double sol[D]);*/

/*Write your own objective function name instead of sphere*/
//FunctionCallback function = &procetime;

/*Fitness function*/
double CalculateFitness(double fun)
{
	 double result=0;
	 if(fun>=0)
	 {
		 result=1/(fun+1);
	 }
	 else
	 {
		 result=1+fabs(fun);
	 }
	 return result;
}

/*The best food source is memorized*/
void MemorizeBestSource()
{
    int i,j;    
	for(i=1;i<=FoodNumber;i++)
	{
    	if (f[i]<GlobalMin)
   		{
            GlobalMin=f[i];
            /*for(j=0;j<S*J;j++)
               GlobalParams[j]=Foods[i][j].number;*/
        }
	}
	//fprintf(file,"GlobalMin=%f\n",GlobalMin);
}

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
/*Variables are initialized in the range [lb,ub]. If each parameter has different range, use arrays lb[j], ub[j] instead of lb and ub */
/* Counters of food sources are also initialized in this function*/
void init(int index)
{
    int i,j,kk,k,ii;
    /*for(i=1;i<=S;i++)
    {       
         fprintf(file,"ub[%d]=%d lb[%d]=%d\n",i,ub[i],i,lb[i]);
    }*/
    for(kk=1;kk<=S;kk++)
    {
        for(ii=1;ii<=J;ii++)
           Foods[index][kk][ii].number=0.0;
        for(ii=1;ii<=10;ii++)
           num[kk][ii]=1;
        for (j=1;j<=J;j++)
        {          
                r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                //fprintf(file,"r=%f\n",r);
                Foods[index][kk][j].number=r*(ub[kk]-lb[kk])+lb[kk];
                Foods[index][kk][j].pos=j;  
                solution[kk][j].number=Foods[index][kk][j].number;
                solution[kk][j].pos=j;
        }
        qsort(Foods[index][kk],J+1,sizeof(Foods[index][kk][1]),cmp);//***使用快速排序 
        for(k=1;k<=J;k++)
        {
            for(j=1;j<=sm[kk];j++)
            {
              if((int)(Foods[index][kk][k].number)==j)
              {
                order[kk][j][num[kk][j]]=Foods[index][kk][k].pos;
                num[kk][j]++;
                break;
              }
            }              
        }
     }
         /*fprintf(file,"initial\n");
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
        } */ 
        f[index]= procetime(S,J,sm,protime,order,num);
	    fitness[index]=CalculateFitness(f[index]);
	    trial[index]=0;
	   // fprintf(file,"f[%d]=%f\n",index,f[index]);
}
//change into 2 dimensional and the array begin from 1 

/*All food sources are initialized */
void initial()
{
	int i;
	for(i=1;i<=FoodNumber;i++)
	{
	   init(i);
	}
	GlobalMin=f[1];
    /*for(i=0;i<D;i++)
    GlobalParams[i]=Foods[0][i];*/
}

void SendEmployedBees()
//雇佣蜂，引领蜂 
{
   int i,j,kk,k,ii;
  /*Employed Bee Phase*/
   for (i=1;i<=FoodNumber;i++)
  {
               r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
               neighbour=(int)(r*(FoodNumber-1)+1);
               //fprintf(file,"neighbour:\n %d\n",neighbour);
               while(neighbour==i)
               {
                    r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                    neighbour=(int)(r*(FoodNumber-1)+1);
               }
                for(kk=1;kk<=S;kk++)
               {
                    for(ii=1;ii<=10;ii++)
                      num[kk][ii]=1;
                    /*The parameter to be changed is determined randomly*/
                    r = ((double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                    param2change=(int)(r*(J-1)+1);
                    /*A randomly chosen solution is used in producing a mutant solution of the solution i*/
                    /*r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                    neighbour=(int)(r*FoodNumber);*/
                    
                    /*Randomly selected solution must be different from the solution i*/        
                    /*while(neighbour==i)
                    {
                        r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                        neighbour=(int)(r*FoodNumber);
                    }*/
                    /*fprintf(file,"param2change:\n %d\n",param2change);
                    for(j=1;j<=J;j++)
                    {
                        solution[kk][j].number=Foods[i][kk][j].number;
                        solution[kk][j].pos=Foods[i][kk][j].pos;
                    } 
                    fprintf(file,"1:\n");
                    for(j=1;j<=J;j++) 
                    {
                      fprintf(file,"solution.postion=%d solution.number=%f ",solution[kk][j].pos,solution[kk][j].number);                      
                    }
                    fprintf(file,"\n"); */
                    /*v_{ij}=x_{ij}+\phi_{ij}*(x_{kj}-x_{ij}) */
                    /* fprintf(file,"1:\n");
                     fprintf(file,"solution=%f\n",solution[kk][param2change].number);*/
                    r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                    solution[kk][param2change].number=Foods[i][kk][param2change].number+(Foods[i][kk][param2change].number-Foods[neighbour][kk][param2change].number)*(r-0.5)*2;
                     /*fprintf(file,"2:\n");
                     fprintf(file,"solution=%f\n",solution[kk][param2change].number);*/
                    /*if generated parameter value is out of boundaries, it is shifted onto the boundaries*/
                    while (solution[kk][param2change].number<lb[kk])
                    {
                        r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                        solution[kk][param2change].number=r*(ub[kk]-lb[kk])+lb[kk];
                    }
                   while (solution[kk][param2change].number>=ub[kk])
                   {
                        r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                        solution[kk][param2change].number=r*(ub[kk]-lb[kk])+lb[kk];
                   }
                  /* fprintf(file,"2:\n");
                     for(j=1;j<=J;j++) 
                    {
                      fprintf(file,"solution.postion=%d solution.number=%f ",solution[kk][j].pos,solution[kk][j].number);                      
                    }
                    fprintf(file,"\n");*/
                    qsort(solution[kk],J+1,sizeof(solution[kk][1]),cmp);//***使用快速排序 
                   /* fprintf(file,"3:\n");
                     for(j=1;j<=J;j++) 
                    {
                      fprintf(file,"solution.postion=%d solution.number=%f ",solution[kk][j].pos,solution[kk][j].number);                      
                    }
                    fprintf(file,"\n");*/
                    for(k=1;k<=J;k++)
                    {
                        for(j=1;j<=sm[kk];j++)
                        {
                          if((int)(solution[kk][k].number)==j)
                          {
                            order[kk][j][num[kk][j]]=solution[kk][k].pos;
                            num[kk][j]++;
                            break;
                          }
                        }              
                    }
              }
              fprintf(file,"SendEmployedBees:\n");
              for(ii=1;ii<=S;ii++)
            {
                fprintf(file,"stages=%d\n",ii);
                for(j=1;j<=sm[ii];j++)
                {     
                    fprintf(file,"num=%d ",num[ii][j]);     
                    fprintf(file,"machines=%d\n",j);
                    fprintf(file,"jobs=\n");
                    for(k=1;k<num[ii][j];k++)  
                    fprintf(file,"%d ",order[ii][j][k]);
                    fprintf(file,"\n");
                }
                fprintf(file,"\n");
            }  
             ObjValSol= procetime(S,J,sm,protime,order,num);
             //fprintf(file,"ObjValSol=%f\n",ObjValSol);
	         FitnessSol=CalculateFitness(ObjValSol);
            /*a greedy selection is applied between the current solution i and its mutant*/
                if (FitnessSol>fitness[i])
                {
                /*If the mutant solution is better than the current solution i, replace the solution with the mutant and reset the trial counter of solution i*/
                    trial[i]=0;
                    for(kk=1;kk<=S;kk++)
                    {
                        for(j=1;j<=J;j++)
                        {
                            Foods[i][kk][j].number=solution[kk][j].number;
                            Foods[i][kk][j].pos=solution[kk][j].pos;
                        }
                    }
                    f[i]=ObjValSol;
                    fitness[i]=FitnessSol;
                }
                else
                {   /*if the solution i can not be improved, increase its trial counter*/
                    trial[i]=trial[i]+1;
                }
  }
            /*end of employed bee phase*/
}
//change into 2 dimensional and the array begin from 1

/* A food source is chosen with the probability which is proportioal to its quality*/
/*Different schemes can be used to calculate the probability values*/
/*For example prob(i)=fitness(i)/sum(fitness)*/
/*or in a way used in the metot below prob(i)=a*fitness(i)/max(fitness)+b*/
/*probability values are calculated by using fitness values and normalized by dividing maximum fitness value*/
void CalculateProbabilities()
{
     int i;
     double maxfit;
     maxfit=fitness[1];
     for (i=2;i<=FoodNumber;i++)
     {
        if (fitness[i]>maxfit)
        maxfit=fitness[i];
     }

     for (i=1;i<=FoodNumber;i++)
     {
         prob[i]=(0.9*(fitness[i]/maxfit))+0.1;
         //fprintf(file,"prob[%d]=%f\n",i,prob[i]);
     }
}

void SendOnlookerBees()
//跟随蜂 
{

          int i,j,t,kk,k,ii;
          i=1;
          t=0;
          /*onlooker Bee Phase*/
          while(t<FoodNumber)
        {

                r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
              
                if(r<prob[i]) /*choose a food source depending on its probability to be chosen*/
                {        
                       t++;
                       r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                       neighbour=(int)(r*(FoodNumber-1)+1);
                       while(neighbour==i)
                       {
                            r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                            neighbour=(int)(r*(FoodNumber-1)+1);
                       }
                       for(kk=1;kk<=S;kk++)
                       {
                            for(ii=1;ii<=10;ii++)
                              num[kk][ii]=1;
                            /*The parameter to be changed is determined randomly*/
                            r = ((double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                            param2change=(int)(r*(J-1)+1);
                            /*A randomly chosen solution is used in producing a mutant solution of the solution i*/
                            /*r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                            neighbour=(int)(r*FoodNumber);
                            
                            /*Randomly selected solution must be different from the solution i*/        
                            /*while(neighbour==i)
                            {
                                r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                                neighbour=(int)(r*FoodNumber);
                            }*/
                          
                            for(j=1;j<=J;j++)
                            {
                                solution[kk][j].number=Foods[i][kk][j].number;
                                solution[kk][j].pos=Foods[i][kk][j].pos;
                            }   
                            /*v_{ij}=x_{ij}+\phi_{ij}*(x_{kj}-x_{ij}) */
                            r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                            solution[kk][param2change].number=Foods[i][kk][param2change].number+(Foods[i][kk][param2change].number-Foods[neighbour][kk][param2change].number)*(r-0.5)*2;
                    
                            /*if generated parameter value is out of boundaries, it is shifted onto the boundaries*/
                            while (solution[kk][param2change].number<lb[kk])
                            {
                                r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                                solution[kk][param2change].number=r*(ub[kk]-lb[kk])+lb[kk];
                            }
                           while (solution[kk][param2change].number>=ub[kk])
                           {
                                r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                                solution[kk][param2change].number=r*(ub[kk]-lb[kk])+lb[kk];
                           }
                            qsort(solution[kk],J+1,sizeof(solution[kk][1]),cmp);//***使用快速排序 
                             for(k=1;k<=J;k++)
                            {
                                for(j=1;j<=sm[kk];j++)
                                {
                                  if((int)(solution[kk][k].number)==j)
                                  {
                                    order[kk][j][num[kk][j]]=solution[kk][k].pos;
                                    num[kk][j]++;
                                    break;
                                  }
                                }              
                            }
                    }
                    /*fprintf(file,"SendOnlookerBees:\n");
                    for(int ii=1;ii<=S;ii++)
                    {
                        fprintf(file,"stages=%d\n",ii);
                        for(j=1;j<=sm[ii];j++)
                        {     
                            fprintf(file,"num=%d ",num[ii][j]);     
                            fprintf(file,"machines=%d\n",j);
                            fprintf(file,"jobs=\n");
                            for(k=1;k<num[ii][j];k++)  
                            fprintf(file,"%d ",order[ii][j][k]);
                            fprintf(file,"\n");
                        }
                        fprintf(file,"\n");
                    } */ 
                     ObjValSol= procetime(S,J,sm,protime,order,num);
        	         FitnessSol=CalculateFitness(ObjValSol);
                    /*a greedy selection is applied between the current solution i and its mutant*/
                        if (FitnessSol>fitness[i])
                        {
                        /*If the mutant solution is better than the current solution i, replace the solution with the mutant and reset the trial counter of solution i*/
                            trial[i]=0;
                            for(kk=1;kk<=S;kk++)
                            {
                                for(j=1;j<=J;j++)
                                {
                                    Foods[i][kk][j].number=solution[kk][j].number;
                                    Foods[i][kk][j].pos=solution[kk][j].pos;
                                }
                            }
                            f[i]=ObjValSol;
                            fitness[i]=FitnessSol;
                        }
                        else
                        {   /*if the solution i can not be improved, increase its trial counter*/
                            trial[i]=trial[i]+1;
                        }
           }
          /*if */
            i++;
            if (i==FoodNumber+1)
            i=1;
      }/*while*/
        /*end of onlooker bee phase     */
}
//change into 2 dimensional and the array begin from 1
/*determine the food sources whose trial counter exceeds the "limit" value. In Basic ABC, only one scout is allowed to occur in each cycle*/
void SendScoutBees()
//侦察蜂 
{
    int maxtrialindex,i;
    maxtrialindex=1;
    for (i=2;i<=FoodNumber;i++)
    {
       if (trial[i]>trial[maxtrialindex])
        maxtrialindex=i;
    }
    if(trial[maxtrialindex]>=limit)//当大于尝试次数时需要重新初始化一个 
    {
    	init(maxtrialindex);
    }
}
//the array begin from 1

/*Main program of the ABC algorithm*/
int main()
{
    int iter,run;
    double mean;
    mean=0;
    srand(time(NULL));
    int i,j,k,ii;
    po s[200];
  	FILE *f1;
    file=fopen("result\\out17.txt","w");
	if((f1=fopen("input\\P10S2T03.dat","r"))==NULL)
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
    fprintf(file,"lower=%lf\n",lower);
    for(i=1;i<=S;i++)
    {
         ub[i]=sm[i]+1;
         lb[i]=1;
    }
    double mmin=100000000.0;
    for(run=1;run<=runtime;run++)
    {    
        initial();
        MemorizeBestSource();
        for (iter=1;iter<=maxCycle;iter++) //迭代次数 
        {
            SendEmployedBees();//雇佣蜂时期 
            CalculateProbabilities();//计算可能性 
            //SendOnlookerBees();//跟随蜂时期 
            MemorizeBestSource();//记录最好的蜂源  
            SendScoutBees();//如果到达尝试次数后，就到侦察蜂时期 
        }
       /* for(j=0;j<D;j++)
		{
			printf("GlobalParam[%d]: %f\n",j+1,GlobalParams[j]);
		}*/
        fprintf(file,"%d. run: %f \n",run,GlobalMin);
        GlobalMins[run]=GlobalMin;
        mean=mean+GlobalMin;
        if(GlobalMin<mmin)
          mmin=GlobalMin;
    }
    double pd;
    pd=PD(mmin,lower);
    mean=mean/runtime;
    fprintf(file,"Means of %d runs: %f\n",runtime,mean);
    fprintf(file,"Mins  of %d runs: %f\n",runtime,mmin);
    fprintf(file,"PD of this time: %f\n",pd);
    //fprintf(file,"maxspan=%d\n",max);    
    //system("pause");
    return 0;
}
////change into 2 dimensional and the array begin from 1
//delete the functions
