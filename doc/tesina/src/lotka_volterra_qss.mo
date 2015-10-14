model lotka_volterra
  Real x(start = 0.5);
  Real y(start = 0.5);
  parameter Real a = 0.1;
  parameter Real b = 0.1;
  parameter Real c = 0.1;
  parameter Real d = 0.1;
initial algorithm 
  x := 0.5;
  y := 0.5;
equation
  der(x) =  x * (a - b * y);
  der(y) =  - y * (d - c * x);
	annotation(
	experiment(
		MMO_Description="Lotka Volterra model",
		MMO_Solver=QSS3,
		MMO_Output={x[:]},
		StartTime= 0.0,
		StopTime= 300.0,
		Tolerance={ 1e-3},
		AbsTolerance={ 1e-6}
	));
end lotka_volterra;
