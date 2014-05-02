class QSSIntegrator
  parameter Real x0 = 0;
  Real u;
  Real y(start = x0);
equation
  der(y) = u;
end QSSIntegrator;
