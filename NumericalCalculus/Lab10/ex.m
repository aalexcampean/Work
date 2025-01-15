backward([2, 4 2; 0 -1 1; 0 0 -1], [8 0 -1]);
forward([1 0 0; (1 / 2) 1 0; (1 / 2) 1 1], [8, 4, 3]);
gauss([1 -1 1; -2 2 1; -3 -1 5], [-1 2 -5]);

n = 5;

A = 5 * eye(n) - diag(ones(n - 1, 1), -1) - diag(ones(n - 1, 1), 1);
b = 3 * ones(n, 1) + triu(ones(n, 1)) + tril(ones(n, 1), 1 - n);

gauss(A, b)
LUP(A, b)
cholesky(A, b)
QR(A, b)

A = 5 * eye(n) - diag(ones(n - 1, 1), -1) - diag(ones(n - 1, 1), 1) - diag(ones(n - 3, 1), -3) - diag(ones(n - 3, 1), 3);
b = ones(n, 1) + triu(ones(n, 1)) + tril(ones(n, 1), 1 - n) + triu(ones(n, 1), -2) + tril(ones(n, 1), 3 - n);

gauss(A, b)
LUP(A, b)
cholesky(A, b)
QR(A, b)