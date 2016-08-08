#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

int s1[100];
int norder(int m,int n)//m is the number of jobs ,n is the number of factories;
{
    int sum=0;
    int temp;
    int f=0;
    for(int i=1;i<=n;i++)
    {
       s1[i]=1;
    } 
    if(m==n)
    {
        f=1;    
    }
    if(f==0)
    {
        for(int i=1;i<n;i++)
        {
            temp=rand()%(m-n-sum);
            s1[i]+=temp;
            sum+=temp;
            if(sum==m-n)
            {
              break;
            }
            //printf("%d\n",s1[i]);         
        }
    }
    s1[n]+=m-n-sum;
    f=0;
    for(int i=1;i<=n;i++)
      printf("%d ",s1[i]);
      printf("\n");
    
}

int main()
{
    srand(time(0));
    int job,f;
    scanf("%d %d",&job,&f);
    norder(job,f);
    system("pause");
    return 0;
}
