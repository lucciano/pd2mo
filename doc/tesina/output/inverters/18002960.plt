set xrange [0:250 ] ; set grid ; set title 'Plot'
set datafile separator ","
plot  "18002960.csv" using 1:2 with lines title 'Voltage uN',  "18002960.csv" using 1:3 with lines title 'Voltage u1'

set term png
set output "inverters-qss.png"
replot
set term x11
