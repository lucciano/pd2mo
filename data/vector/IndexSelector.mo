class IndexSelector
  parameter Real p[3] = {3, 9, 100};
  parameter Integer L = p[1];
  parameter Integer H = p[2];
  constant Integer N = p[3];
  Real u[N, 1];
  Real y[N, 1];
equation
  for i in 1:N loop
    y[i, 1] = if i > L and i <= H then u[i, 1] else 0;
  end for;
  annotation(PD2MO = {Vector, Vector});
end IndexSelector;
