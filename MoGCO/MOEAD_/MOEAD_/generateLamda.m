function lamdaM = generateLamda(N,M) 
% 产生N 个权重向量 weight vector
% lamdaM 为 N*M矩阵

if M == 2   %  2目标
    array = (0:N)/N;
    for i= 1:N+1
    	lamdaM(i,1)=array(i);
        lamdaM(i,2)=1-array(i);
    end
    len = size(lamdaM,1);
    index = randperm(len);
    index = sort(index(1:N));
    lamdaM = lamdaM(index,:);
    
elseif M==3  %  3目标
    k = 1;
    array = (0:25)/25;
    for i = 1:26
        for j = 1:26
            if i+j<28
                lamdaM(k,1) = array(i);
                lamdaM(k,2) = array(j);
                lamdaM(k,3) = array(28-i-j);
                k =k+1;
            end
        end
    end
    len = size(lamdaM,1);
    index = randperm(len);
    index = sort(index(1:N));
    lamdaM = lamdaM(index,:);
    
end
