n=10;
A=5*eye(n)-diag(ones(n-1,1),1)-diag(ones(n-1,1),-1)-diag(ones(n-3,1),3)-diag(ones(n-3,1),-3);
b=[3; 2; 2; ones(n-6,1); 2; 2; 3];
x0=zeros(size(b));
eps=0.001;
maxn=50;
Jacobi(A,b,x0,eps,maxn);
GaussSeidel(A,b,x0,eps,maxn);
SOR(A,b,x0,eps,maxn)