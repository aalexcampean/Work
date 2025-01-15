% Exercise 2 / Laboratory 8

f = @(x) exp(1).^(-x.^2);
a = 0;
b= 1;
err = 0.0001;
n = 1;

% Using Composite Rectangle Method
method1 = @CompositeRectangle;

% Using Trapezoidal
method2 = @Trapezoidal;

% Using Simpson's Rule
method3 = @SimpsonsRule;

AdaptiveQuadratures(f,a,b,err,method1,n)