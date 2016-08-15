function fit=benchMark(x,Dimension)
     value=0;
     for j=1:Dimension
         value=value+x(j).^2;
     end
     fit=value;
end