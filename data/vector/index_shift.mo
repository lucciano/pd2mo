class IndexShift
  constant Real p[2] = {-1, 10};
  constant Integer Shift = integer(p[1]);
  constant Integer N = integer(p[2]);
  Real u[N, 1];
  Real y[N, 1];
equation
  if Shift > 0 then
    for i in 1:N - Shift loop
      y[i + Shift, 1] = u[i, 1];
    end for;
    for i in 1:Shift loop
      y[i, 1] = 0;
    end for;
  else
    for i in 1:N + Shift loop
      y[i, 1] = u[i - Shift, 1];
    end for;
    for i in N + Shift + 1:N loop
      y[i, 1] = 0;
    end for;
  end if;
  annotation(PD2MO = {Vector, Vector});
end IndexShift;
