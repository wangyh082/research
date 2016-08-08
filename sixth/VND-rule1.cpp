#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>//设置随机数种子头文件
#include<math.h>
#include<string.h>
using namespace std;
struct po
{
    int s;
    int pos;
}jo[1000];//begin from 0 
int matrices[1000][1000];
int mat[1000][1000];
int disp[7][500];//dispatch the jobs to the factories
int c[1000][1000];
int a[1500];//
int b[1500];//when the insert function is applied,a & b are necessary
int fn[1000];
int ft[1000];
FILE *out1;
int job;
int step;
int f;

int cmp(const void *a,const void *b)
{
    po l1=*(po*)a;
    po l2=*(po*)b;
    int t=l1.s-l2.s;
    if(t<0)  return 1;
    else
      if(t>0) return -1;
    else
      {
              t=l1.pos-l2.pos;
              if(t>0) return 1;
              else return -1;
      }
}

int protime(int *a,int m,int step)
{
     memset(c,0,sizeof(c));
     c[a[1]][1]=mat[a[1]][1];    
     for(int i=2;i<=m;i++)
        c[a[i]][1]=c[a[i-1]][1]+mat[a[i]][1];
     for(int i=2;i<=step;i++)
        c[a[1]][i]=c[a[1]][i-1]+mat[a[1]][i];
     for(int i=2;i<=m;i++)
       for(int j=2;j<=step;j++)
          c[a[i]][j]=max(c[a[i-1]][j],c[a[i]][j-1])+mat[a[i]][j];
     return c[a[m]][step];    
}

void insert(int *a,int n,int c,int d)//insert c into the d position 
{
    for(int i=1;i<=n;i++)
      b[i]=a[i];
    for(int i=n;i>=d;i--)
       b[i+1]=b[i];
       b[d]=c;
    /* for(int i=1;i<=n+1;i++)
       fprintf(out1,"%d ",b[i]);
       fprintf(out1,"\n");*/
} 

void rule1(int *fn,int *ft)
{
    int mark,mark1;
    int t;
    for(int i=1;i<=f;i++)
    {
      fn[i]=1;
      ft[i]=0;
    } 
    for(int i=1;i<=f;i++)
      disp[i][fn[i]]=jo[i-1].pos;
    for(int i=f+1;i<=job;i++)//dispatch the other jobs
    {
        int  min=9999999;
        int  min1=999999;
        for(int j=1;j<=f;j++)
        {
           ft[j]=protime(disp[j],fn[j],step);
           fprintf(out1,"ft[%d]=%d\n",j,ft[j]);
           if(ft[j]<min)
           {
              min=ft[j];
              mark=j;
           }
        }//find the min factory,then insert the job into it 
        fprintf(out1,"min=%d,mark=%d\n",min,mark);       
        for(int j=1;j<=fn[mark]+1;j++)
        {
           insert(disp[mark],fn[mark],jo[i-1].pos,j);
           t=protime(b,fn[mark]+1,step);
           if(t<min1)
           {
               min1=t;
               mark1=j;//mark1 is the last position
           }
        }
        insert(disp[mark],fn[mark],jo[i-1].pos,mark1);
        fn[mark]++;//after inserted ,the number of factory
        //for(int i=1;i<=f;i++)
         // fprintf(out1,"fn[%d]=%d\n",i,fn[i]);
        for(int j=1;j<=fn[mark];j++)
          disp[mark][j]=b[j];
    } 
}

int main()
{ 
    freopen("Ta001.txt","r",stdin);
    int mmin=999999;   
    srand(time(0));
    out1=fopen("Ta001_result.txt","w");
        scanf("%d%d",&job,&step);
        scanf("%d",&f);
        memset(jo,0,sizeof(jo[0]));
        for(int i=1;i<=job;i++)
          for(int j=1;j<=step*2;j++)
            scanf(" %d",&matrices[i][j]);
        for(int i=1;i<=job;i++)
          for(int j=1;j<=step;j++)
            mat[i][j]=matrices[i][j*2];
         for(int i=1;i<=job;i++)
         {
           for(int j=1;j<=step;j++)
              jo[i-1].s+=mat[i][j];
           jo[i-1].pos=i;
           //fprintf(out1,"%d:%d\n",jo[i-1].pos,jo[i-1].s);
         }
         qsort(jo,job,sizeof(jo[0]),cmp);
         for(int i=1;i<=job;i++)
           fprintf(out1,"%d:%d\n",jo[i-1].pos,jo[i-1].s); //the descending order of jobs
         rule1(fn,ft);
         for(int i=1;i<=f;i++)
         {
            fprintf(out1,"f=%d:",i);
           for(int j=1;j<=fn[i];j++)
            fprintf(out1,"%d ",disp[i][j]);
            fprintf(out1,"\n");
         }
         /*int t;
         for(int i=1;i<=f;i++)
         {
           t=protime(disp[i],fn[i],step);  
           fprintf(out1,"t=%d\n",t);
         } */     
        system("pause");
        return 0; 
}
