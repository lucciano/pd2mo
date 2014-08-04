class IndexShift
	parameter Real p[9]={50,100,0,0,0,0,0,0,0};
	parameter Integer Shift=p[1];
	constant Integer N=p[2];
	Real u[N][1];
	Real y[N][1];
equation
	for i in 1:N loop
		y[i][1]=(if i-Shift >0 and i-Shift<N then u[i-Shift] else 0);
	end for;
	annotation (PD2MO={Vector,Vector});
end IndexShift;
