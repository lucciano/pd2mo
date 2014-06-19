class Constant
  parameter Real k = 1;
  Real y[1] (start = {k});
equation
  y[1] = k;
end Constant;
