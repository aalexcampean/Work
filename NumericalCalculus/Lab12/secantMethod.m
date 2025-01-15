% Ex2 using the secant method

function secantMethod(x0, x1, epsilon, max_iterations)
    f = @(x) x^3 + x^2 - 1; % The function
    
    i = 2; 
    while i <= max_iterations
        x = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0)); % Calculate the next approximation using the secant method formula
        x0 = x1;
        x1 = x;
        
        if abs(f(x)) < epsilon % Check if the absolute value of f(x) is below the tolerance
            break;
        end
        
        i = i + 1;
    end
    
    fprintf('Approximation: x = %.6f\n', x);
end

x0 = 1;
x1 = 2;
epsilon = 1e-4;
max_iterations = 100;

secantMethod(x0, x1, epsilon, max_iterations);