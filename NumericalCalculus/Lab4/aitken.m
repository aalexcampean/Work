% Computing it using Aitken-type methods
% Lecture3 - 1.21

function z = aitken(x,y,a)
  er = 1e-3;
  [z, I] = sort(abs(x-a));
  x = x(I);
  y = y(I);
  n=length(x);

  ak=zeros(n,n);
  ak(:,1)=y';
  
  for i=1:n
      for j=1:i-1
         ak(i,j+1) = (1/(x(i)-x(j))) * (ak(j,j) * (x(i)-a) - ak(i,j) * (x(j)-a));
      endfor
      
      if i>1 && abs(ak(i-1,i-1)-ak(i,i))<=er
            z = ak(i,i);
            return
      endif
end