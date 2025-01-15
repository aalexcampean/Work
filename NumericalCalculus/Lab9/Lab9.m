%Gaussian Function
function [I,gn,gc] = Gaussian(f,n,nrCase)
    alpha = zeros(1,n);
    switch nrCase
        case 1
            beta = [2,(4-(1:n-1).^(-2)).^(-1)]; % legendre case
        case 2
            beta = [pi,1/2,(1/4)*ones(1,n-2)]; % chebasev1 case
        case 3
            beta = [pi/2,(1/4)*ones(1,n-1)]; % chebasev2 case
        case 4 % laguerre case
            a = input('a = ');
            k = 1:n-1;
            alpha = [a+1,2*k+a+1];
            beta = [gamma(1+a),k.*(k+a)];
        case 5 % hermite case
            beta = [sqrt(pi),(1:n-1)/2];
    end
    J = diag(alpha) + diag(sqrt(beta(2:n)),1)+diag(sqrt(beta(2:n)),-1);
    [v,d] = eig(J);
    gn = diag(d);
    gc = beta(1)*v(1,:).^2;
    I = gc * f(gn);
end;

%1 - Hermite Function
f = @(x) (exp(-x.*x)./exp(-x.*x));
n = 2;
nrCase = 5;
[I,gn,gc] = Gaussian(f,n,nrCase)

f = @(x) (exp(-x.*x)./exp(-x.*x));
n = 8;
nrCase = 5;
[I,gn,gc] = Gaussian(f,n,nrCase)

%2 - Chebasev 2 Function
f = @(x) sqrt(x.^2+1)./ sqrt(x.^2+1);
n = 2;
nrCase = 3;
[I,gn,gc] = Gaussian(f,n,nrCase)


f = @(x) sqrt(x.^2+1)./ sqrt(x.^2+1);
n = 8;
nrCase = 3;
[I,gn,gc] = Gaussian(f,n,nrCase)

%3 - Legendre Function
f = @(x) sin(x.^2);
n = 2;
nrCase = 1;
[I,gn,gc] = Gaussian(f,n,nrCase)

f = @(x) sin(x.^2);
n = 8;
nrCase = 1;
[I,gn,gc] = Gaussian(f,n,nrCase)

%4 - Laguerre Function
f = @(x) sin(x);
n = 2;
nrCase = 4;
[I,gn,gc] = Gaussian(f,n,nrCase)

f = @(x) sin(x);
n = 8;
nrCase = 4;
[I,gn,gc] = Gaussian(f,n,nrCase)

%5 - Chebasev 1 Function
f = @(x) x.^2;
n = 2;
nrCase = 2;
[I,gn,gc] = Gaussian(f,n, nrCase)

f = @(x) x.^2;
n = 8;
nrCase = 2;
[I,gn,gc] = Gaussian(f,n, nrCase)
