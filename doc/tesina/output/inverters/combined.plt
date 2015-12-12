set xrange [0:250 ] ; set grid ; set title 'Plot'
set datafile separator ","
plot  "18002960.csv" using 1:3 with lines title 'Voltage u1', \
"18002960.csv" using 1:2 with lines title 'Voltage uN', \
"VecInt_2_y_1[1].dat" with lines title "VecInt_2_y_1[1]", \
"VecInt_2_y_1[1000].dat" with lines title "VecInt_2_y_1[1000]"

set autoscale xy


set term png
set output "inverters-all.png"
replot
set term x11
