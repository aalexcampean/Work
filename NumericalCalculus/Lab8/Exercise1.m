% Exercise 1 / Laboratory 8

% Initialization
f = @(x) 1/x;
a = 1;
b = 2;

% Using Composite Rectangle
n = 1;
while true
    if(abs(log(2)-CompositeRectangle(f,a,b,n))<0.0001)
        break;
    end
    n = n+1;
end
compositeRectangleResult = CompositeRectangle(f,a,b,n)

% Using Trapezoidal
n=1;
while true
    if(abs(log(2)-Trapezoidal(f,a,b,n))<0.0001)
        break;
    end
    n = n+1;
end
trapezoidalResult = Trapezoidal(f,a,b,n)

% Using Simpson's Rule
n=1;
while true
    if(abs(log(2)-SimpsonsRule(f,a,b,n))<0.0001)
        break;
    end
    n = n+1;
end
simpsonsRuleResult = SimpsonsRule(f,a,b,n)2

