model index_plus
  parameter Integer N = 10;
  Real y[N], u[N];
  parameter Integer shift = 1;
equation
  for i in 1 + shift:N loop
    y[i] = u[i - shift];
  end for;
  for i in 1:shift loop
    y[i] = 0;
  end for;
end index_plus;