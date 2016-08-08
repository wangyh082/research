#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>//设置随机数种子头文件
#include<string.h>
#define NP 20
#define M 50
using namespace std;
int order[1000];//order下标从1开始  
int matrices[1000][1000];
int mat[1000][1000];
int c[1000][1000];
int flag[1000]; 
struct po
{
    double number;
    int pos;
}s[100];
int a[100]={1,2,3};//表示第一个工厂的序列； 
int b[100]={4,5};//表示第二个工厂的序列；
int c1[100]={6,7}; 
FILE *out1;



int protime(int *a,int m,int step)//calculate one factory's time
{
     memset(c,0,sizeof(c));
     c[a[0]][1]=mat[a[0]][1];    
     for(int i=1;i<m;i++)
        c[a[i]][1]=c[a[i-1]][1]+mat[a[i]][1];
     for(int i=2;i<=step;i++)
        c[a[0]][i]=c[a[0]][i-1]+mat[a[0]][i];
     for(int i=1;i<m;i++)
       for(int j=2;j<=step;j++)
          c[a[i]][j]=max(c[a[i-1]][j],c[a[i]][j-1])+mat[a[i]][j];
     return c[a[m-1]][step];    
}


int main()
{
    freopen("Ta001.txt","r",stdin);
    int mmin=999999; 
    int job,step;
    int f;
    srand(time(0));
    out1=fopen("Ta001_test.txt","w");
        scanf("%d%d",&job,&step);
        scanf("%d",&f);
        for(int i=1;i<=job;i++)
          for(int j=1;j<=step*2;j++)
            scanf(" %d",&matrices[i][j]);
        for(int i=1;i<=job;i++)
          for(int j=1;j<=step;j++)
            mat[i][j]=matrices[i][j*2];
         for(int i=1;i<=job;i++)
         {
           for(int j=1;j<=step;j++)
             fprintf(out1,"%d ",mat[i][j]);
             fprintf(out1,"\n");
         }
         for(int i=0;i<=3;i++)
           fprintf(out1,"a[%d]=%d\n",i,a[i]);
          int t1=protime(a,3,step);
            fprintf(out1,"t1=%d\n",t1);
          int t2=protime(b,2,step);
            fprintf(out1,"t2=%d\n",t2);
          int t3=protime(c1,2,step);
            fprintf(out1,"t3=%d\n",t3);
       system("pause");
       return 0;
}
