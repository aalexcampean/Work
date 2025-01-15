% EX2.

% a).
t = -1 : 0.01 : 1;

T1 = cos(acos(t));
T2 = cos(2*acos(t));
T3 = cos(3*acos(t));

hold on
plot(t, T1);
plot(t, T2);
plot(t, T3);
hold off

% b).
n = 8
t = 0 : 0.01 : 1;

T0 = 1;
T1 = x;

hold on
plot(x, T0);
plot(x, T1);
for i = 2:n  % i fron 2 until n
	T2 = 2 * x .* T1 .- T0;
	plot(x, T2);
	T0 = T1;
	T1 = T2;
end
hold off