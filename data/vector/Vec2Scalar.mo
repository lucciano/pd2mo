class Vec2Scalar
	parameter Real p[9]={40,0,0,0,0,0,0,0,0};

	parameter Integer Index=p[1];
	Real u[N][1];
	Real y[1];
equation
	y[1]=u[Index][1];
	annotation (PD2MO={Vector,Scalar});
end Vec2Scalar;

