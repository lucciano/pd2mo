model CoupledIntegradaor
  parameter Real Constant_0_k = 1;
  Real Constant_0_y[1];
  parameter Real QSSIntegrator_2_p[4] = {0,1e-06,0.001,0};
  parameter Real QSSIntegrator_2_x0 = 0;
  Real QSSIntegrator_2_u[1];
  Real QSSIntegrator_2_y[1](start = {0});
  parameter Real WSum_3_p[9] = {1,(-1),0,0,0,0,0,0,2};
  parameter Integer WSum_3_n = integer(2);
  parameter Real WSum_3_w[WSum_3_n] = WSum_3_p[1:WSum_3_n];
  Real WSum_3_u[WSum_3_n];
  Real WSum_3_y[1];
  equation
    Constant_0_y[1] = 1;
    der(QSSIntegrator_2_y[1]) = QSSIntegrator_2_u[1];
    WSum_3_y[1] = WSum_3_u*WSum_3_w;
    WSum_3_u[1] = Constant_0_y[1];
    QSSIntegrator_2_u[1] = WSum_3_y[1];
    WSum_3_u[2] = QSSIntegrator_2_y[1];
end CoupledIntegradaor;

