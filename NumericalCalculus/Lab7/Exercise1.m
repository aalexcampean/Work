% Exercise 1 / Laboratory 7

x = [1,2,3,4,5,6,7];
fx = [13,15,20,14,15,13,10];
p = polyfit(x,fx,1);
polyval(p,8)

hold on

plot(x,fx,"*")
plot(x,polyval(p,x))

hold off