class LotkaVolterra
  Real x(start = 0.5);
  Real y(start = 0.5);
  parameter Real a = 0.1;
  parameter Real b = 0.1;
  parameter Real c = 0.1;
  parameter Real d = 0.1;
equation
  der(x) = x * (a - b * y);
  der(y) = y * (c * x - d);
end LotkaVolterra;
