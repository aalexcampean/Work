% Ex.3

t = linspace(-5,5,15);
f = @(x)sin(2*x);

d = f(t);

deriv = @(x)2*cos(2*x);

v = deriv(t);

x = linspace(-5,5,50);

[H] = HermiteInterpol(t,d,v,x);

hold on 
plot(x, f(x),'*')
plot(x, H)