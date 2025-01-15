% Ex1.

t = [0 3 5 8 13]; % time
d = [0 225 383 623 993]; % distance
v = [75 77 80 74 72]; % velocity
x = 10; % the point in which we want to approximate

D = HermiteInterpol(t, d, v, x)

eps = 0.001;
S = HermiteInterpol(t, d, v, x + eps);

(S-D)/eps

