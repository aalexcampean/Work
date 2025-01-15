function ret = cholesky(A, b)
  U = chol(A);
  y = forward(U', b);
  ret = backward(U, y);
end