

function [H] = HermiteInterpol(t,d,v,x)
% t = t
% d = f(t)
% v = f'(t)
% x = the points in which we want to approximate

l = length(t);
 
z = reshape([t;t], 1, []);
f = reshape([d;d], 1, []);

m = zeros(2*l, 2*l); % Matrix of divided diff
m(:, 1) = f';
m(1:2:end, 2) = v';
m(2:2:2*l-1, 2) = (d(2:l) - d(1:l-1)) ./ (t(2:l) - t(1:l-1));

for k = 3:2*l
    for i = 1:2*l-k+1
        m(i,k) = (m(i+1,k-1) - m(i,k-1)) / (z(i+k-1) - z(i));
    end
end

lx = length(x); % Hermite interpolation
p = ones(lx,1);
s = m(1, 1) * ones(lx, 1);   % --> f(z0) = m(1,1)

for j = 1:lx
  for i = 1:2*l-1
    p(j) = p(j) * (x(j) - z(i));
    s(j) = s(j) + p(j) * m(1,i+1);
  end
end

H=s' ;