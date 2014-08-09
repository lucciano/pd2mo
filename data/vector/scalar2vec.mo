class Scalar2Vector
	parameter Real p[9]={40,0,0,0,0,0,0,0,0};
	constant Integer N=0;//p[2];
	parameter Integer Index=40;//p[1];
	Real u[1];
	Real y[N,1];
equation
	for i in 1:N loop
		y[i,1]= (if Index==i or Index==-1 then u[1] else 0);
	end for;
	annotation (PD2MO={Scalar,Vector});
end Scalar2Vector;
