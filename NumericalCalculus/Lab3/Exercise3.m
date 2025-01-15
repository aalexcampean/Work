% Ex3.

x = linspace(0, 10, 21);
barry_function = (1 + cos(pi*x)) ./ (1 + x);

y = 0 : 0.01 : 10;
true_function = (1 + cos(pi*y)) ./ (1 + y);

sol = [];
for i = 1 : length(x)
	sol = [sol lagrangeBary(x, barry_function, x(i))];
end


hold on
ylim([0, 2]);
plot(x, sol, '-g');
plot(t, true_function);
title("Lagrange - green & True function - blue");
hold off