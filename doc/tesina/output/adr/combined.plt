set xrange [0:10 ] ; set grid ; set title 'Plot'
set datafile separator ","
plot  "28302480.csv" using 1:2 with lines title 'Last output',  "28302480.csv" using 1:3 with lines title 'First output', "VecInt_1_y_1[1000].dat" with lines title "VecInt_1_y_1[1000]", "VecInt_1_y_1[1].dat" with lines title "VecInt_1_y_1[1]" 


set term png
set output "adr-all.png"
replot
set term x11
