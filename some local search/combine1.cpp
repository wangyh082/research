#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>//设置随机数种子头文件
using namespace std;
int order[100];//把pos数组的值赋给order，order下标从1开始 
int reorder[100];//每次插入后的次序
int rereorder[100];//最好的序列；
int reorder1[100]; 
int matrices[100][100];
int pos[100];
double number[100];

int addsum(int n,int *order)
{
    int sum=0;
    for(int i=1;i<n;i++)
       for(int j=i+1;j<=n;j++)
         sum+=matrices[order[i]][order[j]];
    return sum;
}


void proc1(int n)
{
    for(int i=0;i<n;i++)//生成-4到4之间的实数(精确到小数点后两位的实数) 
    {
         number[i]=(-400+rand()%(400-(-400)+1))/100.0 ;
         pos[i]=i+1;
    }
   /*for(int i=0;i<n;i++)
       printf(" %d ",pos[i]);
    printf("\n");
    for(int i=0;i<n;i++)
       printf(" %lf ",number[i]);
    printf("\n");  */  
    for(int i=0;i<n-1;i++)
      for(int j=0;j<n-1-i;j++)
      {
              if(number[j]>number[j+1])
              {
                 swap(number[j],number[j+1]);
                 swap(pos[j],pos[j+1]);
              } 
      }
    /*for(int i=0;i<n;i++)
       printf(" %d ",pos[i]);
    printf("\n");*/
   // for(int i=0;i<n;i++)
    //   printf(" %lf ",number[i]);
    //printf("\n");
}

void proc2(int n)
{
     proc1(n);
    for(int i=1;i<=n;i++)
      order[i]=pos[i-1];  //赋值很重要； 
    for(int i=1;i<=n;i++)
     printf(" %d ",order[i]);//获得随机数的序列
     printf("\n"); 
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

int main()
{
    int n;
    scanf("%d",&n);
    srand(time(0));
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        scanf("%d",&matrices[i][j]);
     printf("\n");
     proc2(n);
    system("pause");
    return 0;
}
//此为产生随机序列和NEH的结合 
