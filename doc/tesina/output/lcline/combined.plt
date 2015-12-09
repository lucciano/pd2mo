set xrange [0:1200 ] ; set grid ; set title 'Plot'
set datafile separator ","
plot  "21110912.csv" using 1:2 with lines title 'Voltage uN',  "21110912.csv" using 1:3 with lines title 'Voltage u1', "VecInt_1_y_1[1000].dat" with lines title "VecInt_1_y_1[1000]", "VecInt_1_y_1[1].dat" with lines title "VecInt_1_y_1[1]" 


set term png             
set output "lcline-all.png" 
replot
set term x11
