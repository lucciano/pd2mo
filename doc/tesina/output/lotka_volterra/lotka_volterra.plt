set title "lotka_volterra"
set ylabel "State Variables"
set xrange [0:300]
set yrange [0:2.5]
set grid
plot "/opt/qss-solver/output/lotka_volterra/QSSIntegrator_1_y[1].dat" with lines title "QSSIntegrator_1_y[1]", "/opt/qss-solver/output/lotka_volterra/QSSIntegrator_2_y[1].dat" with lines title "QSSIntegrator_2_y[1]" 

set term png  
set output "lotka_volterra-qss.png"
replot
set term x11
