function  [X,fit ]= updateNeigh(X,fit,Bi,y,fity) 
 
% k=0;
for i=1:length(Bi)
    
    scalarfit1 = teFit(fit(Bi(i),:),Bi(i));
    scalarfit2 = teFit(fity,Bi(i));
    if  scalarfit2 <= scalarfit1
%         111111
        X(Bi(i),:) = y;
        fit(Bi(i),:) = fity;
%         k=k+1;
    end
end
 