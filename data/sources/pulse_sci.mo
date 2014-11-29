model pulse_sci
  constant Real p[4] = {1, 1, 1, 2};
  Real y[1];
  parameter Real low = p[1];
  parameter Real amplitude = p[2];
  parameter Real ti = p[3];
  parameter Real tf = p[4];
  discrete Real d(start = low);
equation
  y = d;
algorithm
  when time > ti then
    d := low + amplitude;
  end when;
  when time > tf then
    d := low;
  end when;
end pulse_sci;
