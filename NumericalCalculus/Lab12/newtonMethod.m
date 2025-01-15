% Ex1 using Newton's method

function newtonMethod(x0, epsilon, max_iterations)
    f = @(x) x - cos(x); % the function
    df = @(x) 1 + sin(x); % the derivative
    
    x = x0; % initializing the variables
    for i = 1:max_iterations % continues until the maximum number of iterations is reached or until the approximation error is below the tolerance:
        x = x - f(x) / df(x);
        
        if abs(f(x)) < epsilon
            break;
        end
    end
    
    fprintf('Approximation: x = %.6f\n', x);
end

x0 = 4;
epsilon = 1e-4;
max_iterations = 100;

newtonMethod(x0, epsilon, max_iterations);