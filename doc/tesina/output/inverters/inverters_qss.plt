set title "inverters_qss"
set ylabel "State Variables"
set xlabel "Time"
set xrange [0:250]
set grid
plot "/home/luciano/qss-solver/output/inverters_qss/VecInt_2_y_1[1000].dat" with lines title "VecInt_2_y_1[1000]", "/home/luciano/qss-solver/output/inverters_qss/VecInt_2_y_1[1].dat" with lines title "VecInt_2_y_1[1]" 
