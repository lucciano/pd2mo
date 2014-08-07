class VectorSum
	parameter Real p[9]={1,-1,0,0,0,0,0,2,10};
	parameter Integer Index=p[1];

	constant Integer N=p[9];
	constant Integer nin=p[8];
	parameter Real w[nin]=p[1:nin];
	Real u[N][nin];
	Real y[N][1];
equation
	for i in 1:N loop
		y[i][1]=u[i]*w;
	end for;
	annotation (PD2MO={Vector,Vector});
end VectorSum;
