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
int a[100];//表示第一个工厂的序列； 
int b[100];//表示第二个工厂的序列； 
FILE *out1;

int addsum(int n,int *order)
{
    int sum=0;
    for(int i=1;i<n;i++)
       for(int j=i+1;j<=n;j++)
         sum+=matrices[order[i]][order[j]];
    return sum;
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

void proc1(int n)
{
    for(int i=0;i<n;i++)//生成-4到4之间的实数(精确到小数点后两位的实数) 
    {
         s[i].number=(-400+rand()%(400-(-400)+1))/100.0 ;
         s[i].pos=i+1;
    }
    /*for(int i=0;i<n;i++)
     printf(" %lf %d ",s[i].number,s[i].pos);
     printf("\n"); */
    qsort(s,n,sizeof(s[0]),cmp);//***使用快速排序 
}

void proc2(int n,int *order)
{
      proc1(n);
    for(int i=1;i<=n;i++)
      order[i]=s[i-1].pos;  //赋值很重要；
    int reorder[100];//每次插入后的序列 
    int reorder1[100];//中间对比序列 
    int rereorder[100];//最好的序列； 
    int sum11;//初始的序列和
    int sum2[120];//比较的和 
    int sum22;
    int i,j,ii,jj,kk;
    int p;
    int temp;
    for(i=1;i<n;i++)
    {
          for(kk=1;kk<=n;kk++)
             reorder[kk]=0;
          sum11=addsum(i+1,order);
         // printf("sum11=%d\n",sum11);
          temp=order[i+1];
          sum22=0;
          for(j=1;j<=i;j++)
          {             
              for(kk=1;kk<=j;kk++)
                sum2[kk]=0;
              reorder[j]=temp;
              if(j==1) jj=0;
              else
              {
                for(jj=1;jj<=j-1;jj++)
                   reorder[jj]=order[jj];
              }
                p=j;
              for(ii=1;ii<=i-jj;ii++)
              {
                 ++p;
                 reorder[p]=order[p-1];
              }
             /* for(kk=1;kk<=i+1;kk++)
              {
                 printf(" %d ",reorder[kk]);
              }
                printf("\n");*/
                //reorder数组的长度是i+1;
               sum2[j]=addsum(i+1,reorder);
             //  printf("sum2[%d]=%d\n",j,sum2[j]);
               if(sum2[j]>sum22)
               {
                  sum22=sum2[j];
                  for(kk=1;kk<=i+1;kk++)
                    reorder1[kk]=reorder[kk];
               }  
              // for(kk=1;kk<=i+1;kk++)
                 // reorder[kk]=reorder1[kk];  
           }               
           if(sum22>sum11)
           {
                for(kk=1;kk<=i+1;kk++) 
                      rereorder[kk]=reorder1[kk];
                  sum11=sum22;
           }
           else
           {
                for(kk=1;kk<=i+1;kk++) 
                      rereorder[kk]=order[kk];
           }
          for(kk=1;kk<=i+1;kk++) 
             order[kk]=rereorder[kk];         
    }
    /*printf("final order:\n");
    for(int i=1;i<=n;i++)
     printf(" %d ",order[i]);//最后的序列 
     printf("\n");*/
}

void induce(int n,int *order)
{
      int i,temp;
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


int protime(int *a,int m,int step)//calculate one factory's time
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
int main()
{
    freopen("Ta001_2.txt","r",stdin);
    int mmin=999999; 
    int job,step;
    int f;
    srand(time(0));
    out1=fopen("Ta001_2_result.txt","w");
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
        for(int i=1;i<=2;i++)
        {              
             induce(job,order);
             int m=1+rand()%(job-1);
           fprintf(out1,"m=%d\n",m);  
           int n=job-m;         
           for(int j=1;j<=m;j++)
             a[j]=order[j]; 
           int c=1;
           for(int j=m+1;j<=job;j++)
             b[c++]=order[j];
          /* for(int j=1;j<=m;j++)
             fprintf(out1,"%d ",a[j]);
             fprintf(out1,"\n");
           for(int j=1;j<=c-1;j++)
             fprintf(out1,"%d ",b[j]);
             fprintf(out1,"\n");
          /*int m=6;
          int n=1;
             a[1]=1;a[2]=4;a[3]=5,a[4]=2;a[5]=6;a[6]=3;
             b[1]=7;*/
          int t1=protime(a,m,step);
            fprintf(out1,"t1=%d\n",t1);
          int t2=protime(b,n,step);
            fprintf(out1,"t2=%d\n",t2);
          int result=max(t1,t2);
          if(result<mmin)
             mmin=result;
       }
       fprintf(out1,"result=%d\n",mmin);
       system("pause");
       return 0;
}
