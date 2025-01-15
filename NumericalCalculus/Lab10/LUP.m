function ret = LUP(A, b)
  [L, U, P] = lu(A);
  y = forward(L, P * b);
  ret = backward(U, y);
end