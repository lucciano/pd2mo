model vector_pow2
  constant Real p[1] = {1};
  constant Integer N = integer(p[1]);
  Real u[N, 1];
  Real y[N, 1];
equation
  for i in 1:N loop
    y[i, 1] = u[i,1]*u[i,1];
  end for;
  annotation (PD2MO={Vector,Vector});
end vector_pow2;
