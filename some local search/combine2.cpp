#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>//�������������ͷ�ļ� 
#include<algorithm>
using namespace std;

int matrices[100][100];
int order[100]; //�����һ������,��pos�����ֵ����order��order�±��1��ʼ 
int flag[100]; 
int finalor[100];//һ����������õ����� 
int ffinalor[100];//100����������õ����� 
int reorder[100];//ÿ�β����Ĵ���
int rereorder[100];//��õ����У�
int reorder1[100]; 
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
    //for(int i=0;i<n;i++)
     //  printf(" %d ",pos[i]);
   // printf("\n");
   // for(int i=0;i<n;i++)
    //   printf(" %lf ",number[i]);
    //printf("\n");
}

void proc2(int n,int *order)
{
    int sum11;//��ʼ�����к�
    int sum2[120];//�Ƚϵĺ� 
    int sum22;
    int i,j,ii,jj,kk;
    int p;
    int temp;
    proc1(n);
    for(int i=1;i<=n;i++)
      order[i]=pos[i-1];   
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

int proc(int n)//���1��ʼ����
{
     int i,temp;
     int max=0; 
     int sum1,sum2;
     for(i=1;i<=n;i++)
     {
       finalor[i]=0; 
     }
     //srand(time(0));
    /* for(i=1;i<=n;i++)
     {     
       temp=1+rand()%n;
        while(flag[temp]==1)
         temp=1+rand()%n;
        order[i]=temp;
        flag[temp]=1;
     } */
     //sort(order,order+n+1);
     proc2(n,order);//������������� 
     //for(int i=1;i<=n;i++)
     //  printf(" %d ",order[i]);//����������� 
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
    out1=fopen("result1","w");
    for(int j=1;j<=n;j++)
       ffinalor[j]=0;
    srand(time(0));  
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
//��ΪNEH��update_lop�Ľ�� 
/*
4
0 1 2 3
4 0 5 6
7 9 0 9
8 8 9 0
*/
