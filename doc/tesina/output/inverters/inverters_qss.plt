set title "inverters_qss"
set ylabel "State Variables"
set xlabel "Time"
set xrange [0:250]
set grid
set datafile separator ","
plot "VecInt_2_y_1[1000].dat" with lines title "VecInt_2_y_1[1000]", "VecInt_2_y_1[1].dat" with lines title "VecInt_2_y_1[1]" 

set term png
set output "inverters-qss.png"
replot
set term x11
