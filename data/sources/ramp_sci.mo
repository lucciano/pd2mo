model ramp_sci
  constant Real p[5] = {5, 5, 5, 1, 2};
  parameter Real t0 = p[1];
  parameter Real tr = p[2];
  parameter Real v = p[3];
  discrete Real s, e;
  Real y[1];
initial algorithm
  e := 0;
  s := 0;
equation
  y[1] = (1-pre(e))*pre(s) * ((time-t0) * v / tr)+ pre(e)*v;
algorithm
  when time > t0 then
    s := 1;
  end when;
  when time > t0 + tr then
    e := 1;
  end when;
end ramp_sci;
