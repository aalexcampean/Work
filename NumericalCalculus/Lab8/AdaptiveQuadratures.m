function A = AdaptiveQuadratures(f,a,b,e,method,n)
    A1 = method(f,a,b,n);
    A2 = method(f,a,b,2*n);
    if(abs(A1-A2)<e)
        A = A2;
    else
        A = AdaptiveQuadratures(f,a,(a+b)/2,e,method,n)+AdaptiveQuadratures(f,(a+b)/2,b,e,method,n);
    end
end