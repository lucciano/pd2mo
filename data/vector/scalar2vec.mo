class Scalar2Vector
	parameter Real p[2]={-1,40};
	constant Integer N=p[2];
	parameter Integer Index=p[1];
	Real u[1];
	Real y[N,1];
equation
	for i in 1:N loop
		y[i,1]= (if Index+1==i or Index==-1 then u[1] else 0);
	end for;
	annotation (PD2MO={Scalar,Vector});
end Scalar2Vector;
