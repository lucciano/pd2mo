model hysteretic_vec
  constant Real p[5] = {1, 1, 1, 1, 1};
  parameter Real xl = p[1];
  parameter Real xu = p[2];
  parameter Real yl = p[3];
  parameter Real yu = p[4];
  constant Integer N = integer(p[5]);
  Real u[N, 1];
  Real y[N, 1];
  discrete Real state[N];
equation
  for i in 1:N loop
    y[i, 1] = state[i];
  end for;
algorithm
  for i in 1:N loop
    when u[i, 1] > xu then
      state[i] := yu;
    end when;
  end for;
  for i in 1:N loop
    when u[N, 1] < xl then
      state[i] := yl;
    end when;
  end for;
  annotation (PD2MO={Vector,Vector});
end hysteretic_vec;
