set xrange [0:0.01 ] ; set grid ; set title 'Plot'
set datafile separator ","
plot  "plots/32978672.csv" using 1:2 with lines title 'Current',  "plots/32978672.csv" using 1:3 with lines title 'Voltage'

set terminal wxt persist