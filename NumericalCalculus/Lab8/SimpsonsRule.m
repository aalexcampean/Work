function S = SimpsonsRule(f,a,b,n)
    h = (b-a)/(2*n);
    sum1 = 0;
    sum2 = 0;
    for i =1:n
        sum1 = sum1 + f(a+(2*i-1)*h);
    end
    for i =1:n-1
        sum2 = sum2+ f(a+2*i*h);
    end
    S = (h/3)*(f(a)+4*sum1+2*sum2+f(b));
end