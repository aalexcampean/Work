% Ex1.

x = [1, 1.5, 2, 3, 4];
y = [0, 0.17609, 0.30103, 0.47712, 0.60206];

newtInterp(x, y, 2.5)
newtInterp(x, y, 3.25)

t = 1 : 0.1 : 3.5;
f = log10(t);
interpolated = [];

for i = 1 : length(t)
	interpolated = [interpolated newtInterp(x, y, t(i))];
end

plot(t, f, t, interpolated)

% the max interpolation error
max(abs(f-interpolated))