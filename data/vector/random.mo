model random
  Real y;

  function rand
    output Real y;
    input Real u;
  algorithm
    y := u;
  end rand;

  // import math;
  parameter Real T = 1;
  discrete Real d;
  discrete Real next_t(start = 0);
equation
  y = d;
algorithm
  when time > next_t then
    d := rand(5);
    next_t := next_t + T;
  end when;
end random;