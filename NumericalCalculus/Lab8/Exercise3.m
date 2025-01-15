% Exercise 3 / Laboratory 8

% Defining the function f(x) and the limits
f = @(x) 1 ./ (2 + cos(x));
a = 0;
b = 2 * pi;
expectedResult = 2 .* pi ./ sqrt(3)

n = 1;
while true
    x = Romberg(f,a,b,n);
    if(abs(expectedResult - x(n, 1))<0.0001)
        break;
    end;
    n=n+1;
end

v=Romberg(f,a,b,n);
v(n,1)
