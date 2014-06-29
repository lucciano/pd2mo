model Model01
  Real contant_1_y, contant_1_k = 1;
  constant Integer sum_1_N = 2;
  Real sum_1_u[sum_1_N];
  Real sum_1_y;
  Real sum_1_w[sum_1_N] = {1,-1};
  Real integrator_1_u;
  Real integrator_1_x0; 
  Real integrator_1_y[1] = integrator_1_x0;
initial algorithm
  for sum_1_i in 1:sum_1_N loop
	w[sum_1_i]:=p[sum_1_i];
  end for;
equation
  der(integrator_1_y[1]) = integrator_1_u;
  sum_1_y = sum_1_w[1] * sum_1_u[1] + sum_1_w[2] * sum_1_u[2];
  contant_1_y = contant_1_k;
  contant_1_y = sum_1_u[1];
  integrator_1_y = sum_1_u[2];
  sum_1_y = integrator_1_u;
  annotation(experiment(StartTime = 0, StopTime = 10, Tolerance = 1e-06, Interval = 0.02));
end Model01;
