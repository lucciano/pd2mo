class VecInt
  parameter Real p[5] = {0, 0, 0, 0, 0};
  constant Integer N = 10;
  //p[2];
  parameter Real x0[N](start = 0);
  /*p[1]*/
  Real u[N, 1];
  Real y[N, 1](start = x0);
equation
  for i in 1:N loop
    der(y[i, 1]) = u[i, 1];
  end for;
  annotation(PD2MO = {Vector, Vector});
end VecInt;
