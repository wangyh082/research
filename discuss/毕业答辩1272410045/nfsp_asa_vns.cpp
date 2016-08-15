#include <iostream>
#include <stdlib.h>
#include <math.h> 
#include <stdio.h> 
#include <time.h>
int T[1000][100];
double d[1000][100][100];
int temp[2000];
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int N,M;
int TS;// the iteration times
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace std;

double max(double a,double b)
{
    if(a>b)
    return a;
    return b;
}

double fitness(int *order,int n,int m)
{
    double cmax;
    int i,j;
    for(j=1;j<=m-1;j++)
    {
      d[1][j][j+1]=T[order[1]][j+1];
      d[2][j][j+1]=max(d[1][j][j+1]-T[order[2]][j],0)+T[order[2]][j+1];
    }
    for(i=2;i<=n;i++)
    {
      for(j=1;j<=m-1;j++)
      {
           d[i][j][j+1]=max(d[i-1][j][j+1]-T[order[i]][j],0)+T[order[i]][j+1];
      }
    }
    double sum=0.0;
    for(j=1;j<=m-1;j++)
      sum+=d[n][j][j+1];
    int sum1=0;
    for(i=1;i<=n;i++)
       sum1+=T[order[i]][1]; 
    cmax=sum+sum1;
    return cmax;       
}


void insert(int *a,int c,int d)//insert c position's value into the d position  c>d or vertex insert
{
    int temp;
    temp=a[c];
    for(int i=c-1;i>=d;i--)
       a[i+1]=a[i];
       a[d]=temp;
       //printf("%d ",b[i]);
      // printf("\n");
}

void exchange1(int *x, int *y)  //interchange
// exchange the values between the two arguments
//
// input arguments:
// x = integer
// y = integer
{
	int temp = *x;
	*x = *y;
	*y = temp;
} //exchange


void BI(int *a,int cityA,int cityB,int cityC)//block insert :three numbers are different from each other
{
        int temp1;
     	if(cityA>cityB)
		{
			temp1=cityA;
			cityA=cityB;
			cityB=temp1;
		}
		if(cityA>cityC)
		{
			temp1=cityA;
			cityA=cityC;
			cityC=temp1;
		}
		if(cityB>cityC)
		{
			temp1=cityB;
			cityB=cityC;
			cityC=temp1;
		}
        //cityA<cityB<cityC
        int i,j;
        int k=0;
        for(i=cityB;i<=cityC;i++)
        {
                temp[k]=a[i];
                for(j=cityB-1+k;j>=cityA+k;j--)
               {
                      a[j+1]=a[j];
               }
               k++;
              
        }
        k=0;
        for(i=cityA;i<=cityA+cityC-cityB;i++)
        {
             a[i]=temp[k]; 
             k++;
        }
} 

void induce(int n,int *order)
{
      int i,temp;
      int flag[1000];
      for(i=1;i<=n;i++)
     {
       order[i]=0;
       flag[i]=0;//表示这个数未生成 
     }
     for(i=1;i<=n;i++)
     {     
        temp=1+rand()%n;
        while(flag[temp]==1)
         temp=1+rand()%n;
        order[i]=temp;
        flag[temp]=1;
     } 
}


double  vns1(int ini[1000],double  x0,int N,int M)
{
    int order[1000];
    int order1[1000];
    double  x;
    int a,b;
    int cityA,cityB,cityC;
    int i,j;
    double y;
    for(i=1;i<=N;i++)
     order[i]=ini[i];
     a=1+rand()%N;
     b=1+rand()%N;
     while(a==b)
     b=1+rand()%N;
     // printf("a=%d b=%d\n",a,b);
     exchange1(&order[a],&order[b]);//randomize the solution*/
     y=fitness(order,N,M);
    for(j=1;j<=(N*(N-1))/2;j++)
    {
             int p=0;
             while(p<2)
             {
                      if(p==0)
                      {  
                          for(i=1;i<=N;i++)
                            order1[i]=order[i];
                           a=1+rand()%N;
                           b=1+rand()%N;
                           while(a==b)
                             b=1+rand()%N;
                            if(a<b)
                            exchange1(&a,&b);         
                            insert(order1,a,b);
                      }
                      if(p==1)
                      {
                            for(i=1;i<=N;i++)
                             order1[i]=order[i];
                loopD:        cityA=1+rand()%N;
                              cityB=1+rand()%N;
                              cityC=1+rand()%N;
                              if(cityA==cityB)
                              goto loopD;
                             BI(order1,cityA,cityB,cityC);
                      }
                        x=fitness(order1,N,M);
                        if(x<=y)
                        {
                                for(i=1;i<=N;i++)
                                 order[i]=order1[i];
                                 y=x;
                                 p=0;
                        }
                        else p++;
             }
            
    }
    if(y<=x0)
    {
          for(i=1;i<=N;i++)
             ini[i]=order[i];
          x0=y;
    }
    return x0;
   
}


int main()
{
    int ijij;
    char s[200];
   for(ijij=111;ijij<=120;ijij++)
  {     
        printf("%d\n",ijij);
        if(ijij<=60)
          TS=20;
         else 
          TS=10;       
         /*TS=1;*/
        if(ijij<=30)
          N=20;
        else if(ijij>30&&ijij<=60)
          N=50;
        else if(ijij>60&&ijij<=90)
          N=100;
        else if(ijij>90&&ijij<=110)
          N=200;
        else
          N=500;
        if((ijij>=1&&ijij<=10)||(ijij>30&&ijij<=40)||(ijij>60&&ijij<=70))
         M=5;
        else if((ijij>10&&ijij<=20)||(ijij>40&&ijij<=50)||(ijij>70&&ijij<=80)||(ijij>90&&ijij<=100))
         M=10;
        else M=20;
        itoa(ijij,s,10);
        char s1[200]="shujujiresult\\";
        strcat(s1,s);
        strcat(s1,s);
        strcat(s1,s);
        char s2[200]=".txt";
        strcat(s1,s2);
        printf("%s\n",s1);
        FILE *file;
    	file=fopen(s1,"w");
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int i,j,times;
	int temp;
	int ini[1000];
	int ini1[1000];
	int ans[1000];
	int greedy,select,initial;
	int tv,two,tg;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double hh,gg;
	double xv,yv;
	double period;
	if(ijij<=30)
	period=1000;
	else  if(ijij>30&&ijij<=60)
	period =5000;
	else if(ijij>60&&ijij<=90)
	period=10000;
	else if(ijij>90&&ijij<=110)
	period=20000;
	else 
	period=100000;
	//period=1000;
	fprintf(file,"period=%lf\n",period/1000);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	double solution;
	double t,var;
	double y,y1;
	double randp,diss,df,sum;
	double maxx,minn,current_temp;
	maxx=-1.0;
	minn=10000000000.0;
	sum=0.0;
	srand((unsigned)time(NULL));//the seed
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	char s3[200]="shujuji\\";
     strcat(s3,s);
     strcat(s3,s2);
     printf("%s\n",s3);
	FILE *f1;
	f1=fopen(s3,"r");
    for(i=1;i<=M;i++)
	   for(j=1;j<=N;j++)
	     fscanf(f1,"%d",&T[j][i]);
	fclose(f1);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	time_t now;
	now = time((time_t *)NULL); 
	fprintf(file,"%s\n", ctime(&now));// print the  time now 
	fprintf(file,"N=%d M=%d\n",N,M);
	time_t   s_clock,e_clock,clock_start,clock_time,clock_time1;
	s_clock=clock();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(times=0;times<TS;times++)
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//cout<<"times:"<<times<<endl;
		printf("times:%d\n",times);
		fprintf(file,"times:%d\n",times);
		t=1000.0;
		//var=(160000.0*pow(1.0*N,0.05)-1.0)/(160000.0*pow(1.0*N,0.05));
		var=0.99999;
		//printf("var=%lf\n",var);
		solution=10000000000.0;
		clock_start=clock();
		tv=0;
		greedy=N/3;
		two=-1;
		/*for(i=1;i<=N;i++)
		{
			ini[i]=i;
		}*/ 
        //the initial sequence
         induce(N,ini);
		/*for(i=1;i<=N;i++)
		  printf("%d ",ini[i]);
		  printf("\n");*/
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		y=fitness(ini,N,M);
		//printf("first:y=%lf\n",y);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
loop1:	;
      	clock_time=clock();
		if((difftime(clock_time,clock_start))>period)
		{
            //printf("time=%lf\n",(difftime(clock_time,clock_start)));
			goto loop2;
        }
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////点插入
		//select=rand()%100;
		if(t<0.005&&two==-1)
		{
			greedy=3*N/2;
			t=1000.0;
			two=1;
			var=0.9999;
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////vns1
		{
            /*int flag[50000];
            memset(flag,0,sizeof(flag));*/
            diss=10000000000.0;
			for(j=1;j<=N;j++)
            ini1[j]=ini[j];
			for(i=0;i<greedy;i++)
			{	 
                 
               	clock_time1=clock();
        		if((difftime(clock_time1,clock_start))>period)
                {
                       //printf("time1=%lf\n",difftime(clock_time1,clock_start)); 
        			   goto loop3;
                } 
                y1=fitness(ini1,N,M);
                //printf("y1=%lf\n",y1);
                df=vns1(ini1,y1,N,M);
                //printf("df=%lf\n",df);
                if(df<diss)
                diss=df;
                /*flag[(int)diss]++;
                if(flag[(int)diss]>6) 
                  break;*/
            }
           //printf(" the diss1=%lf\n",diss);
		}
		//printf(" the diss=%lf\n",diss);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
loop3:	if(diss<y)// find  a  better one
		{
		
            for(j=1;j<=N;j++)
            ini[j]=ini1[j];
			y=diss;
			t=t*var;
		//	printf("%f\n",t);
		 }
		else
		{
			tv++;
			if(tv%N==0)
			{
				for(j=1;j<=N;j++)
                ini[j]=ini1[j];
				y=diss;
			}
			t=t*var;
		}
		if(y<solution)
		{
			solution=y;
			current_temp=t;	
            for(j=1;j<=N;j++)
              ans[j]=ini[j];			
		 	//printf("solution=%lf   t=%f\n",solution,t);
		 	
		}		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(t>0.0025)
			goto loop1;
loop2: ;
		fprintf(file,"solution is:%f.       temperature is:%f\n",solution,current_temp);
		fprintf(file,"ans array:\n");
		for(j=1;j<=N;j++)
		   fprintf(file,"%d ",ans[j]);
		   fprintf(file,"\n");
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
	fprintf(file,"The average run time for the algorithm is : %lf\n",.001*difftime(e_clock,s_clock)/TS);
	fprintf(file,"The average solution for the algorithm is : %lf\n",sum/TS);
	fprintf(file,"The maxx solution for the algorithm is : %lf\n",maxx);
	fprintf(file,"The minn solution for the algorithm is : %lf\n",minn);
  }
	//system("pause");
}
//too slow 
 
