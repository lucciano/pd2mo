model index_minus
  parameter Integer N = 10;
  Real y[N], u[N];
  parameter Integer shift = -3;
equation
  if shift > 0 then
    for i in 1:N + shift loop
      y[i] = u[i - shift];
    end for;
    for i in N + shift + 1:N loop
      y[i] = 0;
    end for;
  else
    for i in 1:N + shift loop
      y[i] = u[i - shift];
    end for;
    for i in N + shift + 1:N loop
      y[i] = 0;
    end for;
  end if;
end index_minus;