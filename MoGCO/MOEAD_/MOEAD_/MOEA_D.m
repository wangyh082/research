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
fun='ZDT3';       % ѡ����Ժ��� DTLZ1
mo_Xrange;    
N = 100;          % ��Ⱥ��С��Ҳ�������� subproblem �ĸ���
lamdaMat = generateLamda(N,M); % ����Ȩ������
T = 20;           % �ھӹ�ģ��С
Maxgen =  250;

%------------------------------- ��ʼ�� initialization 
% ��ʼ���ھ�
B = getNeighbor(lamdaMat,T);
% ��ʼ������λ��
X = repmat(Xmin,N,1)+rand(N,D).*repmat(Xmax-Xmin,N,1); 
for i=1:N
    fit(i,:) = mo_test_function(X(i,:),fun);
end
% ��ʼ��zֵ
for i=1:M
    z(i) = min(fit(:,i));
end


%-------------------------------- ���� update
% ����ѭ��
for gen =1:Maxgen
    
for i = 1:N  % ��ÿһ������
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
 


