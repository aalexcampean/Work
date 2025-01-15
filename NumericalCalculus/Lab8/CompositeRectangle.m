function C = CompositeRectangle(f,a,b,n)
    h = (b-a)/n;
    s = 0;
    for i = 0:n-1
    s = s + f(a+(i+1/2)*h);
    end
    C = h*s;
end