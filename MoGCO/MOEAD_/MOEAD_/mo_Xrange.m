% 多目标测试函数 上下界

 
% ZDT 1
if strcmp(fun,'ZDT1')
    M=2;  %目标个数
    D=30; %问题维度
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);
end

% ZDT 2
if strcmp(fun,'ZDT2')
    M=2;  %目标个数
    D=30; %问题维度
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);
end

% ZDT 3
if strcmp(fun,'ZDT3')
    M=2;  %目标个数
    D=30; %问题维度
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);
end

% ZDT 4
if strcmp(fun,'ZDT4')
    M=2;  %目标个数
    D=10; %问题维度
    Xmax=[1 5*ones(1,D-1)];
    Xmin=[0 -5*ones(1,D-1)];
end

% ZDT 6
if strcmp(fun,'ZDT6')
    M=2;  %目标个数
    D=10; %问题维度
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);
end

% SCH
if  strcmp(fun,'SCH')
    M=2;   %目标个数
    D=1;   %问题维度
    Xmax=2*ones(1,D);
    Xmin=0*ones(1,D);
end

% POL
if  strcmp(fun,'FON') 
    M=2;   %目标个数
    D=3;   %问题维度
    Xmax=4*ones(1,D);
    Xmin=-4*ones(1,D);
end

 % POL
if  strcmp(fun,'POL')  
    M=2;   %目标个数
    D=2;   %问题维度
    Xmax=pi*ones(1,D);
    Xmin=-pi*ones(1,D);
end

% KUR
if  strcmp(fun,'KUR')  
    M=2;   %目标个数
    D=3;   %问题维度
    Xmax=5*ones(1,D);
    Xmin=-5*ones(1,D);
end

 %DTLZ1
if  strcmp(fun,'DTLZ1')    
    M=input('目标个数：M=');   
    D=7;   %问题维度
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);   
end 


 %DTLZ2
if  strcmp(fun,'DTLZ2') 
    M=input('目标个数：M=');  
    D=12;   %问题维度
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D); 
end 

 %DTLZ3
if  strcmp(fun,'DTLZ3') 
    M=input('目标个数：M=');  
    D=12;   %问题维度
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);   
end 

 %DTLZ4
if  strcmp(fun,'DTLZ4') 
    M=input('目标个数：M='); 
    D=12;   %问题维度
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);     
end 
  
  %DTLZ5
if  strcmp(fun,'DTLZ5') 
    M=3;   %目标个数
    D=12;   %问题维度
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);    
end

  %DTLZ6
if  strcmp(fun,'DTLZ6') 
    M=3;   %目标个数
    D=22;   %问题维度
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);  
end
 