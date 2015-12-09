set title "lcline_qss"
set xrange [0:1200]
set grid
plot "/opt/qss-solver/output/lcline_qss/VecInt_1_y_1[1000].dat" with lines title "VecInt_1_y_1[1000]", "/opt/qss-solver/output/lcline_qss/VecInt_1_y_1[1].dat" with lines title "VecInt_1_y_1[1]" 

set term png
set output "lclines-qss.png"
replot
set term x11
