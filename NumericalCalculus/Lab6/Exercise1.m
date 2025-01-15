% Exercise 1 / Laboratory 6

x = [0, pi / 2, pi, (3 * pi) / 2, 2 * pi];
fx = sin(x);

% Cubic natural spline
tNatural = spline(x, fx);
natural = ppval(tNatural, pi / 4);

% Cubic clamped spline
tClamped = spline(x, [1, fx, 1]);
clamped = ppval(tClamped, pi / 4);

interval = linspace(0,2*pi,50);

hold on

% The grapgh of the function
plot(interval, sin(interval));

% The grapgh of the cubic clamped spline
xx = ppval(tClamped, interval);
plot(interval, xx);

% The grapgh of the cubic natural spline
yy = ppval(tNatural, interval);
plot(interval, yy);

hold off