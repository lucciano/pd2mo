model Integrador
  parameter Real QSSIntegrator_0_p[4] = {0,1e-06,0.001,0};
  parameter Real QSSIntegrator_0_x0 = 0;
  Real QSSIntegrator_0_u[1];
  Real QSSIntegrator_0_y[1](start = {0});
  parameter Real WSum_1_p[9] = {1,(-1),0,0,0,0,0,0,2};
  parameter Integer WSum_1_n = integer(2);
  parameter Real WSum_1_w[WSum_1_n] = WSum_1_p[1:WSum_1_n];
  Real WSum_1_u[WSum_1_n];
  Real WSum_1_y[1];
  parameter Real Constant_2_k = 1;
  Real Constant_2_y[1];
  equation
    der(QSSIntegrator_0_y[1]) = QSSIntegrator_0_u[1];
    WSum_1_y[1] = WSum_1_u*WSum_1_w;
    Constant_2_y[1] = 1;
    QSSIntegrator_0_u[1] = WSum_1_y[1];
    WSum_1_u[2] = QSSIntegrator_0_y[1];
    WSum_1_u[1] = Constant_2_y[1];
end Integrador;

