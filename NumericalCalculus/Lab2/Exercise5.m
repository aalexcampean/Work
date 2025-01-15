% EX5.

n = 4;
x = [2 4 6 8];
f = [4 8 14 16];
t = [x ; f];

for i = 2:n % we start from 2 cuz the first 2 columns are the values of x and fx
	new_t = [];
	for j = 1:n-i+1
		new_t = [new_t (t(i, j+1) - t(i, j)) / (t(1, j+i-1) - t(1, j))];
	endfor
	new_t = [new_t zeros(1, i-1)];
	t = [t ; new_t];
	prev_t = new_t;
endfor
t'