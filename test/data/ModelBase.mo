model ModelBase
class Constant_a
  Real a_y;
  parameter Real a_k = 1;
equation
  a_y = a_k;
end Constant;
class Constant_b
  Real b_y;
  parameter Real b_k = 1;
equation
  b_y = b_k;
end Constant;
end ModelBase;
