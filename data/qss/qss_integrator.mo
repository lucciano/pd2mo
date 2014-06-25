class QSSIntegrator
  parameter Real x0 = 0;
  Real u[1];
  Real y[1](start = {x0});
equation
  der(y[1]) = u[1];
end QSSIntegrator;
