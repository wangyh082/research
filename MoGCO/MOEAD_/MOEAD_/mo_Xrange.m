% ��Ŀ����Ժ��� ���½�

 
% ZDT 1
if strcmp(fun,'ZDT1')
    M=2;  %Ŀ�����
    D=30; %����ά��
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);
end

% ZDT 2
if strcmp(fun,'ZDT2')
    M=2;  %Ŀ�����
    D=30; %����ά��
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);
end

% ZDT 3
if strcmp(fun,'ZDT3')
    M=2;  %Ŀ�����
    D=30; %����ά��
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);
end

% ZDT 4
if strcmp(fun,'ZDT4')
    M=2;  %Ŀ�����
    D=10; %����ά��
    Xmax=[1 5*ones(1,D-1)];
    Xmin=[0 -5*ones(1,D-1)];
end

% ZDT 6
if strcmp(fun,'ZDT6')
    M=2;  %Ŀ�����
    D=10; %����ά��
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);
end

% SCH
if  strcmp(fun,'SCH')
    M=2;   %Ŀ�����
    D=1;   %����ά��
    Xmax=2*ones(1,D);
    Xmin=0*ones(1,D);
end

% POL
if  strcmp(fun,'FON') 
    M=2;   %Ŀ�����
    D=3;   %����ά��
    Xmax=4*ones(1,D);
    Xmin=-4*ones(1,D);
end

 % POL
if  strcmp(fun,'POL')  
    M=2;   %Ŀ�����
    D=2;   %����ά��
    Xmax=pi*ones(1,D);
    Xmin=-pi*ones(1,D);
end

% KUR
if  strcmp(fun,'KUR')  
    M=2;   %Ŀ�����
    D=3;   %����ά��
    Xmax=5*ones(1,D);
    Xmin=-5*ones(1,D);
end

 %DTLZ1
if  strcmp(fun,'DTLZ1')    
    M=input('Ŀ�������M=');   
    D=7;   %����ά��
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);   
end 


 %DTLZ2
if  strcmp(fun,'DTLZ2') 
    M=input('Ŀ�������M=');  
    D=12;   %����ά��
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D); 
end 

 %DTLZ3
if  strcmp(fun,'DTLZ3') 
    M=input('Ŀ�������M=');  
    D=12;   %����ά��
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);   
end 

 %DTLZ4
if  strcmp(fun,'DTLZ4') 
    M=input('Ŀ�������M='); 
    D=12;   %����ά��
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);     
end 
  
  %DTLZ5
if  strcmp(fun,'DTLZ5') 
    M=3;   %Ŀ�����
    D=12;   %����ά��
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);    
end

  %DTLZ6
if  strcmp(fun,'DTLZ6') 
    M=3;   %Ŀ�����
    D=22;   %����ά��
    Xmax=1*ones(1,D);
    Xmin=0*ones(1,D);  
end
 