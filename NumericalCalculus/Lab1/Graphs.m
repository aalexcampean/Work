% Graphs
%
%
%
% Ex1.
x = linspace(0,1)
f = exp(10.*x.*(x-1)).*sin(x.*12.*pi)
plot(x, f)

x = linspace(0,1)
f = 3.*exp(5.*x.^2 - 1).*cos(12.*pi.*x)
plot(x, f)


% Ex2.
t = linspace(0,10*pi)
a = 2
b = 5
x = (a+b).*cos(t) - b.*cos((a/b + 1).*t)
y = (a+b).*sin(t) - b.*sin((a/b + 1).*t)
plot(x,y)


% Ex3.
v = linspace(0, 2.*pi)
f1 = cos(v)
f2 = sin(v)
f3 = cos(2.*v)
plot(v, f1)
hold on
plot(v, f2)
hold on
plot(v, f3)
hold off


% Ex4.
r = linspace(-1, 0)
f1 = r.^3 + sqrt(1-r)
s = linspace(0, 1)
f2 = s.^3 - sqrt(1-s)
plot(r, f1)
hold on
plot(s, f2)


% Ex5.
x1 = 0 : 2 : 50
x2 = 1 : 2 : 49
f1 = x1/2
f2 = 3 * x2 + 1
plot(x1, f1, "*", x2, f2, "*")


% Ex6.
k = 5
g = 1 + 1/2
G = [g]
for c = 1:k
  g = 1 + 1/g
  G = [G g]
endfor
G


% Ex7.
x = -2 : 0.02 : 2
y = -4 : 0.01 : 4
[x, y] = meshgrid(x,y)
f = exp(-((x - 1/2).^2 .+ (y-1/2).^2))
mesh(x,y,f)