function y=beta(a,b,min,max)
     u1=randNo(0.0,1.0);
     u2=randNo(0.0,1.0);
     v1=power(u1,1.0/a);
     v2=power(u2,1.0/b);
     w=v1+v2;
     while(w>1)
          u1=randNo(0.0,1.0);
          u2=randNo(0.0,1.0);
          v1=power(u1,1.0/a);
          v2=power(u2,1.0/b);
          w=v1+v2;
     end
     x=v1/w;
     y=(max-min)*x+min;
end
