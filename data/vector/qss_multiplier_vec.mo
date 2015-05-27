class qss_multiplier_vec
  parameter Real p[2] = {1};
  constant Integer N = p[1];
  Real u[N, 2];
  Real y[N,1];
equation
  for i in 1:N loop
    y[i,1] = u[i,1]*u[i,2];
  end for;
  annotation(PD2MO = {Vector, Vector});
end qss_multiplier_vec;
