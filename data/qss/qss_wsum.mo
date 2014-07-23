class WSum
	parameter Real p[9]={0,0,0,0,0,0,0,0};
	parameter Integer n= integer(p[9]);
	parameter Real w[n] = p[1:n];
 	Real u[n];
	Real y[1];
equation
	y[1]=u*w;
end WSum;
	
