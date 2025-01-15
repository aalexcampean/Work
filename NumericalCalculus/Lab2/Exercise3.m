% EX3.

n = 6;
x = -1 : 0.01 : 3;

% e^x derivated any number of times = e^x
% e^x0 = e^0 = 1
fxi = 1;

hold on
plot(x, fxi);
for i = 1:n-1
	f = fxi + x.^i / factorial(i); % computing the sum from 1 util (n-1)
	plot(x, f);
	fxi = f;
end 
hold off