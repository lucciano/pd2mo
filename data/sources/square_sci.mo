model square_sci
  constant Real p[3] = {1, 440, 75};

  parameter Real amplitude = p[1];
  parameter Real freq = p[2];
  parameter Real DC = p[3]/100;
  discrete Real lev(start = 1);
  discrete Real next(start = 0);
  Real y[1];
initial algorithm
  next:= DC/freq;
equation
  y[1] = pre(lev)*amplitude;
algorithm
  when time > next then
	lev:=1-lev;
	next:=time+lev*DC/freq+(1-lev)*(1-DC)/freq;	
  end when;
end square_sci;
