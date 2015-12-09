set xrange [0:300 ] ; set grid ; set title 'Lotka Volterra Model'
set yrange [0:2.5]
set datafile separator ","
plot  "26738368.csv" using 1:2 with lines title 'Preys',  "26738368.csv" using 1:3 with lines title 'Predators'

set term png             
set output "lotka_volterra-pd.png" 
replot
set term x11
