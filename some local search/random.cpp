#include<stdio.h>
#include<stdlib.h>
#include<time.h>//�������������ͷ�ļ�
#include<algorithm>
using namespace std;
double number[100];
int pos[100];

void proc1(int n)
{
    for(int i=0;i<n;i++)//����-4��4֮���ʵ��(��ȷ��С�������λ��ʵ��) 
    {
         number[i]=(-400+rand()%(400-(-400)+1))/100.0 ;
         pos[i]=i+1;
    }
   /* for(int i=0;i<n;i++)
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
    for(int i=0;i<n;i++)
       printf(" %d ",pos[i]);
    printf("\n");
   // for(int i=0;i<n;i++)
    //   printf(" %lf ",number[i]);
    printf("\n");
}

int main()
{
    int n;
    srand(time(0));
    scanf("%d",&n);
    proc1(n);
    system("pause");
    return 0;
}
