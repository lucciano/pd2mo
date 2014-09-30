model Pd2Model
  parameter Real WSum_0_p[9] = {1,1,0,0,0,0,0,0,2};
  parameter Integer WSum_0_n = integer(2);
  parameter Real WSum_0_w[WSum_0_n] = WSum_0_p[1:WSum_0_n];
  Real WSum_0_u[WSum_0_n];
  Real WSum_0_y[1];
  parameter Real Constant_1_k = 1;
  Real Constant_1_y[1](start = {Constant_1_k});
  parameter Real Constant_2_k = 1;
  Real Constant_2_y[1](start = {Constant_2_k});
  parameter Real QSSIntegrator_4_x0 = 0;
  Real QSSIntegrator_4_u[1];
  Real QSSIntegrator_4_y[1](start = {QSSIntegrator_4_x0});
  parameter Real WSum_5_p[9] = {1,-1,0,0,0,0,0,0,2};
  parameter Integer WSum_5_n = integer(2);
  parameter Real WSum_5_w[WSum_5_n] = WSum_5_p[1:WSum_5_n];
  Real WSum_5_u[WSum_5_n];
  Real WSum_5_y[1];
  equation
    WSum_0_y[1] = WSum_0_u*WSum_0_w;
    Constant_1_y[1] = Constant_1_k;
    Constant_2_y[1] = Constant_2_k;
    der(QSSIntegrator_4_y[1]) = QSSIntegrator_4_u[1];
    WSum_5_y[1] = WSum_5_u*WSum_5_w;
    WSum_5_u[1] = WSum_0_y[1];
    QSSIntegrator_4_u[1] = WSum_5_y[1];
    WSum_5_u[2] = QSSIntegrator_4_y[1];
end Pd2Model;
