function T = Trapezoidal(f,a,b,n)
    h = (b-a)/n;
    s = 0;
    for i=1:n-1
        s = s+f(a+i*h);
    end
    T = (h/2)*(f(a)+2*s+f(b));
end