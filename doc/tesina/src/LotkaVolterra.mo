class LotkaVolterra
  Real x(start = 0.5);
  Real y(start = 0.5);
  parameter Real a = 0.1;
  parameter Real b = 0.1;
  parameter Real c = 0.1;
  parameter Real d = 0.1;
equation
  0 =  x * (a - b * y) - der(x);
  0 = der(y) + y * (d - c * x);
end LotkaVolterra;
