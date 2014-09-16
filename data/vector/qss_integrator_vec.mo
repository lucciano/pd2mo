class VecInt
  parameter Real p[5] = {0, 10, 0, 0, 10};
  constant Integer N = p[5];
  parameter Real x0 = p[4];
  Real u[N, 1];
  Real y[N, 1];
initial equation 
  for i in 1:N loop
    y[i,1] = x0;
  end for;
equation
  for i in 1:N loop
    der(y[i, 1]) = u[i, 1];
  end for;
  annotation(PD2MO = {Vector, Vector});
end VecInt;
