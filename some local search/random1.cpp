#include<stdio.h>
#include<stdlib.h>
#include<time.h>//设置随机数种子头文件
#include<algorithm>
using namespace std;
struct po
{
    double number;
    int pos;
}s[100];

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
    for(int i=0;i<n;i++)
     printf(" %lf %d ",s[i].number,s[i].pos);
     printf("\n"); 
    qsort(s,n,sizeof(s[0]),cmp);//***使用快速排序 
}

int main()
{
    int n;
    srand(time(0));
    scanf("%d",&n);
    proc1(n);
    for(int i=0;i<n;i++)
     printf(" %lf %d ",s[i].number,s[i].pos);
     printf("\n"); 
    system("pause");
    return 0;
}
