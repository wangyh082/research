#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>//�������������ͷ�ļ� 
#include<algorithm>
using namespace std;

int matrices[100][100];
int order[100]; //�����һ������ 
int flag[100]; 
int finalor[100];//һ����������õ����� 
int ffinalor[100];//100����������õ����� 

int addsum(int n,int *order)
{
    int sum=0;
    for(int i=1;i<n;i++)
       for(int j=i+1;j<=n;j++)
         sum+=matrices[order[i]][order[j]];
    return sum;
}


int proc(int n)//���1��ʼ����
{
     int i,temp;
     int max=0; 
     int sum1,sum2;
     for(i=1;i<=n;i++)
     {
       order[i]=0;
       flag[i]=0;//��ʾ�����δ����
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
    // for(int i=1;i<=n;i++)
      // printf(" %d ",order[i]);����������� 
     sum1=addsum(n,order);
     //printf("sum1=%d\n",sum1);
      for(int i=1;i<n;i++)
     {     
              for(int j=i;j<n;j++)  
            {       
                  swap(order[j],order[j+1]);//����(n-1)*n/2�Σ�
                 // for(int i=1;i<=n;i++)
                  //  printf(" %d ",order[i]); 
                   // printf("\n"); 
                  sum2=addsum(n,order);
                 // printf("sum2=%d\n",sum2);
                  if(sum1>sum2)
                 {
                    swap(order[j],order[j+1]);
                  //  for(int i=1;i<=n;i++)
                  //   printf(" %d ",order[i]); 
                   //  printf("\n"); 
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
           }
             //for(int i=1;i<=n;i++)
             // printf(" %d ",order[i]); 
             // printf("\n"); 
     } 
     return max;
    // printf("%d\n",max);
    // for(int i=1;i<=n;i++)
     // printf(" %d ",finalor[i]);
     // printf("\n"); 
}

int main()
{ 
    freopen("N-pal23","r",stdin);
    FILE *out1;
    int mmax=0;      
    int n;
    srand(time(0));
    out1=fopen("result2","w");
    for(int j=1;j<=n;j++)
       ffinalor[j]=0;  
    for(int i=1;i<=100;i++)//ִ��100�Σ������Ľ��д��һ���ļ��� 
   {     
        int MAX; 
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
          for(int j=1;j<=n;j++)
           scanf("%d",&matrices[i][j]);   
        MAX=proc(n);  
        if(MAX>mmax)
        {
            mmax=MAX;
            for(int i=1;i<=n;i++)
              ffinalor[i]=finalor[i];
        }
        fprintf(out1,"%d\n",MAX);//MAX��ʾ����һ����������õĽ���� 
       for(int i=1;i<=n;i++)
       {
          fprintf(out1," %d ",finalor[i]);
       }
          fprintf(out1,"\n");  
          //Sleep���ʱ�����Ժ���Ϊ��λ��               
   }
   fprintf(out1,"all max=%d\n",mmax);//mmax��ʾ����100����������õĽ���� 
   for(int i=1;i<=n;i++)
   {
       fprintf(out1," %d ",ffinalor[i]);
   }
       fprintf(out1,"\n");  
    system("pause");
    return 0;
}
/*
5
0 1 2 3 6
4 0 5 6 7
7 9 0 9 8
8 8 9 0 9
7 8 9 8 0
4
0 1 2 3 
4 0 5 6 
7 9 0 9 
8 8 9 0

*/
