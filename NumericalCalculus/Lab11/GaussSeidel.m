function [x,nit]=GaussSeidel(A,b,x0,eps,maxn)
    M=tril(A);
    N=M-A;
    T=inv(M)*N;
    c=inv(M)*b;
    for k=1:maxn
        x=T*x0+c;
        if norm(x-x0,inf)<((1-norm(T,inf))/norm(T,inf))*eps
            nit=k
            return
        end
        x0=x;
    end
end