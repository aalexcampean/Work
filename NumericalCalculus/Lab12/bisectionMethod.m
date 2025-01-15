% Ex3 using the bisection method

function bisectionMethod(a, b, epsilon, max_iterations)
    f = @(x) (x^2) * log(x); % The function
    
    i = 1;
    while i <= max_iterations
        c = (a + b) / 2; % Compute the midpoint of the interval
        fa = f(a); % Evaluate the values of the function in the points a, b, c
        fb = f(b);
        fc = f(c);
        
        if fa * fc < 0 % Check if f(a) and f(c) have opposite signs
            b = c;
        else
            a = c;
        end
        
        if b - a < epsilon
            break;
        end
        
        i = i + 1;
    end
    
    x = (a + b) / 2;
    fprintf('Approximation: x = %.6f\n', x);
end

a = 1;
b = 2;
epsilon = 1e-4;
max_iterations = 100;

bisectionMethod(a, b, epsilon, max_iterations);