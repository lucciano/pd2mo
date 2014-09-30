model Pd2Model
  parameter Real Constant_0_k = 1;
  Real Constant_0_y[1](start = {Constant_0_k});
  parameter Real WSum_1_p[9] = {1,-1,0,0,0,0,0,0,2};
  parameter Integer WSum_1_n = integer(2);
  parameter Real WSum_1_w[WSum_1_n] = WSum_1_p[1:WSum_1_n];
  Real WSum_1_u[WSum_1_n];
  Real WSum_1_y[1];
  parameter Real QSSIntegrator_2_x0 = 0;
  Real QSSIntegrator_2_u[1];
  Real QSSIntegrator_2_y[1](start = {QSSIntegrator_2_x0});
  equation
    Constant_0_y[1] = Constant_0_k;
    WSum_1_y[1] = WSum_1_u*WSum_1_w;
    der(QSSIntegrator_2_y[1]) = QSSIntegrator_2_u[1];
    WSum_1_u[1] = Constant_0_y[1];
    QSSIntegrator_2_u[1] = WSum_1_y[1];
    WSum_1_u[2] = QSSIntegrator_2_y[1];
end Pd2Model;
