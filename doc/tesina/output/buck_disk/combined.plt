set xrange [0:0.01 ] ; set grid ; set title 'Plot'
set datafile separator ","
plot  "32978672.csv" using 1:2 with lines title 'Current',  "32978672.csv" using 1:3 with lines title 'Voltage', "QSSIntegrator_1_y[1].dat" with lines title "QSSIntegrator_1_y[1]", "QSSIntegrator_2_y[1].dat" with lines title "QSSIntegrator_2_y[1]" 
set autoscale xy

set term png
set output "buck_disk-all.png"
replot
set term x11
