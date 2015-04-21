model qss_switch
  parameter Real p[1] = {0};
  parameter Real level = p[1];
  Real u[3];
  Real y[1];
  discrete Real d;
equation
  y[1] = u[1] * d + u[3] * (1 - d);
initial algorithm
  if u[2] > level then
    d := 1;
  elseif u[2] < level then
    d := 0;
  end if;
algorithm
  when u[2] > level then
    d := 1;
  elsewhen u[2] < level then
    d := 0;
  end when;
end qss_switch;
