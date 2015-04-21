class qss_quantizer
  parameter Real p[2]={1,0};
  parameter Real dQ = p[1];
  discrete Real level(start=0);
  Real u[1];
  Real y[1];
equation
  y[1]=pre(level);
initial algorithm
  if u[1]>level+dQ then
    level:=level+dQ;
  end if ;
  if u[1]<level then
    level:=level-dQ;
  end if ;
algorithm
  when u[1]>level+dQ then
    level:=level+dQ;
  end when;
  when u[1]<level then
    level:=level-dQ;
  end when;

end qss_quantizer;
