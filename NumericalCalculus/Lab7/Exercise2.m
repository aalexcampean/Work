% Exercise 2 / Laboratory 7
 
clf
x = [0,10,20,30,40,60,80,100];
fx = [0.0061,0.0123,0.0234,0.0424,0.0738,0.1992,0.4736,1.0133];
p = polyfit(x,fx,1);
polyval(p,45)

p2 = polyfit(x,fx,2);
p3 = polyfit(x,fx,3);
polyval(p2,45)
polyval(p3,45)
t = 0:0.1:100

hold on

plot(t,polyval(p,t))
plot(t,polyval(p2,t))
plot(t,polyval(p3,t))
plot(x,fx,"*")

hold off

