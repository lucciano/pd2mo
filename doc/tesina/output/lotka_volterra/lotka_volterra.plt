set title "lotka_volterra"
set ylabel "State Variables"
set xlabel "Time"
set xrange [0:300]

set grid
set datafile separator ","
plot "QSSIntegrator_1_y[1].dat" with lines title "QSSIntegrator_1_y[1]", "QSSIntegrator_2_y[1].dat" with lines title "QSSIntegrator_2_y[1]" 

set term png  
set output "lotka_volterra-qss.png"
replot
set term x11
