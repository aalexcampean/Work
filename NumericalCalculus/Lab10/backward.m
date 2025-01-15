function ret = backward(A, b)
  n = length(A);
  ret = zeros(n, 1);
  ret(n) = b(n) / A(n, n);
  for i = (n - 1):-1:1
    sum = 0;
    for j = (i + 1):n
      sum += A(i, j) * ret(j);
    endfor
    ret(i) = (1 / A(i, i)) * (b(i) - sum);
  endfor
end