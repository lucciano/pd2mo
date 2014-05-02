class WSum
  constant Integer N = 8;
  Real u[N] = {0,0,0,0,0,0,0,0};
  Real y;
  parameter Real w[N] = {1,-1,0,0,0,0,0,0};
equation
  y = w[1] * u[1] + w[2] * u[2] + w[3] * u[3] + w[4] * u[4] + w[5] * u[5] + w[6] * u[6] + w[7] * u[7] + w[8] * u[8];
end WSum;
