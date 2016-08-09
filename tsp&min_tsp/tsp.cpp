#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
FILE * file;
//for tsp the max n=20000
//for atsp the max n=500

#define N 200000

#include "support.h"
#include "heap sort.h"
#include "input_output_support.h"
#include "components.h"
#include "grasp_pr.h"




int main()
{
    //output file
    file=fopen("out.txt","w");

	srand((unsigned) time(NULL));

	// number of  size of the instance
	int n;
	// parameter alpha of GRASP
	double a;
	// maximum number of iterations of GRASP
	int mi = 128;

	// open input file
	FILE *f;
	f = freopen("ftv33.atsp","r",stdin);
    char str[100]=" "; 
    char str1[100]=" ";
	// read the instance size
	while(str[0]!='D')
	
	fgets(str, 100 ,f);
	//fprintf(file,"%s\n",str);

    int l=strlen(str);
    int i;
    for(i=l-1;i>=0;i--)
    {
       if(str[i]==' ')
         break;
    }
    int j;
    int k=0;
    for(j=i+1;j<l;j++)
    {
        str1[k++]=str[j];
    }
    str1[k]='\0';
    //fprintf(file,"%d\n",k);
    //fprintf(file,"%s\n",str1);
    
    n=atoi(str1);
    //n is the size of the instance
    fprintf(file,"%d",n);
	int **og = (int **) malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		og[i] = (int *) malloc(n * sizeof(int));
		
	// read the data from the input file
	int num=0;
	int flag=0;
    //计算og数组中的数的个数 
	int num1=0;
    while(fgets(str, 100 ,f)!=NULL)
    {     
      // if(strcmp(str,"EOF")==0)
        // flag=1; 
       //if(flag==0)
       //{             
           num++;              
           if(num>=4)
           {
              //fprintf(file,"%s",str);
              int len=strlen(str);
              num1=get(num1,str,len,n,og);            
           }
          //  fprintf(file,"%d\n",num1);  
           
    }
    //og is the data we need
    for(int i=0;i<n;i++)
    {
       for(int j=0;j<n;j++)
         fprintf(file," %d ",og[i][j]); 
       fprintf(file,"\n");
    }
   	fclose(f);
 
 	// string order we need returned from GRASP_PR
	int *order = (int *) malloc(n * sizeof(int));
	// GRASP_PR iterations for its best solution
	int git;
	//the distance result of the MAXTSP
	int gto;
	// string order returned from GRASP_PR
 	int *gso = (int *) malloc(n * sizeof(int));

	// compute the appropriate value for the parameter alpha according to the
	// instance size
	a = n2a(n);
	// compute a GRASP solution
    grasp_rp(og,n,a,mi,&gto,gso,&git);
	// print the GRASP solution
	output(n, a, mi, git,order);

	// free memory
	for (i = 0; i < n; i++)
		free(og[i]);
	free(og);

    system("pause");
	return 0;
} //main
