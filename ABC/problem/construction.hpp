/*int norder(int m,int n,int *s1)//m is the number of jobs ,n is the number of factories;
{
    int sum=0;
    int temp;
    int f;
    for(int i=1;i<=n;i++)
    {
       s1[i]=0;
    } 
    if(n==1)
       s1[n]=m;
    else
    {
        for(int i=1;i<n;i++)
        {
                temp=rand()%(m-sum);
                s1[i]=temp;
                sum+=temp;   
        }  
        s1[n]=m-sum;
    }    
}
void induce(int n,int *order)
{
      int i,temp;
      int flag[n];
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
}*/
struct po
{
    double number;
    int pos;
};
int FoodNumber;
int ub[200],lb[200];
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

void proc(int n,int m,po s[200])// n is the number of jobs,m is the sm[i]
{
    double a;
    for(int i=1;i<=n;i++)//生成1到sm[i]+1之间的实数(精确到小数点后两位的实数) 
    {
       loop:a=(100+rand()%((m+1)*100-100+1))/100.0 ;
            if(a==(m*1.0+1))
            goto loop;
            if(i>1)
            {
              if(a==s[i-1].number)
              goto loop;
            }
            s[i].number=a;
            s[i].pos=i;        
    } 
    /*for(int i=1;i<=n;i++)
    fprintf(file," %lf %d ",s[i].number,s[i].pos);
    fprintf(file,"\n"); */
    qsort(s,n+1,sizeof(s[1]),cmp);//***使用快速排序 
    /*for(int i=1;i<=n;i++)
    fprintf(file," %lf %d ",s[i].number,s[i].pos);
    fprintf(file,"\n"); */  
}


void division(double foods[FoodNumber][2000],double so[1000],int i,int neighbour,int J,int S,po solution[10][1000])
{
    double r;
    int k,j;
    int m;
    int param2change;
    r = ((double)rand() / ((double)(RAND_MAX)+(double)(1)) );
    param2change=(int)(r*((J*S)-1)+1);
    r = ((double)rand() / ((double)(RAND_MAX)+(double)(1)) );
    so[param2change]=foods[i][param2change]+(foods[i][param2change]-foods[neighbour][param2change])*(r-0.5)*2;
   for(j=1;j<=S;j++)
   {
        for(k=1;k<=J;k++)
        {
            m=(j-1)*J+k;
            while (so[m]<lb[j])
            {
                r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                so[m]=r*(ub[j]-lb[j])+lb[j];
            }
           while (so[m]>=ub[j])
           {
                r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
                so[m]=r*(ub[j]-lb[j])+lb[j];
           }
            so[m]=solution[j][k].number;
            solution[j][k].pos=k;
        }
   }   
}

