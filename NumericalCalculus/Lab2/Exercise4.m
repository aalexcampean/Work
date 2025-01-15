% EX4.

h = 0.25;
n = 6;

f = sqrt(5 * x.^2 + 1); % the function

x = []; % initializing vector x
for i = 0 : n % constructing vector x
	x = [x 1 + i * h];
endfor

x % printing the values of x
f % printing the values of fx

t = [f]
prev_t = f;
for i = 1:n
	new_t = [];
  % parsing the values until the previous size - the position 
  % as the output keep shrinking
	for j = 1:n-i+1 
		new_t = [new_t prev_t(j + 1) - prev_t(j)];
	endfor
	new_t = [new_t zeros(1, i)];
	t = [t ; new_t];
	prev_t = new_t;
endfor
t' % we need to transpose it as we start from the end

