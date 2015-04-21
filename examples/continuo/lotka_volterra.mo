model lotka_volterra
  Real qss_multiplier_0_u[2];
  Real qss_multiplier_0_y[1];
  parameter Real QSSIntegrator_1_p[4] = {0,1e-06,0.001,0.5};
  parameter Real QSSIntegrator_1_x0 = 0.5;
  Real QSSIntegrator_1_u[1];
  Real QSSIntegrator_1_y[1](start = {QSSIntegrator_1_x0});
  parameter Real QSSIntegrator_2_p[4] = {0,1e-06,0.001,0.5};
  parameter Real QSSIntegrator_2_x0 = 0.5;
  Real QSSIntegrator_2_u[1];
  Real QSSIntegrator_2_y[1](start = {QSSIntegrator_2_x0});
  parameter Real WSum_3_p[9] = {0.1,(-0.1),0,0,0,0,0,0,2};
  parameter Integer WSum_3_n = integer(2);
  parameter Real WSum_3_w[WSum_3_n] = WSum_3_p[1:WSum_3_n];
  Real WSum_3_u[WSum_3_n];
  Real WSum_3_y[1];
  parameter Real WSum_4_p[9] = {0.1,(-0.1),0,0,0,0,0,0,2};
  parameter Integer WSum_4_n = integer(2);
  parameter Real WSum_4_w[WSum_4_n] = WSum_4_p[1:WSum_4_n];
  Real WSum_4_u[WSum_4_n];
  Real WSum_4_y[1];
  equation
    qss_multiplier_0_y[1] = qss_multiplier_0_u[1]*qss_multiplier_0_u[2];
    der(QSSIntegrator_1_y[1]) = QSSIntegrator_1_u[1];
    der(QSSIntegrator_2_y[1]) = QSSIntegrator_2_u[1];
    WSum_3_y[1] = WSum_3_u*WSum_3_w;
    WSum_4_y[1] = WSum_4_u*WSum_4_w;
    qss_multiplier_0_u[1] = QSSIntegrator_1_y[1];
    qss_multiplier_0_u[2] = QSSIntegrator_2_y[1];
    QSSIntegrator_1_u[1] = WSum_3_y[1];
    WSum_3_u[2] = qss_multiplier_0_y[1];
    WSum_3_u[1] = QSSIntegrator_1_y[1];
    QSSIntegrator_2_u[1] = WSum_4_y[1];
    WSum_4_u[1] = qss_multiplier_0_y[1];
    WSum_4_u[2] = QSSIntegrator_2_y[1];
end lotka_volterra;

