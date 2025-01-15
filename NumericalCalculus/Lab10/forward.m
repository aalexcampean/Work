function ret = forward(A, b)
  n = length(A);
  ret = zeros(n, 1);
  ret(1) = b(1) / A(1, 1);
  for i = 2:n
    sum = 0;
    for j = 1:(i - 1)
      sum += A(i, j) * ret(j);
    endfor
    ret(i) = (1 / A(i, i)) * (b(i) - sum);
  endfor
end