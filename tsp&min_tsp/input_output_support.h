int get(int num,char *str,int len,int n,int **og)
{    
     char str1[100];
     int a[100];
     memset(a,0,sizeof(a));
     int aa;
     int k=1;
     for(int i=1;i<len;i++)
     {
        if(str[i]>='0'&&str[i]<='9'&&str[i-1]==' ')
        {
            a[k++]=i;
        }
     }
    //  fprintf(file,"*%d \n",k);
    // for(int i=1;i<k;i++)
     // fprintf(file,"%d \n",a[i]); 
      a[k]=len-1;    
      for(int j=2;j<=k;j++) 
      {
         int kk=0;
         for(int jj=a[j-1];jj<=a[j];jj++)
          str1[kk++]=str[jj];
          str1[kk]='\0';
          aa=atoi(str1);
         // fprintf(file,"*%d*\n",aa);
          og[num/n][num%n]=aa;
          num++;
      }
      return num;
}


void output(int n,double a,int mi,int git,int *order)
{
    int i;
    fprintf(file, "\nGRASP_PR for the MAXTSP\n");
	fprintf(file, "-----------------\n");
	fprintf(file, "instance size (number of nodes)      : %d\n", n);
	fprintf(file, "value of the parameter alpha           : %lf\n", a);
	fprintf(file, "maximun number of iterations           : %d\n\n", mi);
	fprintf(file, "iterations for the best GRASP solution : %d\n", git);
	fprintf(file, "string order                           : ");
	for (i = 0; i < n; i++)
		fprintf(file, "%d ", order[i]);
	fprintf(file, "\n\n");
}
