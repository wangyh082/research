#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>//设置随机数种子头文件
#include<string.h>
#define NP 20
#define M 50
using namespace std;
int order[100];//把pos数组的值赋给order，order下标从1开始  
int matrices[100][100];
int flag[100]; 
struct po
{
    double number;
    int pos;
}s[100];
int pop[M][100];//开始的种群 
int r[4];//产生两个随机数的数组； 
int last[M][100];//对待一个个体时，产生三个序列中最好的序列,是一个中间数据 
int best[M];//NP个最优解的数组； 
int fibest[100];//在proc4的比较最优序列 
int result[100];//最后求的最优解的序列 
int firesult[100];//400次循环中最优解
int tem[100];//在主函数的交换步骤中作为中间数组； 
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
    for(int i=0;i<n;i++)//生成-4到4之间的实数(精确到小数点后两位的实数) 
    {
         s[i].number=(-400+rand()%(400-(-400)+1))/100.0 ;
         s[i].pos=i+1;
    }
    /*for(int i=0;i<n;i++)
     printf(" %lf %d ",s[i].number,s[i].pos);
     printf("\n"); */
    qsort(s,n,sizeof(s[0]),cmp);//***使用快速排序 
}

void proc2(int n,int *order)
{
      proc1(n);
    for(int i=1;i<=n;i++)
      order[i]=s[i-1].pos;  //赋值很重要；
    int reorder[100];//每次插入后的序列 
    int reorder1[100];//中间对比序列 
    int rereorder[100];//最好的序列； 
    int sum11;//初始的序列和
    int sum2[120];//比较的和 
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
                //reorder数组的长度是i+1;
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
     printf(" %d ",order[i]);//最后的序列 
     printf("\n");*/
}

void induce(int n,int *order)
{
      int i,temp;
      for(i=1;i<=n;i++)
     {
       order[i]=0;
       flag[i]=0;//表示这个数未生成 
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
    /*fprintf(out1,"the inserted order:\n");
    for(int i=1;i<=n;i++)
     fprintf(out1," %d ",order[i]);
    fprintf(out1,"\n");   */  
}

void GetSecondMaxNumber(int *arr,int n,int &ii,int &jj,int &max,int &second_max)  
{  
    int i ;  
    max = arr[0];  
    second_max = 0x80000000;    
    for(i = 1 ; i < n ; ++i)  
    {  
        if(arr[i] > max)  
        {  
            second_max = max;  
            max = arr[i]; 
            ii=i; 
        }  
        else if(arr[i]<max)   
        {  
            if(arr[i] > second_max) 
            { 
                second_max = arr[i]; 
                jj=i;
            } 
        }  
    }  
   // printf("max %d = %d,second_max %d= %d\n",ii,max,jj,second_max);
}//找最优解和次优解 

 
int  proc4(int n,int *best1)
{     
     int temp;  
     int init; 
     for(int i=1;i<=n*(n-1);i++)
     {
           /*for(int j=1;j<=n;j++)
             fprintf(out1," %d ",best1[j]);
             fprintf(out1,"\n");*/
            init=addsum(n,best1);
            //fprintf(out1,"init=%d\n",init);
            for(int j=1;j<=n;j++)
            {
                flag[j]=0;
            }
            for(int j=1;j<=2;j++) 
             {     
                temp=1+rand()%n;
                while(flag[temp]==1)
                 temp=1+rand()%n;
                r[j]=temp; 
                flag[temp]=1;
             } //产生两个随机数，作为交换的位置；把r[2]插入到r[1]的位置；
            //fprintf(out1,"r[1]=%d r[2]=%d\n",r[1],r[2]);
            int sub1;
            int obj1;
            sub1=obj_func(r[2],r[1],best1);
            //fprintf(out1,"sub1=%d\n",sub1);
            obj1=init-sub1;
           // fprintf(out1,"obj1=%d\n",obj1);
            if(obj1>init)
            {
               init=obj1;
               proc5(n,r[2],r[1],best1);
               for(int j=1;j<=n;j++)
                  fibest[j]=best1[j];
            }
            else
            {
               for(int j=1;j<=n;j++)
                fibest[j]=best1[j];
            }
            /* for(int j=1;j<=n;j++)
             fprintf(out1," %d ",fibest[j]);
             fprintf(out1,"\n");*/
            for(int j=1;j<=n;j++)
               best1[j]=fibest[j];
     }
     for(int i=1;i<=n;i++)
         fibest[i]=best1[i];
    // fprintf(out1,"******init=%d**********\n",init);
     return init;  
}

int main()
{
    freopen("N-atp48","r",stdin);
    int mmax=0; 
    int n;
    int temp,init;
    srand(time(0));
    out1=fopen("result--N-atp48","w");
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
          for(int j=1;j<=n;j++)
            scanf("%d",&matrices[i][j]);
         proc2(n,order);
         for(int i=1;i<=n;i++)
            pop[1][i]=order[i];   
         for(int i=2;i<=NP;i++)
         {  
           //srand(time(0));              
           induce(n,order);            
           for(int j=1;j<=n;j++)
             pop[i][j]=order[j]; 
          // Sleep(1000);
         }
         for(int i=1;i<=NP;i++)
         {
           for(int j=1;j<=n;j++)
             fprintf(out1," %d ",pop[i][j]);
             fprintf(out1,"\n");
         }//产生NP个互不相同的序列；         
         int obj1,obj2; 
         int i;
      for(int p=1;p<=200;p++)
     { 
         memset(best,0,sizeof(best));//记录产生最大的；
         for(i=1;i<=NP;i++)
         {
              init=addsum(n,pop[i]);
             // fprintf(out1,"pop[%d]:init=%d\n",i,init);
              for(int j=1;j<=n;j++)
             { 
               flag[j]=0;//表示这个数未生成
             }
             for(int j=1;j<=2;j++) 
             {     
                temp=1+rand()%n;
                while(flag[temp]==1)
                 temp=1+rand()%n;
                r[j]=temp; 
                flag[temp]=1;
             } //产生两个随机数，作为交换的位置；把r[2]插入到r[1]的位置；
           // fprintf(out1,"r[1]=%d r[2]=%d\n",r[1],r[2]);
            int sub1,sub2;
            sub1=obj_func(r[2],r[1],pop[i]);
            obj1=init-sub1;
           // fprintf(out1,"**obj1=%d***\n",obj1);
            if(obj1>init)
            {
               best[i]=obj1;
               for(int j=1;j<=n;j++)
                  tem[j]=pop[i][j];
               proc5(n,r[2],r[1],tem);
               for(int j=1;j<=n;j++)
                last[i][j]=tem[j];
            }
            else
            {
               best[i]=init;
               for(int j=1;j<=n;j++)
                last[i][j]=pop[i][j];
            }
            //printf("obj1=%d\n",obj1);
            int temp;
            temp=1+rand()%n;
            int flag3=0;
          //  fprintf(out1,"temp=%d\n",temp);
            if(temp<=n-1)
            sub2=obj_func(temp,temp+1,pop[i]);
            else  if(temp==n)
            {
              sub2=obj_func(n,1,pop[i]);
              flag3=1;
            }
            obj2=init-sub2;
            //fprintf(out1,"obj2=%d\n",obj2);
            if(obj2>best[i]) 
            {
               best[i]=obj2;
               for(int j=1;j<=n;j++)
                  tem[j]=pop[i][j]; 
               if(flag3==1)
               {                 
                   proc5(n,n,1,tem);
                   flag3=0;
               }
               else
               proc5(n,temp,temp+1,tem);
               for(int j=1;j<=n;j++)
                last[i][j]=tem[j];
            }
            /*else
            {
                for(int j=1;j<=n;j++)
                last[i][j]=pop[i][j];
            }*/
            /*fprintf(out1,"best[%d]=%d\n",i,best[i]);
            for(int j=1;j<=n;j++)
              fprintf(out1," %d ",last[i][j]);
              fprintf(out1,"\n");*/
            for(int j=1;j<=n;j++)
              pop[i][j]=last[i][j];           
        }//产生NP个best解以及序列；
        int ii,jj,max,second_max; 
        GetSecondMaxNumber(best,NP,ii,jj,max,second_max);
       // fprintf(out1,"ii=%d,max=%d,jj=%d,second_max=%d\n",ii,max,jj,second_max); 
        double rand1;
        rand1=rand()%10/10.0;
        int bbest1,bbest2,bbbest;
        bbest1=0;
        bbest2=0;
        bbbest=0;
        int flag1,flag2;
        flag1=0;
        flag2=0;
       // fprintf(out1,"rand1=%lf\n",rand1);    
        if(rand1<0.5)
        {
              bbest1=proc4(n,pop[ii]);                
        }
        else
        {
              bbest2=proc4(n,pop[jj]);
        }
      //  fprintf(out1,"bbest1=%d,bbest2=%d,max=%d\n",bbest1,bbest2,max);
        if(rand1<0.5)
        {
            if(bbest1>max)
            { 
               bbbest=bbest1;
               for(int i=1;i<=n;i++)
                  result[i]=fibest[i];
                  flag1=1;
            }
            else
            {
                 bbbest=max;
                for(int i=1;i<=n;i++)
                  result[i]=pop[ii][i];
            }
       }
        else
       { 
            if(bbest2>max)
            {
                bbbest=bbest2;
                for(int i=1;i<=n;i++)
                  result[i]=fibest[i];
                  flag2=1;
            }
            else 
            {
                bbbest=max;
                for(int i=1;i<=n;i++)
                  result[i]=pop[ii][i];
            }
       }
        fprintf(out1,"bbbest=%d\n",bbbest);
        for(int i=1;i<=n;i++)
          fprintf(out1," %d ",result[i]);
          fprintf(out1,"\n");
         if(bbbest>mmax)
         {
              mmax=bbbest;
            for(int i=1;i<=n;i++)
              firesult[i]=result[i];
         }        
         if(flag2==1)
         {
               for(int j=1;j<=n;j++)
               pop[jj][j]=result[j];
               flag2=0;             
        }
        else 
        {
              for(int j=1;j<=n;j++)
               pop[ii][j]=result[j];
               flag1=0;
        }
    }
    fprintf(out1,"mmax=%d\n",mmax);
    for(int i=1;i<=n;i++)
      fprintf(out1," %d ",firesult[i]);
      fprintf(out1,"\n");
    system("pause");
    return 0;
}
//模块化
