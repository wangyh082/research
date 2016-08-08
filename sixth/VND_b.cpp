//This is for one individual,when processing time ,we calculate one factory's time,not one individual 
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>//设置随机数种子头文件
#include<math.h>
#include<string.h>
using namespace std;
struct po
{
    int s;
    int pos;
}jo[1000];//begin from 0 
int matrices[1000][1000];
int mat[1000][1000];
int disp[1000][1000];//dispatch the jobs to the factories
int c[1000][1000];
int a[1500];//
int b[1500];//when the insert function is applied,a & b are necessary
int fn[1000];//fn is the number of jobs in f
int ft[1000];//ft is the protime  in f
int order[1000];//the temp order
FILE *out1;
int job;
int step;
int f;
int cmax,cmin;//applied for LS_2
int x,y;//applied for LS_2 
int flag[1000];//flag for each factory

int cmp(const void *a,const void *b)
{
    po l1=*(po*)a;
    po l2=*(po*)b;
    int t=l1.s-l2.s;
    if(t<0)  return 1;
    else
      if(t>0) return -1;
    else
      {
              t=l1.pos-l2.pos;
              if(t>0) return 1;
              else return -1;
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

void insert(int *a,int n,int c,int d)//insert c into the d position 
{
    for(int i=1;i<=n;i++)
      b[i]=a[i];
    for(int i=n;i>=d;i--)
       b[i+1]=b[i];
       b[d]=c;
     for(int i=1;i<=n+1;i++)
       fprintf(out1,"%d ",b[i]);
       fprintf(out1,"\n");
} 

void proc5(int n,int i,int j,int *a)
{
     for(int ii=1;ii<=n;ii++)
       order[ii]=a[ii];
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
    fprintf(out1,"the inserted order:\n");
    for(int i=1;i<=n;i++)
     fprintf(out1," %d ",order[i]);
    fprintf(out1,"\n");
}

int remove(int *a,int p,int n)
{
     if(p==n)
     {
        n--;
        return n;
     }
     else
     {
         for(int i=p;i<=n-1;i++)
         {
              a[i]=a[i+1];
         }
         n--;
         return n;
     }
}

void rule2(int *fn,int *ft)
{
    int mark,mark1;
    int t;
    for(int i=1;i<=f;i++)
    {
      fn[i]=1;
      ft[i]=0;
    } 
    for(int i=1;i<=f;i++)
      disp[i][fn[i]]=jo[i-1].pos;
    for(int i=f+1;i<=job;i++)//dispatch the other jobs
    {
        int  min=999999;
        for(int j=1;j<=f;j++)
        {
           ft[j]=protime(disp[j],fn[j],step);
           fprintf(out1,"ft[%d]=%d\n",j,ft[j]);
        }
        for(int jj=1;jj<=f;jj++)
        {     
            for(int j=1;j<=fn[jj]+1;j++)
            {
               insert(disp[jj],fn[jj],jo[i-1].pos,j);
               t=protime(b,fn[jj]+1,step);
               fprintf(out1,"t=%d\n",t);
               if(t<min)
               {
                   min=t;
                   mark1=j;//mark1 is the last position
                   mark=jj;//mark is the position of the factory
               }
            }
        }
        fprintf(out1,"mark=%d,mark1=%d\n",mark,mark1);
        insert(disp[mark],fn[mark],jo[i-1].pos,mark1);
        fn[mark]++;//after inserted ,the number of factory
        //for(int i=1;i<=f;i++)
         // fprintf(out1,"fn[%d]=%d\n",i,fn[i]);
        for(int j=1;j<=fn[mark];j++)
          disp[mark][j]=b[j];
    } 
}

void find_x_y(int f,int &x,int &y,int disp[1000][1000],int fn[1000])
{
     memset(ft,0,sizeof(ft));
     int max=0;
     int min=999999;
     for(int i=1;i<=f;i++)
     {
         ft[i]=protime(disp[i],fn[i],step);
         if(ft[i]<min)
         {
              min=ft[i];
              x=i;
         }
         if(ft[i]>max)
         {
              max=ft[i];
              y=i;
         }
     }
     fprintf(out1,"x=%d y=%d min=%d max=%d\n",x,y,min,max);
}

bool criterion_b(int a,int aa,int b,int bb)
{
    if((a-aa)+(b-bb)>0)
       return true;
      return false; 
}

void LS_1(int ff,int disp[1000][1000],int fn[1000])
{
     int t;
     int min=9999999;
     int t1=protime(disp[ff],fn[ff],step);
     bool flag=true;
     int kk;
     while(flag)
     {
        flag=false;
        for(int j=1;j<=fn[ff];j++)
        {            
             for(int k=1;k<=fn[ff];k++)
             {                 
                 if(k!=j)
                 {
                    proc5(fn[ff],j,k,disp[ff]);//order is important
                    t=protime(order,fn[ff],step);
                    fprintf(out1,"t=%d\n",t);
                    if(t<min)
                    {
                         min=t;
                         kk=k;
                         for(int j=1;j<=fn[ff];j++)
                          disp[ff][j]=order[j];
                    } 
                 }
             }
          //  fprintf(out1,"min=%d kk=%d\n",min,kk);
            if(min<t1)
            {
               t1=min;
               flag=true;
               break;
            }  
        }
     }
}

int  LS_2(int y,int disp[1000][1000],int fn[1000])
{
     int cmax1=0;
     int cmin1=9999999;
     int t;
     int ii,jj,kk;
     for(int i=1;i<=fn[y];i++)
     {
          for(int j=1;j<=f;j++)
          {
               if(j!=y)
               {
                    for(int k=1;k<=fn[j]+1;k++)
                    {
                        insert(disp[j],fn[j],disp[y][i],k);
                        t=protime(b,fn[j]+1,step);
                       // fprintf(out1,"t=%d\n",t);
                        if(t>cmax1)
                        {
                             cmax1=t;
                        }
                        if(t<cmin1)
                        {
                            cmin1=t;
                            ii=i;//the first positon
                            jj=j;//factory
                            kk=k;//the last position
                        }
                    }
               } 
          }
     }
    fprintf(out1,"the last factory=%d the first position=%d the last positon =%d\n",jj,ii,kk);
    fprintf(out1,"cmax1=%d cmin1=%d\n",cmax1,cmin1);
    if(criterion_b(cmax,cmax1,cmin,cmin1))
    {
        insert(disp[jj],fn[jj],disp[y][ii],kk);
        fn[jj]++;
        for(int j=1;j<=fn[jj];j++)
        disp[jj][j]=b[j];
        int number=remove(disp[y],ii,fn[y]);
        fn[y]=number;        
        return 1;
    } 
    else
        return 0;
}

int main()
{ 
    freopen("Ta001_3.txt","r",stdin);
    int mmin=999999;   
    srand(time(0));
    out1=fopen("Ta001_3_result.txt","w");
        scanf("%d%d",&job,&step);
        scanf("%d",&f);
        memset(jo,0,sizeof(jo[0]));
        for(int i=1;i<=job;i++)
          for(int j=1;j<=step*2;j++)
            scanf(" %d",&matrices[i][j]);
        for(int i=1;i<=job;i++)
          for(int j=1;j<=step;j++)
            mat[i][j]=matrices[i][j*2];
         for(int i=1;i<=job;i++)
         {
           for(int j=1;j<=step;j++)
              jo[i-1].s+=mat[i][j];
           jo[i-1].pos=i;
           //fprintf(out1,"%d:%d\n",jo[i-1].pos,jo[i-1].s);
         }
         qsort(jo,job,sizeof(jo[0]),cmp);
         for(int i=1;i<=job;i++)
           fprintf(out1,"%d:%d\n",jo[i-1].pos,jo[i-1].s); //the descending order of jobs
         rule2(fn,ft);
         for(int i=1;i<=f;i++)
         {
            fprintf(out1,"f=%d:",i);
           for(int j=1;j<=fn[i];j++)
            fprintf(out1,"%d ",disp[i][j]);
            fprintf(out1,"\n");
         }//NEH2 initialization   
        bool impro=true;
        for(int i=1;i<=f;i++)
          flag[i]=1;
        while(impro)
        {
             for(int i=1;i<=f;i++)
             {
                 if(flag[i]==1)
                 {
                        LS_1(i,disp,fn);
                        flag[i]=0;
                 }
             }
                 for(int i=1;i<=f;i++)
               {
                    fprintf(out1,"f=%d:",i);
                   for(int j=1;j<=fn[i];j++)
                    fprintf(out1,"%d ",disp[i][j]);
                    fprintf(out1,"\n");
               }   
               find_x_y(f,x,y,disp,fn);
               cmax=ft[y];
               cmin=ft[x];
               int l=LS_2(y,disp,fn);
               if(l==1)
               {
                 flag[y]=1;
                 flag[x]=1;
               }
               else
                impro=false;     
        }        
        for(int i=1;i<=f;i++)
        {
            fprintf(out1,"f=%d:",i);
           for(int j=1;j<=fn[i];j++)
            fprintf(out1,"%d ",disp[i][j]);
            fprintf(out1,"\n");
        }  
        find_x_y(f,x,y,disp,fn);
        int result=ft[y];
        fprintf(out1,"the process time is=%d\n",result);      
        system("pause");
        return 0; 
}
