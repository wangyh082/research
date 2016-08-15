function B = getNeighbor(lamdaMat,T);
%  ·µ»ØÁÚ¾ÓBË÷Òı

N =size(lamdaMat,1);
distanceMat = zeros(N,N);

for i = 1:N
    for j = 1:N
        l = lamdaMat(i,:)-lamdaMat(j,:);
        distanceMat(i,j)=sqrt(l*l');
    end
end

% ·µ»ØÁÚ¾ÓË÷Òı
for i = 1:N
    [s,sindex] = sort(distanceMat(i,:));
     B(i,:) = sindex(1:T);
end
