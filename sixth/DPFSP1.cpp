#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>//�������������ͷ�ļ�
#include<string.h>
#define NP 20
#define M 50
using namespace std;
int order[1000];//order�±��1��ʼ  
int matrices[1000][1000];
int mat[1000][1000];
int c[1000][1000];
int flag[100]; 
int er[100][500];//��Ų���n������; 
struct po
{
    double number;
    int pos;
}s[100];
int a[100];//��ʾ��һ�����������У� 
int b[100];//��ʾ�ڶ������������У�
int s1[100];//��ʾ����f�������,�Һ�Ϊjob�ĸ��� 
int t[100];//ÿ��������Ҫ��ʱ��; 
FILE *out1;

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
    for(int i=0;i<n;i++)//����-4��4֮���ʵ��(��ȷ��С�������λ��ʵ��) 
    {
         s[i].number=(-400+rand()%(400-(-400)+1))/100.0 ;
         s[i].pos=i+1;
    }
    /*for(int i=0;i<n;i++)
     printf(" %lf %d ",s[i].number,s[i].pos);
     printf("\n"); */
    qsort(s,n,sizeof(s[0]),cmp);//***ʹ�ÿ������� 
}

void proc2(int n,int *order)
{
      proc1(n);
    for(int i=1;i<=n;i++)
      order[i]=s[i-1].pos;  //��ֵ����Ҫ��
    int reorder[100];//ÿ�β��������� 
    int reorder1[100];//�м�Ա����� 
    int rereorder[100];//��õ����У� 
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

void induce(int n,int *order)
{
      int i,temp;
      for(i=1;i<=n;i++)
     {
       order[i]=0;
       flag[i]=0;//��ʾ�����δ���� 
     }
     for(i=1;i<=n;i++)
     {     
        temp=1+rand()%n;
        while(flag[temp]==1)
         temp=1+rand()%n;
        order[i]=temp;
        flag[temp]=1;
     } 
}


int protime(int *a,int m,int step)
{
     memset(c,0,sizeof(c));
     c[a[1]][1]=mat[a[1]][1];    
     for(int i=2;i<=m;i++)
        c[a[i]][1]=c[a[i-1]][1]+mat[a[i]][1];
     for(int i=2;i<=step;i++)
        c[a[1]][i]=c[a[1]][i-1]+mat[a[1]][i];
     for(int i=2;i<=m;i++)
       for(int j=2;j<=step;j++)
          c[a[i]][j]=max(c[a[i-1]][j],c[a[i]][j-1])+mat[a[i]][j];
     return c[a[m]][step];    
}

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
      fprintf(out1,"%d ",s1[i]);
      fprintf(out1,"\n");
    
}

int main()
{
    freopen("Ta001_3.txt","r",stdin);
    int mmin=999999;   
    int job,step;
    int f;
    srand(time(0));
    out1=fopen("Ta001_3_result.txt","w");
        scanf("%d%d",&job,&step);
        scanf("%d",&f);
        for(int i=1;i<=job;i++)
          for(int j=1;j<=step*2;j++)
            scanf(" %d",&matrices[i][j]);
        for(int i=1;i<=job;i++)
          for(int j=1;j<=step;j++)
            mat[i][j]=matrices[i][j*2];
         for(int i=1;i<=job;i++)
         {
           for(int j=1;j<=step;j++)
             fprintf(out1,"%d ",mat[i][j]);
             fprintf(out1,"\n");
         }
        for(int i=1;i<=50;i++)
        {   
           int max=0;            
           induce(job,order);
           int sum=0;
           norder(job,f);
           for(int j=1;j<=f;j++) 
           {
               for(int p=1;p<=s1[j];p++)
               {
                  sum++;
                  er[j][p]=order[sum];
                  fprintf(out1," %d ",er[j][p]);
               }
               fprintf(out1,"\n");
           }
          for(int i=1;i<=f;i++) 
          {
             t[i]=protime(er[i],s1[i],step);
          }
          for(int i=1;i<=f;i++)
          {
            fprintf(out1,"t[%d]=%d\n",i,t[i]);
            if(t[i]>max)
              max=t[i];
          }         
          int result=max;
          if(result<mmin)
             mmin=result;
       }
       fprintf(out1,"result=%d\n",mmin);
       system("pause");
       return 0;
}
