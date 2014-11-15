model pulse
  Real y;
  parameter Real low = 1;
  parameter Real amplitude = 1;
  parameter Real ti = 1;
  parameter Real tf = 3;
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
end pulse;