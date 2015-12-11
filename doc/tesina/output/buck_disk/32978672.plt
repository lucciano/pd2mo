set xrange [0:0.01 ] ; set grid ; set title 'Plot'
set datafile separator ","
plot  "32978672.csv" using 1:2 with lines title 'Current',  "32978672.csv" using 1:3 with lines title 'Voltage'


set term png
set output "buck_disk-pd.png"
replot
set term x11
