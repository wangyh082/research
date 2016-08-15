%___________________________________________________________________%
%   source codes version 1.0               %
%                                                                   %
%  Developed in MATLAB R2011b(7.13)                                 %
%                                                                   %
%  programmer: Xiangtao Li and Yuhe Wang                            %
%                                                                   %
%         e-Mail: lixt314@nenu.edu.cn                               %
%                                                                   %
%                                                                   %
%                                                                   %

%___________________________________________________________________%



clear all
clc

Runs=2;
Dimension=30;
Population=40;
iterations_Max=5000;
E=exp(1.0);
pi=acos(-1.0);
Range=100; % x belongs to [-Range,Range]
red=0.25;
tr=30.0;
cp=0.5;
     xdash=[]; x=[];best_func_Value=[];z=[];y=[];
     sum=0.0;sum_squared=0.0;sum_Eval=0.0;
     %%%%%%%%%%NO. of Runs%%%%%%%%%%%%%%%%%%%%%%%%
     for run=1:1:Runs
         %pause(1);
         fprintf('\nRun=%d\n',run);


         slope = -1.0/(iterations_Max-1);

         %%%%%%%%%%%%initialization%%%%%%%%%%%%
         for i=1:Population 
              for j=1:Dimension
                  x(i,j)=beta(0.1,0.1,-Range,Range);
              end
         end
         %%%%%%%%%%%%%function evaluation%%%%%%%%%%%%%%%

         for i=1:Population
              best_func_Value(i)= benchMark(x(i,:),Dimension); 
         end
          min=best_func_Value(1);  bestone=1;
         for r=1:Population
                if(best_func_Value(r)<min ) 
                            min=best_func_Value(r);
                            bestone=r;
                end
         end
         %%%%%%%%%%%%%%%%Search Process%%%%%%%%%%%%%%%
           mu = (Population + 1 - (1:Population)) / (Population + 1); % emigration rate
            lambda = 1 - mu; % immigration rate
         for itr=1:iterations_Max
           
             
              for i=1:Population
                  for j=1:Dimension
                      cdc=randNo(0,1);%%%%%%%%%%Counsling Decisive Coefficient%%%%%%%%%%%%%%%

                      if (cdc<=cp)
                          
                          %%%
                          counselor1=randNo1(i,Population);
                          counselor2=randNo1(i,Population);
                          while(counselor2==counselor1)
                               counselor2=randNo1(i,Population);
                          end
                          counselor3=randNo1(i,Population);
                          while(counselor3==counselor1 || counselor3==counselor2)
                              counselor3=randNo1(i,Population);
                          end
                          counselor4=randNo1(i,Population);
                          while(counselor4==counselor1 || counselor4==counselor2 || counselor4==counselor3)
                               counselor4=randNo1(i,Population);
                          end
                          counselor5=randNo1(i,Population);
                          while(counselor5==counselor1 || counselor5==counselor2 || counselor5==counselor3 || counselor5==counselor4)
                              counselor5=randNo1(i,Population);
                          end
                                  w1=randNo(0.0,1.0); 
                            w2=randNo(0.0,1.0-w1);
                           % w3=randNo(0.0,1.0-w1-w2);  
                            %w4=randNo(0.0,1-w1-w2-w3);
                            w3=1-w1-w2; %-w3-w4;
                            
                            
                           %  xdash(i,j)= x(counselor1,j) + 0.5.*(x(counselor2,j)-x(counselor3,j));
                           xdash(i,j)= w1*x(counselor1,j) + w2*x(counselor2,j)+ w3*x(counselor3,j); % + w4*x(counselor4,j) + w5*x(counselor5,j) ;
                      else
                            range_length=2*Range;
                            mdf_max_itr=0.5*red*range_length*power(slope*itr + 1.0, tr ); 
                            xdash(i,j)= x(i,j) + randNo(-mdf_max_itr, mdf_max_itr);
                            while(xdash(i,j) > Range || xdash(i,j) < -Range)
                                 xdash(i,j)= x(i,j) + randNo(-mdf_max_itr, mdf_max_itr);
                            end      
                      end
                  end
                  %%%%%%%%%%%%%%%%%%%%%%Function Evalution%%%%%%%%%%%%%%%%%%%%%%%%%
                  z=xdash(i,:);
                  func_temp= benchMark(z,Dimension) ;
                     if(func_temp < best_func_Value(i))       
                                x(i,:)=xdash(i,:); 
                            best_func_Value(i)=func_temp;
                     end
              end
        
         %%%%%%%%%%%%%%%%%%%%%%%Determining the best solution%%%%%%%%%%%%%%%%%%%%%%
         %min=best_func_Value(1);  bestone=1;
         for r=1:Population
                if(best_func_Value(r)<min ) 
                            min=best_func_Value(r);
                            bestone=r;
                end
         end
          min
         end
         %%%%%%%%%%%%%%%%%For Statistics%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % sum=sum+min;
        % sum_squared=sum_squared+power(min,2.0);
        min
         %fprintf('Min =%.16f\n\n',min);
     end
    % fprintf('\nThe Optimum At : \n');
    % for r=1:Dimension
     %     fprintf('x[%d][%d]=%.16f\n',bestone,r,x(bestone,r));
    % end
    % fprintf('* No. of Function Evaluations =%d\n\n',bestone);
     
    % fprintf('* Mean = %.16f\n\n',sum/Runs);
     
    % fprintf('* Standard Deviation = %e\n\n',sqrt( ( sum_squared - power(sum/Runs,2.0)*Runs )/(Runs-1) ) );

 
         
                  
         