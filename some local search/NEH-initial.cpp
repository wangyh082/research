#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
int order[100];//��pos�����ֵ����order��order�±��1��ʼ 
int reorder[100];//ÿ�β����Ĵ���
int rereorder[100];//��õ����У�
int reorder1[100]; 
int matrices[100][100];

int addsum(int n,int *order)
{
    int sum=0;
    for(int i=1;i<n;i++)
       for(int j=i+1;j<=n;j++)
         sum+=matrices[order[i]][order[j]];
    return sum;
}


void proc2(int n,int *order)
{
    int sum11;//��ʼ�����к�
    int sum2[120];//�Ƚϵĺ� 
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
                //reorder����ĳ�����i+1;
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
     printf(" %d ",order[i]);//�������� 
     printf("\n");*/
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        scanf("%d",&matrices[i][j]);
    //for(int i=1;i<=n;i++)//�˶���Ҫrandom�Ľ�� 
    //   order[i]=pos[i-1];// 
    for(int i=1;i<=n;i++)
      scanf("%d",&order[i]);       
    proc2(n,order);
    for(int i=1;i<=n;i++)
     printf(" %d ",order[i]);//�������� 
    system("pause");
    return 0;
}
