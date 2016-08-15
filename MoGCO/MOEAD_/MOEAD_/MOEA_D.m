%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Written by Chen Xu, 2013.06.28
% Ph.D. Students in East China University of Science and Technology
% email: chenxu796@qq.com 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% MOEA/D: A Multiobjective Evolutionary Algorithm Based on Decomposition
% Qingfu Zhang, Senior Member, IEEE, and Hui Li
% IEEE TRANSACTIONS ON EVOLUTIONARY COMPUTATION, VOL. 11, NO. 6, DECEMBER 2007


clear all;
clc

format long
 
global Xmax Xmin M  lamdaMat  z

rand('state',sum(100*clock));

%------------------------------- input 
fun='ZDT3';       % 选择测试函数 DTLZ1
mo_Xrange;    
N = 100;          % 种群大小，也是子问题 subproblem 的个数
lamdaMat = generateLamda(N,M); % 产生权重向量
T = 20;           % 邻居规模大小
Maxgen =  250;

%------------------------------- 初始化 initialization 
% 初始化邻居
B = getNeighbor(lamdaMat,T);
% 初始化个体位置
X = repmat(Xmin,N,1)+rand(N,D).*repmat(Xmax-Xmin,N,1); 
for i=1:N
    fit(i,:) = mo_test_function(X(i,:),fun);
end
% 初始化z值
for i=1:M
    z(i) = min(fit(:,i));
end


%-------------------------------- 更新 update
% 迭代循环
for gen =1:Maxgen
    
for i = 1:N  % 对每一个个体
    % Reproduction
    index = randperm(T);
    r1 = B(i,index(1));
    r2 = B(i,index(2));
    y = geneticOp( X(r1,:), X(r2,:));
    
    % Improvement
    y = CheckBound(y,Xmax,Xmin);
    fity = mo_test_function(y,fun);
     for j=1:M
        z(j) = min(z(j),fity(j));
     end
    
    % Update of neighboring solution   
    [X,fit] = updateNeigh(X,fit,B(i,:),y,fity);
    
end

if M==2
    scatter(fit(:,1),fit(:,2));
elseif M==3
    scatter3( fit(:,1), fit(:,2),fit(:,3) );
    set(gca,'xdir','reverse'); set(gca,'ydir','reverse');
%     plot3(fit(:,1),fit(:,2),fit(:,3),'o');
end

title(num2str(gen));
drawnow
end
 


