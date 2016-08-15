#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>//设置随机数种子头文件 
#include<algorithm>

using namespace std;

int matrices[100][100];
int order[100]; 
int flag[100]; 
int finalor[100];
int ffinalor[100];

int addsum(int n)
{
    int sum=0;
    for(int i=1;i<n;i++)
       for(int j=i+1;j<=n;j++)
         sum+=matrices[order[i]][order[j]];
    return sum;
}


int proc(int n)//点从1开始计数
{
     int i,temp;
     int max=0; 
     int sum1,sum2;
     for(i=1;i<=n;i++)
     {
       order[i]=0;
       flag[i]=0;//表示这个数未生成
       finalor[i]=0; 
     }
     for(i=1;i<=n;i++)
     {     
       temp=1+rand()%n;
        while(flag[temp]==1)
         temp=1+rand()%n;
        order[i]=temp;
        flag[temp]=1;
     } 
     //sort(order,order+n+1);
     printf("the first order:");
     for(int i=1;i<=n;i++)
       printf(" %d ",order[i]);
     sum1=addsum(n);
     printf("sum1=%d\n",sum1);
     for(int i=1;i<n;i++)
     {              
          swap(order[i],order[i+1]);//交换n-1次；
          for(int j=1;j<=n;j++)
           printf(" %d ",order[j]); 
           printf("\n"); 
          sum2=addsum(n);
          printf("sum2=%d\n",sum2);
          if(sum1>sum2)
         {
            swap(order[i],order[i+1]);
            for(int i=1;i<=n;i++)
             printf(" %d ",order[i]); 
             printf("\n"); 
            if(sum1>max)
            {
              max=sum1;
              for(int i=1;i<=n;i++)
                finalor[i]=order[i];
            }
          }
          else
          {
             if(sum2>max)
             {
                max=sum2;
                for(int i=1;i<=n;i++)
                  finalor[i]=order[i];
             }
             sum1=sum2; 
          }
           printf("the final order:");
          for(int i=1;i<=n;i++)
            printf(" %d ",order[i]); 
            printf("\n"); 
     } 
     return max;
}

int main()
{ 
        int n;
        int MAX;
        srand(time(0)); 
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
          for(int j=1;j<=n;j++)
           scanf("%d",&matrices[i][j]);   
        MAX=proc(n);  
        printf(" MAX=%d ",MAX);
       for(int i=1;i<=n;i++)
       {
          printf(" %d ",finalor[i]);
       }
          printf("\n");  
    system("pause");
    return 0;
}
/*
5
1 8 1 2 3
4 9 5 6 8
7 9 7 9 9
8 8 9 10 9
8 7 4 5 6
*/
