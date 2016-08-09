//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <stdlib.h>
#include <math.h> 
#include <stdio.h> 
#include <time.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define  TS		1// the iteration times
#define  N		51
#define  OPT	426
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace std;

int main()
{
    FILE *file;
	file=fopen("out2.txt","w");
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int i,j,times;
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
	double period;
	period=1000.0*pow(1.0*N,0.8);
	cout<<period/1000<<endl;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double *ptd=new double[N*N];	
	double solution;
	double t,var;
	double y;
	double randp,diss,df,sum;
	double maxx,minn,current_temp;
	maxx=-1.0;
	minn=10000000000.0;
	sum=0.0;
	var=(160000.0*pow(1.0*N,0.05)-1.0)/(160000.0*pow(1.0*N,0.05));
	printf("var1=:%9.9lf\n",var);
	var=(80000.0*pow(1.0*N,0.05)-1.0)/(80000.0*pow(1.0*N,0.05));
	printf("var2=:%9.9lf\n",var);
	srand((unsigned) time(NULL));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double *p1;//p1 store the x and y coordinate
	p1=ptf;
	FILE *f1;
	if((f1=fopen("1.c","r"))==NULL)
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
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	time_t now;
	now = time((time_t *)NULL); 
	fprintf(file,"%s\n", ctime(&now));// print the  time now 
	time_t s_clock,e_clock,clock_start,clock_time;
	s_clock=clock();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(times=0;times<TS;times++)
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//cout<<"times:"<<times<<endl;
		fprintf(file,"times:%d\n",times);
		t=1000.0;
		var=(160000.0*pow(1.0*N,0.05)-1.0)/(160000.0*pow(1.0*N,0.05));
		solution=10000000000.0;
		clock_start=clock();
		tv=0;
		greedy=N/3;
		two=-1;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for(i=0;i<N;i++)
		{
			ini[i]=i;
		}
		j=rand()%N;
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
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		y=0;
		for(i=0;i<N-1;i++)
		{
			y=y+*(p2+ini[i]*N+ini[i+1]);//row and column
		}
		y=y+*(p2+ini[0]*N+ini[N-1]);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
loop1:	;
		clock_time=clock();
		if((difftime(clock_time,clock_start))>period)
			goto loop2;
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
		if(t<0.005&&two==-1)
		{
			greedy=3*N/2;
			t=1000.0;
			two=1;
			var=(80000.0*pow(1.0*N,0.05)-1.0)/(80000.0*pow(1.0*N,0.05));
		}
		if(select<10)
		{
			diss=100000000.0;
			for(i=0;i<greedy;i++)
			{
				cityA=rand()%(N-2)+1;
loopA:	;
				cityB=rand()%(N-2)+1;
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
		if(select>=10&&select<11)
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
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////块反转
		if(select>=11)
		{
			diss=10000000000.0;
			for(i=0;i<greedy;i++)
			{
				cityA=rand()%(N-2)+1;
loopC:	;
				cityB=rand()%(N-2)+1;
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
			if(select<10)
			{
				mid=ini[city2];
				for(i=city2;i>city1;i--)
				{
					ini[i]=ini[i-1];
				}
				ini[city1]=mid;
			}
			if(select>=10&&select<11)
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
			}
			if(select>=11)
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
				current_temp=t;
			 	//fprintf(file,"%f   %f\n",solution,t);
			}
			t=t*var;
		//	printf("%f\n",t);
		}
		else
		{
			tv++;
			randp=0.001*(rand()%1001);//produce one decimal between 0-1
			double ff;
			ff=exp((-df)/(t*OPT/(10.0*N)));
			if(ff>randp||tv%(N/10)==0)
			{
				if(select<10)
				{
					mid=ini[city2];
					for(i=city2;i>city1;i--)
					{
						ini[i]=ini[i-1];
					}
					ini[city1]=mid;
				}
				if(select>=10&&select<11)
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
				}
				if(select>=11)
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
			}
			t=t*var;
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(t>0.0025)
			goto loop1;
loop2: ;
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
	e_clock=clock();
	/*cout<<"The average run time for the algorithm is : "<<0.001*difftime(e_clock,s_clock)/TS<<endl;
	cout<<"The average solution for the algorithm is : "<<sum/TS<<endl;
	cout<<"The maxx solution for the algorithm is : "<<maxx<<endl;
	cout<<"The minn solution for the algorithm is : "<<minn<<endl;
	cout<<"The average error for the algorithm is : "<<(sum/TS-OPT)/(1.0*OPT)<<endl;*/
	fprintf(file,"The average run time for the algorithm is : %lf\n",.001*difftime(e_clock,s_clock)/TS);
	fprintf(file,"The average solution for the algorithm is : %lf\n",sum/TS);
	fprintf(file,"The maxx solution for the algorithm is : %lf\n ",maxx);
	fprintf(file,"The minn solution for the algorithm is : %lf \n",minn);
	fprintf(file,"The average error for the algorithm is : %lf\n",(sum/TS-OPT)/(1.0*OPT));
	//system("pause");
	delete ptd;
	delete ptf;
}
