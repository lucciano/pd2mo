set title "lcline_qss"
set xrange [0:1200]
set grid

set datafile separator ","
plot "VecInt_1_y_1[1000].dat" with lines title "VecInt_1_y_1[1000]", "VecInt_1_y_1[1].dat" with lines title "VecInt_1_y_1[1]" 

set term png
set output "lcline-qss.png"
replot
set term x11
