#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
#include <fstream>
using namespace std;
double per[25];
int  p[25];
int main()
{
    //string s1=' ';
    int num=0;
    string line;
    ifstream   in("nonECM-Metazoa.seq70");
    ofstream   outfile("out1");
    while(getline(in, line)!=NULL)
    {
           num++;         
           if(num%2==0)
           {  
              printf("num=%d :",num);
              printf("length=%d\n",line.length());
              for(int i=0;i<20;i++)
              {
                 per[i]=0;
                 p[i]=0;
              }
              for(int i=0;i<30;i++)
             {
                      if(line[i]=='F'||'W'||'Y') 
                         p[0]++;
                      if(line[i]=='D'||'E')
                         p[1]++;
                      if(line[i]=='H')
                         p[2]++;
                      if(line[i]=='K') 
                         p[3]++;
                      if(line[i]=='R') 
                         p[4]++;
                      if(line[i]=='C') 
                         p[5]++;
                      if(line[i]=='M') 
                         p[6]++;
                      if(line[i]=='Q'||'N') 
                         p[7]++;
                      if(line[i]=='S'||'T') 
                         p[8]++;
                      if(line[i]=='A'||'G'||'I'||'L'||'V'||'P') 
                         p[9]++;
             } 
              for(int i=30;i<line.length();i++)
              {
                    if(line[i]=='F'||'W'||'Y') 
                         p[10]++;
                      if(line[i]=='D'||'E')
                         p[11]++;
                      if(line[i]=='H')
                         p[12]++;
                      if(line[i]=='K') 
                         p[13]++;
                      if(line[i]=='R') 
                         p[14]++;
                      if(line[i]=='C') 
                         p[15]++;
                      if(line[i]=='M') 
                         p[16]++;
                      if(line[i]=='Q'||'N') 
                         p[17]++;
                      if(line[i]=='S'||'T') 
                         p[18]++;
                      if(line[i]=='A'||'G'||'I'||'L'||'V'||'P') 
                         p[19]++;   
              }
              for(int i=0;i<9;i++)
                per[i]=p[i]*100/(30*1.0);
              for(int i=9;i<20;i++)
                per[i]=p[i]*100/((line.length()-30)*1.0);
              for(int i=0;i<20;i++)
                printf("%d ",p[i]);
                printf("\n");
               for(int i=0;i<20;i++)
               outfile<<per[i]<<','; 
               outfile<<endl;  
           }
           
    }
    system("pause");
    return 0;
}
