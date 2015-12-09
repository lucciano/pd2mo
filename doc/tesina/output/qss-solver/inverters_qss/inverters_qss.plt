set title "inverters_qss"
set xrange [0:250]
set ytics 1
set grid
plot "/opt/qss-solver/output/inverters_qss/VecInt_2_y_1[1000].dat" with lines title "VecInt_2_y_1[1000]", "/opt/qss-solver/output/inverters_qss/VecInt_2_y_1[1].dat" with lines title "VecInt_2_y_1[1]" 


set term png
set output "inverters-qss.png"
replot
set term x11
