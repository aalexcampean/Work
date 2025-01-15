% Ex3.

x = linspace(0, 6, 13);
interpPoints = exp(sin(x));
t = 0 : 0.01 : 6;
f = exp(sin(t));
sol = [];

for i = 1 : length(t)
	sol = [sol newtInterp(x, interpPoints, t(i))];
end

hold on
plot(x, interpPoints); % the interpolation points
plot(t, f); % the function f
plot(t, sol); % the Newton interpolation polynomial
hold off