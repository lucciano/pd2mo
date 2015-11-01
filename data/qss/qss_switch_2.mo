model qss_switch
  parameter Real p[1] = {0};
  parameter Real level = p[1];
  Real u[3];
  Real y[1];
equation
  when u[2] > level
	  y[1] = u[1];
  elsewhen u[2] < level
	  y[1] = u[3];
end qss_switch;
