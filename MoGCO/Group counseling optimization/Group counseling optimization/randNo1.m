function  y=randNo1(i,Population) 
   % r=randi(Population,1,1);
    r=1+fix(Population*rand(1,1));
    while(r==i)
     %   r=randi(Population,1,1);
      r=1+fix(Population*rand(1,1));
    end
    y=r;
end