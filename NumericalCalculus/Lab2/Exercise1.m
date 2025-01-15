% EX1.

% 1st Polynomial
subplot(2, 2, 1); % rows, column, index
x = 0 : 0.01 : 1; % usually the step is chosen to be 0.1
f = x;
plot(x, f);
title('Subplot 1st polynomial: l2(x) = x');

% 2nd Polynomial
subplot(2, 2, 2); 
x = 0 : 0.01 : 1;
f = 3 * x.^2 / 2 - 1/2;
plot(x, f);
title('Subplot 2nd polynomial: l2(x) = 3 * x^2 / 2 - 1/2');

% 3rd Polynomial
subplot(2, 2, 3);
x = 0 : 0.01 : 1;
f = 5/2 * x.^3 - 3/2 * x;
plot(x, f);
title('Subplot 3rd polynomial: l3(x) = 5/2 * x^3 - 3/2 * x');

% 4th Polynomial
subplot(2, 2, 4);
x = 0 : 0.01 : 1;
f = 35/8 * x.^4 - 15/4 * x.^2 + 3/8;
plot(x, f);
title('Subplot 3rd polynomial: l4= 35/8 * x^4 - 15/4 * x^2 + 3/8');