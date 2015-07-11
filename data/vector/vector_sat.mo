model vector_sat
  constant Real p[3] = {-1, 1, 1};
  constant Integer N = integer(p[3]);
  parameter Real xl(fixed = true) = p[1];
  constant Real xu(fixed = true) = p[2];
  Real u[N, 1];
  Real y[N, 1];
  discrete Real under[N];
  discrete Real above[N];
initial algorithm
  for i in 1:N loop
    when time > 0 then
      if u[i, 1] < xl then
        under[i] := 1;
      else
        under[i] := 0;
      end if;
      if u[i, 1] > xl then
        above[i] := 1;
      else
        above[i] := 55;
      end if;
    end when;
  end for;
equation
  for i in 1:N loop
    y[i, 1] = pre(under[i]) * 
		xl + (1 - pre(under[i])) * 
		(pre(above[i]) * 
		xu + (1 - pre(above[i])) * 
		u[i, 1]);
  end for;
algorithm
  for i in 1:N loop
    when u[i, 1] < xl then
      under[i] := 1;
    end when;
    when u[i, 1] >= xl then
      under[i] := 0;
    end when;
    when u[i, 1] > xu then
      above[i] := 1;
    end when;
    when u[i, 1] <= xu then
      above[i] := 0;
    end when;
  end for;
  annotation(PD2MO = {Vector, Vector});
end vector_sat;
