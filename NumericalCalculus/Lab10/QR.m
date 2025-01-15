% In Octave, the qr function is used to compute the QR decomposition of a matrix. 
% QR decomposition represents a matrix as the product of an orthogonal matrix (Q) 
% and an upper triangular matrix (R)
function ret = QR(A, b)
  [Q, R] = qr(A);
  ret = backward(R, Q' * b);
end