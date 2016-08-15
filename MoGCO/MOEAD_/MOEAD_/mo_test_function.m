function obj=mo_test_function(x,fun)
 global M
% 多目标测试函数
% 包括  ZDT1 ZDT2 ZDT3 ZDT4 ZDT6 
% DTLZ1  DTLZ2  DTLZ3 DTLZ4 DTLZ5 DTLZ6 
% SCH FON  POL KUR
 D=length(x);
 
if strcmp(fun,'ZDT1')
    %ZDT1
    y=x(2:end);
    gx=1+9*sum(y)/(D-1);
    obj(1)=x(1);
    obj(2)=gx*(1-sqrt(x(1)/gx));
end


if strcmp(fun,'ZDT2')
    %ZDT2
    y=x(2:end);
    gx=1+9*sum(y)/(D-1);
    obj(1)=x(1);
    obj(2)=gx*(1-(x(1)/gx)^2);
  
end


if strcmp(fun,'ZDT3')
    %ZDT3
    y=x(2:end);
    gx=1+9*sum(y)/(D-1);
    obj(1)=x(1);
    obj(2)=gx*(1-sqrt(x(1)/gx)-x(1)/gx*sin(10*pi*x(1)));
  
end


if strcmp(fun,'ZDT4')
    %ZDT4
    y=x(2:end);
    gx=1+10*(D-1)+sum(y.*y-10*cos(4*pi*y));
    obj(1) = x(1);
    obj(2) = gx*(1-sqrt(x(1)/gx));
end

if strcmp(fun,'ZDT6')
    %ZDT6
    y=x(2:end);
    gx=1+9*(sum(y)/(D-1))^0.25;
    obj(1)=1-exp(-4*x(1))*(sin(6*pi*x(1)))^6;
    obj(2)=gx*(1-(obj(1)/gx)^2);
 
end


if strcmp(fun,'SCH')
    % SCH
    obj(1) = x(1)^2;
    obj(2) = (x(1)-2)^2;
end
 

if  strcmp(fun,'FON')
    % FON
    D=3;
    y1=(x-1/sqrt(3)).^2;
    g1=sum(y1);
    y2=(x+1/sqrt(3)).^2;
    g2=sum(y2);
    obj(1) = 1-exp(-g1);
    obj(2) = 1-exp(-g2);  
end


if  strcmp(fun,'POL')
    % POL
   A1=0.5*sin(1)-2*cos(1)+sin(2)-1.5*cos(2);
   A2=1.5*sin(1)-cos(1)+2*sin(2)-0.5*cos(2);
   B1=0.5*sin(x(1))-2*cos(x(1))+sin(x(2))-1.5*cos(x(2));
   B2=1.5*sin(x(1))-cos(x(1))+2*sin(x(2))-0.5*cos(x(2));
   obj(1) = 1+(A1-B1)^2+(A2-B2)^2;
   obj(2) = (x(1)+3)^2+(x(2)+1)^2; 
end


if  strcmp(fun,'KUR') 
    % KUR
    x1=x(1:end-1);
    x2=x(2:end);
    y1=-10*exp(-0.2*sqrt(x1.^2+x2.^2));
    obj(1) =sum(y1);
    y2=abs(x).^0.8+5*sin(x.^3);
    obj(2) =sum(y2);   
end


 %DTLZ1
if  strcmp(fun,'DTLZ1') 
    
     switch M
         case 2
         xg=x(:,2:end);
         gx=100*(6+sum((xg-0.5).^2-cos(20*pi*(xg-0.5))));
         obj(1)=0.5*x(1)*(1+gx);
         obj(2)=0.5*(1-x(1))*(1+gx);     
         case 3
         xg=x(:,3:end);
         gx=100*(5+sum((xg-0.5).^2-cos(20*pi*(xg-0.5))));
         obj(1)=0.5*x(1)*x(2)*(1+gx);
         obj(2)=0.5*x(1)*(1-x(2))*(1+gx);
         obj(3)=0.5*(1-x(1))*(1+gx);
     end
end


  %DTLZ2
if  strcmp(fun,'DTLZ2') 
     switch M
         case 2
             xg=x(:,2:end);
             gx=sum((xg-0.5).^2);
             obj(1)=(1+gx)*cos(x(1)*0.5*pi);
             obj(2)=(1+gx)*sin(x(1)*0.5*pi);  
         case 3
             xg=x(:,3:end);
             gx=sum((xg-0.5).^2);
             obj(1)=(1+gx)*cos(x(1)*0.5*pi)*cos(x(2)*0.5*pi);
             obj(2)=(1+gx)*cos(x(1)*0.5*pi)*sin(x(2)*0.5*pi);
             obj(3)=(1+gx)*sin(x(1)*0.5*pi);
     end
end


 %DTLZ
if  strcmp(fun,'DTLZ3') 
    switch M
         case 2
             xg=x(:,2:end);
             gx=100*(11+sum((xg-0.5).^2-cos(20*pi*(xg-0.5))));
             obj(1)=(1+gx)*cos(x(1)*0.5*pi);
             obj(2)=(1+gx)*sin(x(1)*0.5*pi);
         case 3
             xg=x(:,3:end);
             gx=100*(10+sum((xg-0.5).^2-cos(20*pi*(xg-0.5))));
             obj(1)=(1+gx)*cos(x(1)*0.5*pi)*cos(x(2)*0.5*pi);
             obj(2)=(1+gx)*cos(x(1)*0.5*pi)*sin(x(2)*0.5*pi);
             obj(3)=(1+gx)*sin(x(1)*0.5*pi);
    end
end


%DTLZ4
if  strcmp(fun,'DTLZ4') 
      switch M
         case 2
             xg=x(:,2:end);
             gx=sum((xg-0.5).^2);
             obj(1)=(1+gx)*cos((x(1)^100)*0.5*pi);
             obj(2)=(1+gx)*sin((x(1)^100)*0.5*pi);
         case 3
             xg=x(:,3:end);
             gx=sum((xg-0.5).^2);
             obj(1)=(1+gx)*cos((x(1)^100)*0.5*pi)*cos((x(2)^100)*0.5*pi);
             obj(2)=(1+gx)*cos((x(1)^100)*0.5*pi)*sin((x(2)^100)*0.5*pi);
             obj(3)=(1+gx)*sin((x(1)^100)*0.5*pi);
      end
end
 
if  strcmp(fun,'DTLZ5') 
     %DTLZ5
     xg=x(:,3:end);
     gx=sum((xg-0.5).^2);
     Q1=(pi/(4*(1+gx)))*(1+2*gx*x(1));
     Q2=(pi/(4*(1+gx)))*(1+2*gx*x(2));    
     obj(1)=(1+gx)*cos(Q1*0.5*pi).*cos(Q2*0.5*pi); 
     obj(2)=(1+gx)*cos(Q1*0.5*pi).*sin(Q2*0.5*pi);
     obj(3)=(1+gx)*sin(Q1*0.5*pi); 
end

if  strcmp(fun,'DTLZ6') 
     %DTLZ6
     xg=x(:,3:end);
     gx=1+(9/20)*sum(xg);  
     obj(1)=x(1);
     obj(2)=x(2);
     hf=3-(f1/(1+gx))*(1+sin(3*pi*f1))-(f2/(1+gx))*(1+sin(3*pi*f2));
     obj(3)=(1+gx)*hf; 
end


   
 

end
    
 


