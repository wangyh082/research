function scalarfit  = teFit(fit,i)

global  lamdaMat z

for j = 1:length(lamdaMat(i,:))
    if lamdaMat(i,j)==0
       lamdaMat(i,j)=0.00001; 
    end
end
scalarfit = max( lamdaMat(i,:).*abs(fit - z) );



