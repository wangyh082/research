//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <math.h> 
#include <string.h>
#include <stdio.h> 
#include <time.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define  TS		10 //the outer iteration times 
#define  N	    200
#define  OPT	29437
#define  it     1// the iteration times

//int pairor[N*(N-1)][N];
int cpSO[10][N];
double cpTO[10];
int temp2[N];
//int temp1[N][N];
int temp[N];
//double h[N*N];
//int hi[N*N];
FILE *file;
int reorder[N];//每次插入后的次序
int rereorder[N];//最好的序列；
int reorder1[N];
double *ptd=new double[N*N];
//double og[N][N];
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "support.h"
//#include "heap sort.h"
#include "initial_support.h"
#include "components1.h"

int main()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	file=fopen("out53.txt","w");
	int i,j,k,times,times1;
	int temp;
	int ini[N],inim[N];
	int cityA,cityB,cityC;
	int city1,city2,city3;
	int initial,select,mid,greedy;
	int tv,two,tg;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double *ptf=new double[2*N];
	double hh,gg;
	double xv,yv;
	//double period;
	//period=1000.0*pow(1.0*N,0.8);
	//printf("%lf\n",period/1000);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
	double solution;
	double t,var;
	double y;
	double randp,diss,df,sum;
	double maxx,minn,current_temp;
	//double a;

//	var=(160000.0*pow(1.0*N,0.05)-1.0)/(160000.0*pow(1.0*N,0.05));
//	fprintf(file,"var1=:%9.9lf\n",var);
//	var=(80000.0*pow(1.0*N,0.05)-1.0)/(80000.0*pow(1.0*N,0.05));
//	fprintf(file,"var2=:%9.9lf\n",var);
	srand((unsigned) time(NULL));//random
	fprintf(file,"N=%d OPT=%d\n",N,OPT);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double *p1;//p1 store the x and y coordinate
	p1=ptf;
	FILE *f1;
	if((f1=fopen("kroB200.tsp","r"))==NULL)
	{
		exit(0);
	}
	for(i=0;i<2;i++)
	{
		for(j=0;j<N;j++)
		{
			*(p1+i*N+j)=0.0;
		}
	}//initial p1
	for(i=0;i<N;i++)
	{
		fscanf(f1,"%d %lf %lf\n",&j,&xv,&yv);
		*(p1+j-1)=xv;
		*(p1+j-1+N)=yv;
	}
	fclose(f1);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//a=n2a(N);
	//fprintf(file,"a=%lf\n",a);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    double *p2;
	p2=ptd;
	for(i=0;i<N;i++)
	{
		*(p2+i*N+i)=0;
	}
	for(i=0;i<N;i++)
	{
		for(j=i+1;j<N;j++)
		{
			*(p2+i*N+j)=sqrt((*(p1+i)-*(p1+j))*(*(p1+i)-*(p1+j))+(*(p1+N+i)-*(p1+N+j))*(*(p1+N+i)-*(p1+N+j)));
		}
	}
	for(i=0;i<N;i++)
	{
		for(j=i+1;j<N;j++)
		{
			*(p2+j*N+i)=*(p2+i*N+j);
		}
	}//p2 store the distances between two nodes;
	time_t s_clock,e_clock,clock_start,clock_time;
	double ti=0.0;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(times1=0;times1<TS;times1++)
 {
	maxx=-1.0;
	minn=10000000000.0;
	sum=0.0;
    printf("times1: %d\n",times1);
	time_t now;
	now = time((time_t *)NULL); 
	printf("%s\n", ctime(&now));// print the  time now 
	//time_t s_clock,e_clock,clock_start,clock_time;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////construction phase
    memset(cpTO,0,sizeof(cpTO));
    memset(cpSO,0,sizeof(cpSO));
    memset(temp2,0,sizeof(temp2));

	for(i=0;i<5;i++)
	{
	    induce(N,cpSO[i]);
        cpTO[i]=evaldis(N,cpSO[i],p2);
    }
    for(i=5;i<10;i++)
    {
          induce(N,cpSO[i]);
          cpTO[i]=evaldis(N,cpSO[i],p2);
          proc1(N,cpSO[i],p2);
          /*for(k=0;k<N;k++)
    	   fprintf(file,"%d ",cpSO[i][k]);
    	   fprintf(file,"\n");*/
          cpTO[i]=evaldis(N,cpSO[i],p2);
          //fprintf(file,"cpTO2[%d]=%lf \n",i,cpTO[i]);
    }
   /* for(i=0;i<10;i++)
	{
	   fprintf(file,"cpTO[%d]=%lf \n",i,cpTO[i]);
       fprintf(file,"cpSO[%d]=\n",i);
	   for(k=0;k<N;k++)
	   fprintf(file,"%d ",cpSO[i][k]);
	   fprintf(file,"\n");
    }*/
   	s_clock=clock();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double best;
	int ii,position;
	for(times=0;times<it;times++)
	{
         /* for(i=0;i<10;i++)
    	 {
    	   fprintf(file,"cpTO[%d]=%lf \n",i,cpTO[i]);
           fprintf(file,"cpSO[%d]=\n",i);
    	   for(k=0;k<N;k++)
    	   fprintf(file,"%d ",cpSO[i][k]);
    	   fprintf(file,"\n");
    	   cpTO[i]=evaldis(N,cpSO[i],p2);  
    	   fprintf(file,"cpTO[%d]=%lf \n",i,cpTO[i]);
         }*/
          fprintf(file,"times: %d\n",times);
          memset(ini,0,sizeof(ini));
          best=10000000000.0;
          double temp3;
          int a,b,c;
          for(j=0;j<10;j++)
          {
                   fprintf(file,"cpTO1[%d]=%lf \n",j,cpTO[j]);
                   fprintf(file,"j=%d\n",j);
       //the first localsearch :swap                     
                   	a=rand()%N;
           loop3:   b=rand()%N;
                   if(a==b)
                    goto loop3;
                   // fprintf(file,"a=%d b=%d\n",a,b);
                    for(k=0;k<N;k++)
                       temp2[k]=cpSO[j][k];
                    exchange1(&temp2[a],&temp2[b]);                  
                    temp3=evaldis(N,temp2,p2);
                    //fprintf(file,"temp3=%lf\n",temp3);
                    if(temp3<cpTO[j])
                    {
                         //fprintf(file,"good temp31=%lf\n",temp3);
                         cpTO[j]=temp3;
                         for(k=0;k<N;k++)
                          cpSO[j][k]=temp2[k];
                    }
                     /*for(k=0;k<N;k++)
    	             fprintf(file,"%d ",cpSO[j][k]);
    	             fprintf(file,"\n"); */         
      //the second localsearch :insert
     	            a=rand()%N;
           loop4:   b=rand()%N;
                   if(a==b)
                    goto loop4;
                   if(a<b)
                    exchange1(&a,&b);
                    for(k=0;k<N;k++)
                       temp2[k]=cpSO[j][k];
                    temp3=evaldis(N,temp2,p2);
                    //fprintf(file,"temp3=%lf\n",temp3);
                    if(temp3<cpTO[j])
                    {
                       // fprintf(file,"good temp32=%lf\n",temp3);
                         cpTO[j]=temp3;
                         for(k=0;k<N;k++)
                          cpSO[j][k]=temp2[k];
                    } 
                    /* for(k=0;k<N;k++)
    	             fprintf(file,"%d ",cpSO[j][k]);
    	             fprintf(file,"\n");   */
      //the third  localsearch :interchange
             c=rand()%N;
            for(k=0;k<N;k++)
             temp2[k]=cpSO[j][k];
            if(c!=N-1)
             exchange1(&temp2[c],&temp2[c+1]);
            else 
             exchange1(&temp2[c],&temp2[0]);                  
             temp3=evaldis(N,temp2,p2);
                //fprintf(file,"temp3=%lf\n",temp3);
            if(temp3<cpTO[j])
            {
                // fprintf(file,"good temp33=%lf\n",temp3);
                 cpTO[j]=temp3;
                 for(k=0;k<N;k++)
                  cpSO[j][k]=temp2[k];
            }
            /* for(k=0;k<N;k++)
             fprintf(file,"%d ",cpSO[j][k]);
             fprintf(file,"\n"); */ 
      //the fourth localsearch :BR
             int cityA,cityB,temp;
             int city1,city2;
             double diss=10000000000.0;
             double y,df;
                cityA=rand()%(N-2)+1;
loopC1:	;
				cityB=rand()%(N-2)+1;
				if(cityA==cityB)
					goto loopC1;
				if(cityA>cityB)
				{
					temp=cityA;
					cityA=cityB;
					cityB=temp;
				}
				df=*(p2+cpSO[j][cityA-1]*N+cpSO[j][cityB])
					+*(p2+cpSO[j][cityA]*N+cpSO[j][cityB+1])
					-*(p2+cpSO[j][cityA-1]*N+cpSO[j][cityA])
					-*(p2+cpSO[j][cityB]*N+cpSO[j][cityB+1]);
				if(df<0)
				{
					city1=cityA;
					city2=cityB;
					if((city1+1)==city2)
            		{
            			temp=cpSO[j][city1];
            			cpSO[j][city1]=cpSO[j][city2];
        		        cpSO[j][city2]=temp;
            		}
            		else 
            		{
            			for(int i=city1;i<=(city1+city2)/2;i++)
            			{
            				temp=cpSO[j][i];
            				cpSO[j][i]=cpSO[j][city2-i+city1];
            				cpSO[j][city2-i+city1]=temp;
            			}
            		}
            		cpTO[j]+=df;
              }
               fprintf(file,"cpTO2[%d]=%lf \n",j,cpTO[j]);
        	   fprintf(file,"cpSO[%d]=\n",j);
        	   for(k=0;k<N;k++)
        	   fprintf(file,"%d ",cpSO[j][k]);
        	   fprintf(file,"\n");      	   
                if(cpTO[j]<best)
                {
                   best=cpTO[j];
                   position=j;
                   for(k=0;k<N;k++)
                      ini[k]=cpSO[j][k];
                }
         }        
          fprintf(file,"ini=\n ");
          fprintf(file,"best=%lf position=%d\n",best,position);
          for(k=0;k<N;k++)
            fprintf(file,"%d ",ini[k]);
            fprintf(file,"\n");
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	for(times=0;times<TS;times++)
//	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	cout<<"times:"<<times<<endl;*/
		t=800.0;
		//var=(80000.0*pow(1.0*N,0.05)-1.0)/(80000.0*pow(1.0*N,0.05));
		var=0.99999;
		solution=10000000000.0;
		//clock_start=clock();
		tv=0;
		greedy=N/3;
		two=-1;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
		/*	for(i=0;i<N;i++)
		{
			ini[i]=i;
		} */
        /*j=rand()%N;
		tg=ini[0];
		ini[0]=ini[j];
		ini[j]=tg;//*ini is  the random solution
		for(i=0;i<N-1;i++)
		{
			hh=sqrt(((*(p1+ini[i])-*(p1+ini[i+1])))*((*(p1+ini[i])-*(p1+ini[i+1])))
				+((*(p1+N+ini[i])-*(p1+N+ini[i+1])))*((*(p1+N+ini[i])-*(p1+N+ini[i+1]))));
			for(j=i+2;j<N;j++)
			{
				gg=sqrt(((*(p1+ini[i])-*(p1+ini[j])))*((*(p1+ini[i])-*(p1+ini[j])))
					+((*(p1+N+ini[i])-*(p1+N+ini[j])))*((*(p1+N+ini[i])-*(p1+N+ini[j]))));
				if(hh>gg)
				{
					tg=ini[i+1];
					ini[i+1]=ini[j];
					ini[j]=tg;
					hh=gg;
				}//find a better one,change 
			}
		}*/
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		y=0;
		for(i=0;i<N-1;i++)
		{
			y=y+*(p2+ini[i]*N+ini[i+1]);//row and column
		}
		y=y+*(p2+ini[0]*N+ini[N-1]);
		//fprintf(file,"y=%lf\n",y);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
loop1:	;
		/*clock_time=clock();
		if((difftime(clock_time,clock_start))>period)
			goto loop2;*/
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		initial=rand()%2;
		if(initial==1)
		{
			for(i=0;i<N/2;i++)
			{
				temp=ini[i];
				ini[i]=ini[N-1-i];
				ini[N-1-i]=temp;
			}// reverse the initial sequence
		}
		else
		{
			temp=ini[N-1];
			for(i=N-1;i>0;i--)
			{
				ini[i]=ini[i-1];
			}
			ini[0]=temp;//insert the last into the first
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////点插入
		select=rand()%100;
		//if(t<15&&two==-1)
		if(t<2&&two==-1)
		{
			greedy=3*N/2;
			t=800.0;
			two=1;
			//var=(80000.0*pow(1.0*N,0.05)-1.0)/(80000.0*pow(1.0*N,0.05));
			var=0.99999;
		}
	/*	if(select<10)
		{
			diss=100000000.0;
			for(i=0;i<greedy;i++)
			{
				cityA=rand()%(N-2)+1;
loopA:	;
				cityB=rand()%(N-2)+1;
				//printf("%d %d\n",cityA,cityB);
				if(cityA==cityB||(cityA+1)==cityB||(cityB+1)==cityA)
					goto loopA;
				if(cityA>cityB)
				{
					temp=cityA;
					cityA=cityB;
					cityB=temp;
				}
				df=*(p2+ini[cityB-1]*N+ini[cityB+1])
					+*(p2+ini[cityB]*N+ini[cityA])
					+*(p2+ini[cityA-1]*N+ini[cityB])
					-*(p2+ini[cityA-1]*N+ini[cityA])
					-*(p2+ini[cityB-1]*N+ini[cityB])
					-*(p2+ini[cityB]*N+ini[cityB+1]);
				if(df<diss)
				{
					diss=df;
					city1=cityA;
					city2=cityB;
				}
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////块插入
		/*if(select>=10&&select<11)
		{
			diss=10000000000.0;
			for(i=0;i<greedy;i++)
			{
loopB:	;
				cityA=rand()%(N-2)+1;
				cityB=rand()%(N-2)+1;
				cityC=rand()%(N-2)+1;
				if(cityA>cityB)
				{
					temp=cityA;
					cityA=cityB;
					cityB=temp;
				}
				if(cityA>cityC)
				{
					temp=cityA;
					cityA=cityC;
					cityC=temp;
				}
				if(cityB>cityC)
				{
					temp=cityB;
					cityB=cityC;
					cityC=temp;
				}
				if(cityA==cityB)
					goto loopB;
				df=*(p2+ini[cityA-1]*N+ini[cityB])
					+*(p2+ini[cityC]*N+ini[cityA])
					+*(p2+ini[cityB-1]*N+ini[cityC+1])
					-*(p2+ini[cityA-1]*N+ini[cityA])
					-*(p2+ini[cityB-1]*N+ini[cityB])
					-*(p2+ini[cityC]*N+ini[cityC+1]);
				if(df<diss)
				{
					diss=df;
					city1=cityA;
					city2=cityB;
					city3=cityC;
				}
			}
		}*/
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////块反转
		if(select>=0)
		{
			diss=10000000000.0;
			for(i=0;i<greedy;i++)
			{
				cityA=rand()%(N-2)+1;
loopC:	;
				cityB=rand()%(N-2)+1;
				//printf("%d %d\n",cityA,cityB);
				if(cityA==cityB)
					goto loopC;
				if(cityA>cityB)
				{
					temp=cityA;
					cityA=cityB;
					cityB=temp;
				}
				df=*(p2+ini[cityA-1]*N+ini[cityB])
					+*(p2+ini[cityA]*N+ini[cityB+1])
					-*(p2+ini[cityA-1]*N+ini[cityA])
					-*(p2+ini[cityB]*N+ini[cityB+1]);
				if(df<diss)
				{
					diss=df;
					city1=cityA;
					city2=cityB;
				}
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(diss<0.0)// find  a  better one
		{
           // fprintf(file,"less\n");
			/*if(select<10)
			{
				mid=ini[city2];
				for(i=city2;i>city1;i--)
				{
					ini[i]=ini[i-1];
				}
				ini[city1]=mid;
			}
		/*	if(select>=10&&select<11)
			{
				for(i=city1,j=city2;j<city3+1;i++,j++)
				{
					inim[i]=ini[j];
				}
				for(i=city1+city3-city2+1,j=city1;j<city2;i++,j++)
				{
					inim[i]=ini[j];
				}
				for(i=city1;i<city3+1;i++)
				{
					ini[i]=inim[i];
				}
			} */
			if(select>=0)
			{
				if((city1+1)==city2)
				{
					temp=ini[city1];
					ini[city1]=ini[city2];
					ini[city2]=temp;
				}
				else
				{
					for(i=city1;i<=(city1+city2)/2;i++)
					{
						temp=ini[i];
						ini[i]=ini[city2-i+city1];
						ini[city2-i+city1]=temp;
					}
				}
			}
			y=y+diss;
			if(y<solution)
			{
				solution=y;
				cpTO[position]=solution;
        		for(i=0;i<N;i++)
        		{
                     cpSO[position][i]=ini[i];
                }
				current_temp=t;
			 	//fprintf(file,"%f   %f\n",solution,t);
			}
			t=t*var;
		//	printf("%f\n",t);
		}
		else
		{
           // fprintf(file,"not less\n");
			tv++;
			randp=0.001*(rand()%1001);//produce one decimal between 0-1
			double ff;
			ff=exp((-df)/(t*OPT/(10.0*N)));
			if(ff>randp||tv%(N/10)==0)
			//if(ff<randp)
			//if(tv%(N/10)==0)
			{
                //fprintf(file,"compulsive accept\n");
			/*	if(select<10)
				{
					mid=ini[city2];
					for(i=city2;i>city1;i--)
					{
						ini[i]=ini[i-1];
					}
					ini[city1]=mid;
				}  
				/*if(select>=10&&select<11)
				{
					for(i=city1,j=city2;j<city3+1;i++,j++)
					{
						inim[i]=ini[j];
					}
					for(i=city1+city3-city2+1,j=city1;j<city2;i++,j++)
					{
						inim[i]=ini[j];
					}
					for(i=city1;i<city3+1;i++)
					{
						ini[i]=inim[i];
					}
				}*/
				if(select>=0)
				{
					if((city1+1)==city2)
					{
						temp=ini[city1];
						ini[city1]=ini[city2];
						ini[city2]=temp;
					}
					else 
					{
						for(i=city1;i<=(city1+city2)/2;i++)
						{
							temp=ini[i];
							ini[i]=ini[city2-i+city1];
							ini[city2-i+city1]=temp;
						}
					}
				}
				y=y+diss;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
			//fprintf(file,"%f \n",y);	
			}
			t=t*var;
			
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//if(t>10)
		if(t>1)
			goto loop1;
loop2: ;
        //fprintf(file,"t=%lf",t);
		fprintf(file,"solution is:%f.       temperature is:%f\n",solution,current_temp);
		sum=sum+solution;
		now = time((time_t *)NULL); 
		fprintf(file,"%s", ctime(&now));
		if(solution>maxx)
		{
			maxx=solution;
		}
		if(solution<minn)
		{
			minn=solution;
		}
	}
	//e_clock=clock();
	/*cout<<"The average run time for the algorithm is : "<<0.001*difftime(e_clock,s_clock)/it<<endl;
	cout<<"The average solution for the algorithm is : "<<sum/it<<endl;
	cout<<"The maxx solution for the algorithm is : "<<maxx<<endl;
	cout<<"The minn solution for the algorithm is : "<<minn<<endl;
	cout<<"The average error for the algorithm is : "<<(sum/it-OPT)/(1.0*OPT)<<endl;*/
	//fprintf(file,"The sum for the algorithm is : %lf\n",sum);
	//fprintf(file,"The average run time for the algorithm is : %lf\n",0.001*difftime(e_clock,s_clock)/it);
	fprintf(file,"The average solution for the algorithm is : %lf\n",sum/it);
	fprintf(file,"The maxx solution for the algorithm is : %lf\n ",maxx);
	fprintf(file,"The minn solution for the algorithm is : %lf \n",minn);
	fprintf(file,"The average error for the algorithm is : %lf\n",(sum/it-OPT)/(1.0*OPT));
	 e_clock=clock();
	 ti+=difftime(e_clock,s_clock);
}
   // e_clock=clock();
    fprintf(file,"The average run time for the algorithm is : %lf\n",0.001*ti/TS);
	//system("pause");
	delete ptd;
	delete ptf;
}

//The minn solution for the algorithm is : 29424.495501 one mutation ;15 10
//The minn solution for the algorithm is : 29379.281022 one mutation ;2 1
//The minn solution for the algorithm is : 29379.281022  one mutation ;2 1,without random
/*71 159 82 94 147 24 198 42 5 9 146 32 46 3 39 137 28 38 30 153 31 187 189 142 179 68 2 25 114 100 48 170 125 143 93 140 56 102 77 92 160 45 52 136 6 133 49 158 96 191 55 95 79 199 8 131 157 132 69 184 168 73 186 23 75 51 166 15 37 112 103 180 91 117 154 90 67 87 11 66 26 36 17 195 109 18 10 145 152 43 150 177 33 174 124 84 34 105 13 58 116 16 7 14 72 98 83 104 172 155 60 12 119 141 176 62 27 138 108 163 97 89 40 197 81 54 173 144 85 167 149 175 178 35 129 139 122 164 181 53 29 80 156 50 41 127 162 126 0 110 78 59 70 44 169 57 47 76 106 128 21 111 115 193 182 120 63 65 171 118 190 130 113 134 99 107 148 183 74 19 185 88 135 196 1 165 64 121 101 20 161 4 86 22 61 194 192 188 123 151 
  71 159 82 94 147 24 198 42 5 9 146 32 46 3 39 137 28 38 30 153 31 187 189 142 179 68 2 25 114 100 48 170 57 169 44 70 59 78 110 0 126 162 127 41 50 156 80 29 53 181 164 122 139 129 35 178 175 149 167 85 144 173 54 81 197 40 89 97 163 108 138 27 62 176 141 119 12 60 155 172 104 83 98 72 14 7 16 116 58 13 105 34 84 124 174 33 177 150 43 152 145 10 18 109 195 17 36 26 66 11 87 67 90 154 117 91 180 103 112 37 15 166 51 75 23 186 73 168 184 69 132 157 131 8 199 79 95 55 191 96 158 49 133 6 136 52 45 160 92 77 102 56 140 93 143 125 47 76 106 128 21 111 115 193 182 120 63 65 171 118 190 130 113 134 99 107 148 183 74 19 185 88 135 196 1 165 64 121 101 20 161 4 86 22 61 194 192 188 123 151 */
