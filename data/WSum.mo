class WSum
  constant Integer N = 8;
  Real u[N] = {0,0,0,0,0,0,0,0};
  Real y;
  parameter Real w[N] = {1,-1,0,0,0,0,0,0};
equation
  y = product(w,u,N);
end WSum;
