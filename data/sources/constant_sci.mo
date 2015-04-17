class Constant
  parameter Real p[1]={1};
  parameter Real k = p[1];
  Real y[1];
equation
  y[1] = k;
end Constant;
