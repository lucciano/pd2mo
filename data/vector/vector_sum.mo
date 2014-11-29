class vector_sum
  parameter Real p[2] = {1, 10};
  constant Integer N = p[2];
  Real u[N, 1];
  Real y[1];
  Real K = p[1];
equation
  y[1] = K * sum(u[:,1]);
  annotation(PD2MO = {Vector, Scalar});
end vector_sum;
