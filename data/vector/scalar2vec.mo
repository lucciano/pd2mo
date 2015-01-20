class Scalar2Vector
  constant Real p[2] = {-1, 10};
  constant Integer N = integer(p[2]);
  parameter Integer Index = integer(p[1]);
  Real u[1];
  Real y[N, 1];
equation
  if Index == (-1) then
    for i in 1:N loop
      y[i, 1] = u[1];
    end for;
  else
    for i in 1:Index loop
      y[i, 1] = 0;
    end for;
    y[Index + 1, 1] = u[1];
    for i in Index + 2:N loop
      y[i, 1] = 0;
    end for;
  end if;
end Scalar2Vector;
