function     y = geneticOp( x1, x2)
global Xmax Xmin
%   用遗传算子产生一个新个体位置

% SBX 模拟二进制交叉
miu = 2 ;
D=length(x1);

for i=1:D
    r=rand;
    if r<=0.5
        beta=(2*r)^(1/(1+miu));
    else
        beta=1/((2*(1-r))^(1/(1+miu)));
    end
    
    y(i)=0.5*((1-beta)*x1(i)+(1+beta)*x2(i));
end
    
% PolyM: 多项式变异
if rand<1/D
    mu=5;
    r=randperm(D);
    ind=r(1);        %选中变异的位置

    r=rand; 
    if r<0.5
        delta=(2*r)^(1/(1+mu))-1;
    else
        delta=1-(2*(1-r))^(1/(mu+1));
    end
    y(ind)=y(ind)+delta*(Xmax(ind)-Xmin(ind));
end

