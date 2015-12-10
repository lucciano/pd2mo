set title "adr"
set ylabel "State Variables"
set xlabel "Time"
set xrange [0:10]
set grid
set datafile separator ","
plot "VecInt_1_y_1[1000].dat" with lines title "VecInt_1_y_1[1000]", "VecInt_1_y_1[1].dat" with lines title "VecInt_1_y_1[1]" 
