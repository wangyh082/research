#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>//设置随机数种子头文件
using namespace std;
int order[100];//把pos数组的值赋给order，order下标从1开始 
int reorder[100];//每次插入后的次序
int reorder1[100];
int rereorder[100];//最好的序列； 
int matrices[100][100];
int init;//初始序列； 
struct po
{
    double number;
    int pos;
}s[100];

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
     //srand(time(0));
    for(int i=0;i<n;i++)//生成-4到4之间的实数(精确到小数点后两位的实数) 
    {
         s[i].number=(-400+rand()%(400-(-400)+1))/100.0 ;
         s[i].pos=i+1;
    }
    for(int i=0;i<n;i++)
     printf(" %lf %d ",s[i].number,s[i].pos);
     printf("\n"); 
    qsort(s,n,sizeof(s[0]),cmp);//***使用快速排序 
}


void proc2(int n,int *order)
{
     proc1(n);
    for(int i=1;i<=n;i++)
      order[i]=s[i-1].pos;  //赋值很重要； 
    for(int i=1;i<=n;i++)
     printf(" %d ",order[i]);//获得随机数的序列 
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
    printf("final order:\n");
    for(int i=1;i<=n;i++)
     printf(" %d ",order[i]);//最后的序列 
     printf("\n");
}

int obj_func(int i,int j,int *order)
{
    int temp=0;
    int obj;
    if(i<j)
    {
        for(int k=i+1;k<=j;k++)
          temp+=matrices[order[i]][order[k]]-matrices[order[k]][order[i]];      
    }
    else
      if(i>j)
    {
         for(int k=j;k<=i-1;k++)
          temp+=matrices[order[k]][order[i]]-matrices[order[i]][order[k]];  
    }
    return  temp;    
}

int main()
{
    int n;
    scanf("%d",&n);
    srand(time(0));
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        scanf("%d",&matrices[i][j]);
    proc2(n,order);
    init=addsum(n,order); 
    printf("init=%d\n",init);
    int i,j,obj,sub;
    scanf("%d%d",&i,&j);
    sub=obj_func(i,j,order);
    obj=init-sub;
    printf("obj=%d\n",obj);
    system("pause");
    return 0;
}
//此为NEH和变换后的目标函数的结合 
