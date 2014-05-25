class WSum
	parameter Real p[9]={0,0,0,0,0,0,0,0};
	constant Integer n=p[9];
	parameter Real w[n];
 	Real u[n];
	Real y[1];
initial algorithm
  for i in 1:n loop
	w[i]:=p[i];
  end for;
equation
	y[1]=u*w;
end WSum;
	
