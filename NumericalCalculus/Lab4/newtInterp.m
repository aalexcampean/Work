% Computing the Newton interpolation polynomial
% Lecture3 - 1.15

function retval = newtInterp(x, f, t)
	df = differences(x, f);
	m = length(x);

	p = 1;
	sol = 0;

  % adding the differences sequentially
	for i = 1:m
		sol += p * df(1, i+1);
		p = p * (t-x(i));
	end
	retval = sol;
end