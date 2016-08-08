//This is for one population,when processing time ,we need to calculate one individual's time 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>//设置随机数种子头文件
#include<iostream>
#include<math.h>
#define M  1000
using namespace std;
int pop[20][50][M];//初始种群
int matrices[1000][1000];
int mat[1000][1000];
int disp[1000][1000];//dispatch the jobs to the factories 
int c[1000][1000];
int fn[1000];
int ft[1000];
int a[1500];//
int b[1500];//when the insert function is applied,a & b are necessary
int order[1000];
int s1[1000];
int fnn[1000][1000];//the jobs of the factory of all the population
int ftt[1000];//to calculate the minimum time of the ten better individuals
int temp1[5][1000][1000];//the temp population
int temp2[1000][1000];//the sequences to be the VND process
int solution[1000][1000];//the solution after 50 times experiments
int so[1000];//mark the length of jobs of each factory
int tt[1000];//the time of the initial individuals
FILE *out1;
struct po
{
    int s;
    int pos;
}jo[1000];//begin from 0
int job;
int step;
int f;
int cmax,cmin;

int protime(int *a,int m,int step)//the suffix of one job begins from 1
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

int protime1(int f,int k,int kk)//calculate one individual's time,k is different from kk
//k is the kind of temp1,kk is the number of the population
{   
     int max=0;
     int t;    
     for(int i=1;i<=f;i++)
     {
          t=protime(temp1[k][i],fnn[kk][i],step);
          if(t>max)
          max=t;                                      
     }
     return max; 
}

void protime2(int f)
{   
     int max=0;
     int t;
     for(int k=1;k<=10;k++)  
     {  
         for(int i=1;i<=f;i++)
         {
              t=protime(pop[k][i],fnn[k][i],step);
              if(t>max)
              max=t;                                      
         }
        tt[k]=max;
    }
   // for(int k=1;k<=10;k++) 
     // fprintf(out1,"tt[%d]=%d ",k,tt[k]); 
}

void insert(int *a,int n,int c,int d)//insert c into the d position 
{
    for(int i=1;i<=n;i++)
      b[i]=a[i];
    for(int i=n;i>=d;i--)
       b[i+1]=b[i];
       b[d]=c;
    /* for(int i=1;i<=n+1;i++)
       fprintf(out1,"%d ",b[i]);
       fprintf(out1,"\n");*/
} 


void remove(int *a,int p,int n)
{
     if(p==n)
     {
        return ;
     }
     else
     {
         for(int i=p;i<=n-1;i++)
         {
              a[i]=a[i+1];
         }
         return ;
     }
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
   /* fprintf(out1,"the inserted order:\n");
    for(int i=1;i<=n;i++)
     fprintf(out1," %d ",order[i]);
    fprintf(out1,"\n");*/
}

void induce(int n,int *order)
{
      int i,temp;
      int flag[1000];
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

void rule1(int *fn,int *ft)
{
    memset(disp,0,sizeof(disp));
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
        int  min=9999999;
        int  min1=999999;
        for(int j=1;j<=f;j++)
        {
           ft[j]=protime(disp[j],fn[j],step);
           //fprintf(out1,"ft[%d]=%d\n",j,ft[j]);
           if(ft[j]<min)
           {
              min=ft[j];
              mark=j;
           }
        }//find the min factory,then insert the job into it 
        //fprintf(out1,"min=%d,mark=%d\n",min,mark);       
        for(int j=1;j<=fn[mark]+1;j++)
        {
           insert(disp[mark],fn[mark],jo[i-1].pos,j);
           t=protime(b,fn[mark]+1,step);
           if(t<min1)
           {
               min1=t;
               mark1=j;//mark1 is the last position
           }
        }
        insert(disp[mark],fn[mark],jo[i-1].pos,mark1);
        fn[mark]++;//after inserted ,the number of factory
        //for(int i=1;i<=f;i++)
         // fprintf(out1,"fn[%d]=%d\n",i,fn[i]);
        for(int j=1;j<=fn[mark];j++)
          disp[mark][j]=b[j];
    } 
}

void rule2(int *fn,int *ft)
{ 
    memset(disp,0,sizeof(disp));
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
           //fprintf(out1,"ft[%d]=%d\n",j,ft[j]);
        }
        for(int jj=1;jj<=f;jj++)
        {     
            for(int j=1;j<=fn[jj]+1;j++)
            {
               insert(disp[jj],fn[jj],jo[i-1].pos,j);
               t=protime(b,fn[jj]+1,step);
               //fprintf(out1,"t=%d\n",t);
               if(t<min)
               {
                   min=t;
                   mark1=j;//mark1 is the last position
                   mark=jj;//mark is the position of the factory
               }
            }
        }
        //fprintf(out1,"mark=%d,mark1=%d\n",mark,mark1);
        insert(disp[mark],fn[mark],jo[i-1].pos,mark1);
        fn[mark]++;//after inserted ,the number of factory
        //for(int i=1;i<=f;i++)
         // fprintf(out1,"fn[%d]=%d\n",i,fn[i]);
        for(int j=1;j<=fn[mark];j++)
          disp[mark][j]=b[j];
    } 
}

int norder(int m,int n)//m is the number of jobs ,n is the number of factories;
{
    int sum=0;
    int temp;
    int flag=0;
    for(int i=1;i<=n;i++)
    {
       s1[i]=1;
    } 
    if(m==n)
    {
        flag=1;    
    }
    if(flag==0)
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
    flag=0;
    /*for(int i=1;i<=n;i++)
      fprintf(out1,"%d ",s1[i]);
      fprintf(out1,"\n");*/
    
}

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

void display(int k)
{
      for(int i=1;i<=f;i++)
     {
           fprintf(out1,"f=%d:",i);
           for(int j=1;j<=fnn[k][i];j++)
           {
             fprintf(out1,"%d ",pop[k][i][j]);                 
           }
           fprintf(out1,"\n");
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
   //  fprintf(out1,"x=%d y=%d min=%d max=%d\n",x,y,min,max);
}

bool criterion_a(int a,int aa,int b,int bb)
{
     if(aa<a&&bb<a)
       return true;
      return false; 
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
     int t1=protime(disp[ff],fn[ff],step);
     int min=99999999;
     //fprintf(out1,"min=%d",min);
     bool flag=true;
     int kk;
     while(flag)
     {
        flag=false;
        for(int j=1;j<=fn[ff];j++)
        {            
             for(int k=1;k<=fn[ff];k++)
             {                 
                    proc5(fn[ff],j,k,disp[ff]);//order is important
                    t=protime(order,fn[ff],step);
                  //  fprintf(out1,"t=%d\n",t);
                    if(t<min)
                    {
                         min=t;
                         kk=k;
                         for(int j=1;j<=fn[ff];j++)
                          disp[ff][j]=order[j];
                    }
             }
           // fprintf(out1,"min=%d kk=%d\n",min,kk);
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
   // fprintf(out1,"the last factory=%d the first position=%d the last positon =%d\n",jj,ii,kk);
  //  fprintf(out1,"cmax1=%d cmin1=%d\n",cmax1,cmin1);
    if(criterion_b(cmax,cmax1,cmin,cmin1))
    {
        insert(disp[jj],fn[jj],disp[y][ii],kk);
        fn[jj]++;
        for(int j=1;j<=fn[jj];j++)
        disp[jj][j]=b[j];
        remove(disp[y],ii,fn[y]);
        fn[y]--;        
        return 1;
    } 
    else
        return 0;
}

int main()
{
    freopen("Ta001_3.txt","r",stdin);  
    srand(time(0));
    out1=fopen("Ta001_3_resultt.txt","w");
        scanf("%d%d",&job,&step);
        scanf("%d",&f);
        memset(jo,0,sizeof(jo[0]));
        for(int i=1;i<=job;i++)
          for(int j=1;j<=step*2;j++)
            scanf(" %d",&matrices[i][j]);
        for(int i=1;i<=job;i++)
          for(int j=1;j<=step;j++)
            mat[i][j]=matrices[i][j*2];
            //begin to initialize the population 
            memset(fnn,0,sizeof(fnn));
             for(int k=1;k<=3;k++)
             {
                 induce(job,order);
                 for(int i=1;i<=job;i++)
                 {
                      jo[i-1].pos=order[i];
                      jo[i-1].s=0;
                 }
                 rule1(fn,ft);
                 for(int i=1;i<=f;i++)
                 fnn[k][i]=fn[i];
                /*  for(int i=1;i<=f;i++)
                 {
                    fprintf(out1,"f=%d:",i);
                   for(int j=1;j<=fn[i];j++)
                    fprintf(out1,"%d ",disp[i][j]);
                    fprintf(out1,"\n");
                 }*/
                 //fprintf(out1,"k=%d\n",k);
                  for(int i=1;i<=f;i++)
                 {
                   // fprintf(out1,"f=%d:",i);
                   for(int j=1;j<=fnn[k][i];j++)
                   {
                     pop[k][i][j]=disp[i][j];
                    // fprintf(out1,"%d ",pop[k][i][j]);                    
                   } 
                  // fprintf(out1,"\n");
                 }                
             }
               for(int k=4;k<=6;k++)
             {
                 induce(job,order);
                 for(int i=1;i<=job;i++)
                 {
                      jo[i-1].pos=order[i];
                      jo[i-1].s=0;
                 }
                 rule2(fn,ft);
                 for(int i=1;i<=f;i++)
                  fnn[k][i]=fn[i];               
                /*  for(int i=1;i<=f;i++)
                 {
                    fprintf(out1,"f=%d:",i);
                   for(int j=1;j<=fn[i];j++)
                    fprintf(out1,"%d ",disp[i][j]);
                    fprintf(out1,"\n");
                 }*/
                 //fprintf(out1,"k=%d\n",k);
                  for(int i=1;i<=f;i++)
                 {
                   // fprintf(out1,"f=%d:",i);
                   for(int j=1;j<=fnn[k][i];j++)
                   {
                     pop[k][i][j]=disp[i][j];
                   //  fprintf(out1,"%d ",pop[k][i][j]);                 
                   }
                  // fprintf(out1,"\n");
                 }                  
             }
             for(int i=1;i<=job;i++)
             {
               for(int j=1;j<=step;j++)
                  jo[i-1].s+=mat[i][j];
               jo[i-1].pos=i;
              // fprintf(out1,"%d:%d\n",jo[i-1].pos,jo[i-1].s);
             }             
             qsort(jo,job,sizeof(jo[0]),cmp);
            // for(int i=1;i<=job;i++)
              // fprintf(out1,"%d:%d\n",jo[i-1].pos,jo[i-1].s); //the descending order of jobs
             rule1(fn,ft);
             for(int i=1;i<=f;i++)
              fnn[7][i]=fn[i];
             //fprintf(out1,"k=7\n");
            for(int i=1;i<=f;i++)
             {
                //fprintf(out1,"f=%d:",i);
               for(int j=1;j<=fnn[7][i];j++)
               {
                 pop[7][i][j]=disp[i][j];
                // fprintf(out1,"%d ",pop[7][i][j]);                 
               }
               //fprintf(out1,"\n");
             } 
             //for(int i=1;i<=job;i++)
             //  fprintf(out1,"%d:%d\n",jo[i-1].pos,jo[i-1].s); //the descending order of jobs
             rule2(fn,ft);
             for(int i=1;i<=f;i++)
              fnn[8][i]=fn[i];
              //fprintf(out1,"k=8\n"); 
               for(int i=1;i<=f;i++)
             {
               // fprintf(out1,"f=%d:",i);
               for(int j=1;j<=fnn[8][i];j++)
               {
                 pop[8][i][j]=disp[i][j];
                // fprintf(out1,"%d ",pop[8][i][j]);                 
               }
               //fprintf(out1,"\n");
             } 
             for(int k=9;k<=10;k++)
             {
                 induce(job,order);
                 int sum=0;
                 norder(job,f);
                 for(int i=1;i<=f;i++)
                  fnn[k][i]=s1[i];
                // fprintf(out1,"k=%d\n",k);
               for(int j=1;j<=f;j++) 
               {
                   for(int p=1;p<=s1[j];p++)
                   {
                      sum++;
                      disp[j][p]=order[sum];
                     // fprintf(out1," %d ",disp[j][p]);
                   }
                  // fprintf(out1,"\n");
               }
                  for(int i=1;i<=f;i++)
                 {
                    //fprintf(out1,"f=%d:",i);
                   for(int j=1;j<=fnn[k][i];j++)
                   {
                     pop[k][i][j]=disp[i][j];
                    // fprintf(out1,"%d ",pop[k][i][j]);                    
                   } 
                   //fprintf(out1,"\n");
                 }  
             } 
           //ending of the initialization of the population
          //begin to do the changes
         // fprintf(out1,"begin to do the changes\n");
          int num[2];//the first way needs two random numbers 
          srand(time(0));          
          //int kkk;
          int t;  
          //int final=999999;
          int min2=999999;
        for(int i=1;i<=100;i++)
      {
            fprintf(out1,"i=%d\n",i);
           /* for(int k=1;k<=10;k++)
            {
            for(int i=1;i<=f;i++)
             {
                fprintf(out1,"f=%d:",i);
               for(int j=1;j<=fnn[k][i];j++)
               {
                 fprintf(out1,"%d ",pop[k][i][j]);                    
               } 
               fprintf(out1,"\n");
             }  
            }*/
            memset(temp1,0,sizeof(temp1));
            memset(ftt,0,sizeof(ftt));            
            int result=0;//the best of the ten individuals to be the VND process
            memset(tt,0,sizeof(tt));
            protime2(f); 
          for(int k=1;k<=10;k++)
          {     
              int kkk=0;
              int min1=tt[k];
              //fprintf(out1,"min1=%d\n",min1);        
              for(int i=1;i<=f;i++)//the first way
              {
                   for(int j=1;j<=fnn[k][i];j++)
                      temp1[1][i][j]=pop[k][i][j];
                   if(fnn[k][i]==1) 
                   {
                         num[1]=1;
                         num[2]=1;
                   }
                   else
                   {
                      for(int j=1;j<=2;j++)
                       {
                          num[j]=1+rand()%fnn[k][i];
                       }
                      while(num[1]==num[2])                                                      
                       {                    
                          num[2]=1+rand()%fnn[k][i];                                 
                       }
                          /*for(int j=1;j<=2;j++)
                          fprintf(out1,"num[%d]=%d ",j,num[j]);
                          fprintf(out1,"\n");*/
                    }
                       swap(temp1[1][i][num[1]],temp1[1][i][num[2]]);
                      /* for(int kk=1;kk<=fnn[k][i];kk++)
                       fprintf(out1,"%d ",temp1[1][i][kk]);
                       fprintf(out1,"\n");  */                                                           
              } 
               t=protime1(f,1,k);
              // fprintf(out1,"k=1 time=%d\n",t);
               if(t<min1)
               {
                    min1=t;
                    kkk=1;
               } 
              // fprintf(out1,"kkk=%d min1=%d\n",kkk,min1);            
             // display(k); //the original population               
              for(int i=1;i<=f;i++)//the second way
              {
                  for(int j=1;j<=fnn[k][i];j++)
                     temp1[2][i][j]=pop[k][i][j];
                  int aa=1+rand()%fnn[k][i];
                  int bb=1+rand()%fnn[k][i];
                  while(a==b)
                    bb=1+rand()%fnn[k][i];
                // fprintf(out1,"aa=%d bb=%d\n",aa,bb);
                 proc5(fnn[k][i],aa,bb,temp1[2][i]);
                 for(int j=1;j<=fnn[k][i];j++)
                     temp1[2][i][j]=order[j];
                /* for(int kk=1;kk<=fnn[k][i];kk++)
                    fprintf(out1,"%d ",temp1[2][i][kk]);
                    fprintf(out1,"\n");*/
             }
             t=protime1(f,2,k);
             //fprintf(out1,"k=2 time=%d\n",t);
             if(t<min1)
             {
                min1=t;
                kkk=2;
             }
             //fprintf(out1,"kkk=%d min1=%d\n",kkk,min1); 
              //display(k); 
              for(int i=1;i<=f;i++)//the third way
              {
                  for(int j=1;j<=fnn[k][i];j++)
                    temp1[3][i][j]=pop[k][i][j];
                  int nu;
                  nu=1+rand()%fnn[k][i];
                  if(nu==fnn[k][i])
                  {
                    swap(temp1[3][i][nu],temp1[3][i][1]);    
                  }
                  else
                  {
                    swap(temp1[3][i][nu],temp1[3][i][nu+1]);
                  }
                /*  for(int kk=1;kk<=fnn[k][i];kk++)
                    fprintf(out1,"%d ",temp1[3][i][kk]);
                    fprintf(out1,"\n");*/
             }
               t=protime1(f,3,k);
              // fprintf(out1,"k=3 time=%d\n",t);
               if(t<min1)
               {
                    min1=t;
                    kkk=3;
               }
               //fprintf(out1,"kkk=%d min1=%d\n",kkk,min1);       
              //display(k);
              int max=0;
              int y;
              int t1;
              for(int i=1;i<=f;i++)//the fourth way
              {
                   for(int j=1;j<=fnn[k][i];j++)
                     temp1[4][i][j]=pop[k][i][j];
                   t1=protime(temp1[4][i],fnn[k][i],step);
                   if(t1>max)
                   {
                        max=t1;
                        y=i;//the first factory
                   }
              }
                int nu1;//the last factory
                int posit1,posit2;//the other two positions               
              nu1=1+rand()%f;
              while(nu1==y)
              nu1=1+rand()%f;
              posit1=1+rand()%fnn[k][y];//the first position
              posit2=1+rand()%fnn[k][nu1];//the last position
             // fprintf(out1,"y=%d nu1=%d posit1=%d posit2=%d\n",y,nu1,posit1,posit2);
              insert(temp1[4][nu1],fnn[k][nu1],temp1[4][y][posit1],posit2);
              fnn[k][nu1]++;
              for(int i=1;i<=fnn[k][nu1];i++)
                temp1[4][nu1][i]=b[i];
              remove(temp1[4][y],posit1,fnn[k][y]);   
              fnn[k][y]--;
            /* for(int i=1;i<=f;i++)
              {
                 fprintf(out1,"f=%d:",i);
                for(int j=1;j<=fnn[k][i];j++)
                 fprintf(out1,"%d ",temp1[4][i][j]);
                 fprintf(out1,"\n");
              }*/
              t=protime1(f,4,k);
             // fprintf(out1,"k=4 time=%d\n",t);
              if(t<min1)
              {
                   min1=t;
                   kkk=4;
              }
              //fprintf(out1,"kkk=%d min1=%d\n",kkk,min1);
              if(kkk!=4)
              {
                fnn[k][nu1]--;
                fnn[k][y]++;  
              }
              if(kkk!=0)
              {
                  for(int i=1;i<=f;i++)
                    for(int j=1;j<=fnn[k][i];j++)
                    pop[k][i][j]=temp1[kkk][i][j];
              }
                    //fprintf(out1,"kkk=%d min1=%d\n",kkk,min1);
                    ftt[k]=min1;                                       
       } 
       int flag11=0;
       for(int k=1;k<=10;k++)//find the minimum of the ten individuals
       {
          // fprintf(out1,"ftt[%d]=%d\n",k,ftt[k]);
           if(ftt[k]<min2)
           {
                 min2=ftt[k];
                 result=k;
                // flag11=1;
           }
          // display(k);
       }
     // fprintf(out1,"min2=%d,result=%d\n",min2,result);
    //begin the VND process
     /* if(flag11==1)//if there is no one to be better,which one to choose to VND process
      {
          for(int i=1;i<=f;i++)
            for(int j=1;j<=fnn[result][i];j++)
             temp2[i][j]=pop[result][i][j];         
                   /*  for(int i=1;i<=f;i++)
                   {
                        fprintf(out1,"f=%d:",i);
                        t=protime(temp2[i],fnn[result][i],step);
                        fprintf(out1,"t=%d\n",t);
                       for(int j=1;j<=fnn[result][i];j++)
                        fprintf(out1,"%d ",temp2[i][j]);
                        fprintf(out1,"\n");
                   }  */ 
          /*bool impro=true;
          int x,y;
          int flag[1000];
            for(int i=1;i<=f;i++)
              flag[i]=1;
            while(impro)
            {
                 for(int i=1;i<=f;i++)
                 {
                     if(flag[i]==1)
                     {
                            LS_1(i,temp2,fnn[result]);
                          /*  for(int ii=1;ii<=f;ii++)
                            {
                                fprintf(out1,"f=%d:",ii);
                               for(int j=1;j<=fnn[result][i];j++)
                                fprintf(out1,"%d ",temp2[ii][j]);
                                fprintf(out1,"\n");
                            } */ 
                           /* flag[i]=0;
                     }
                 }
                   find_x_y(f,x,y,temp2,fnn[result]);
                   cmax=ft[y];
                   cmin=ft[x];
                   int l=LS_2(y,temp2,fnn[result]);
                  // fprintf(out1,"l=%d\n",l);
                   if(l==1)
                   {
                     flag[y]=1;
                     flag[x]=1;
                   }
                   else
                    impro=false;     
            }  */      
           /* for(int i=1;i<=f;i++)
            {
                fprintf(out1,"f=%d:",i);
               for(int j=1;j<=fnn[result][i];j++)
                fprintf(out1,"%d ",temp2[i][j]);
                fprintf(out1,"\n");
            } */
            /*find_x_y(f,x,y,temp2,fnn[result]);
            int last=ft[y];
            if(last<min2)
            {
                 min2=last;        
                 for(int i=1;i<=f;i++)
                {
                   for(int j=1;j<=fnn[result][i];j++)              
                    pop[result][i][j]=temp2[i][j];
                } 
               
            }*/
           // ftt[result]=min2;                                                   
           /* for(int i=1;i<=f;i++)
            {
                fprintf(out1,"f=%d:",i);
               for(int j=1;j<=fnn[result][i];j++)
                fprintf(out1,"%d ",pop[result][i][j]);
                fprintf(out1,"\n");
            }*/
           // flag11=0;
        }
        fprintf(out1,"the last process time is=%d\n",min2);
        /*if(min2<final)
        {
           final=min2;
           for(int i=1;i<=f;i++)
           {
               for(int j=1;j<=fnn[result][i];j++)
               {
                  solution[i][j]=pop[result][i][j];
                  so[i]=fnn[result][i];
               }
            }
        } */          
   // }
    /*fprintf(out1,"final solution value is=%d\n",final);
    fprintf(out1,"final solution is:\n");
    for(int i=1;i<=f;i++)
    {
            fprintf(out1,"f=%d:",i);
           for(int j=1;j<=so[i];j++)
            fprintf(out1,"%d ",solution[i][j]);
            fprintf(out1,"\n");
    }*/
    system("pause");
    return 0;
}
