class VectorSum
  constant Integer N = 10;
  constant Integer nin = 5;
  parameter Real w[nin] = p[1:nin];
  Real u[N, nin];
  Real y[N, 1];
  annotation(PD2MO = {Vector, Vector});
end VectorSum;
