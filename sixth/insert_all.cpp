#include<stdio.h>
#include<stdlib.h>
int a[1500];
int b[1500];
void insert(int *a,int n,int c,int d)//insert c into the d position 
{
    for(int i=1;i<=n;i++)
      b[i]=a[i];
    for(int i=n;i>=d;i--)
       b[i+1]=b[i];
       b[d]=c;
     for(int i=1;i<=n+1;i++)
       printf("%d ",b[i]);
       printf("\n");
}
 
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
       scanf("%d",&a[i]);
    for(int i=1;i<=n+1;i++)
     insert(a,n,3,i);
    system("pause");
    return 0;
}
