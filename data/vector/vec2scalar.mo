class Vec2Scalar
	parameter Real p[2]={1, 40};
	parameter Integer Index=p[1];
	constant Integer N = p[2];
	Real u[N,1];
	Real y[1];
equation
	y[1]=u[Index,1];
	annotation (PD2MO={Vector,Scalar});
end Vec2Scalar;

