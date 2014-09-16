class VectorSum
  parameter Real p[10] = {1, 1, 0, 0, 0, 0, 0, 0, 2, 1000};
  constant Integer N = 1000;
  constant Integer nin = 2;
  parameter Real w[nin] = p[1:nin];
  Real u[N, nin];
  Real y[N, 1];
equation
  for i in 1:N loop
    y[i, 1] = u[i, 1:nin] * w;
  end for;
  annotation(PD2MO = {Vector, Vector});
end VectorSum;