function ret = gauss(A, b)
  [~, n] = size(A);
  for p = 1:n
    [~, q] = max(abs(A(p:n, p)));
    q = q + p - 1;
    if q ~= p
      A([p, q], :) = A([q, p], :);
      b([p, q]) = b([q, p]);
    endif
    for i = (p + 1):n
      temp = A(i, p) / A(p, p);
      b(i) = b(i) - temp * b(p);
      A(i, p:n) = A(i, p:n) - temp * A(p, p:n);
    endfor
  endfor
  ret = backward(A, b);
end