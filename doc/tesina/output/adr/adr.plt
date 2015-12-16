set title "adr"
set ylabel "State Variables"
set xlabel "Time"
set xrange [0:6]
set yrange [0: 1.2 ]
set grid
set datafile separator ","
plot "VecInt_1_y_1[1000].dat" with lines title "VecInt_1_y_1[1000]", "VecInt_1_y_1[1].dat" with lines title "VecInt_1_y_1[1]" 

set term png
set output "adr-qss.png"
replot
set term x11
