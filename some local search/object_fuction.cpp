#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
int init;//已知f(x)初值；
int order[100];//初始序列； 
int matrices[100][100];
int i;//元素位置 
int j;//插入位置 

int addsum(int n,int *order)
{
    int sum=0;
    for(int i=1;i<n;i++)
       for(int j=i+1;j<=n;j++)
         sum+=matrices[order[i]][order[j]];
    return sum;
}

int obj_func(int i,int j,int *order)
{
    int temp=0;
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

void proc5(int n,int i,int j,int *order)
{
     int temp;
     if(i>j)
     {
          temp=order[i];
          for(int k=i-1;k>=j;k--)
            order[k+1]=order[k];
          order[j]=temp;
     }
     else
       if(i<j)
       {
            temp=order[i];
            for(int k=i+1;k<=j;k++)
              order[k-1]=order[k];
            order[j]=temp;
       }
    for(int i=1;i<=n;i++)
     printf(" %d ",order[i]);
    printf("\n");     
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        scanf("%d",&matrices[i][j]);
    for(int i=1;i<=n;i++)
      scanf("%d",&order[i]);
    init=addsum(n,order); 
    printf("init=%d\n",init);
    int i,j,obj,sub;
    scanf("%d%d",&i,&j);
    sub=obj_func(i,j,order);
    obj=init-sub;
    printf("obj=%d\n",obj);
    proc5(n,i,j,order);
    system("pause");
    return 0;
}
