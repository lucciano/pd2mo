model hysteretic
  constant Real p[4] = {1, 2, 3, 4};
  parameter Real xl = p[1];
  parameter Real xu = p[2];
  parameter Real yl = p[3];
  parameter Real yu = p[4];
  Real u[1];
  Real y[1];
  discrete Real state;
equation
  y[1] = state;
algorithm
  when time > 0  then
    if u[1] > xu then
      state := yu;
    end if;
    if u[1] < xl then
      state := yl;
    end if;
  end when;
  when u[1] > xu then
    state := yu;
  end when;
  when u[1] < xl then
    state := yl;
  end when;
end hysteretic;
