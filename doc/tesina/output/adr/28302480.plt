set xrange [0:10 ] ; set grid ; set title 'Plot'
set datafile separator ","
plot  "28302480.csv" using 1:2 with lines title 'Last output',  "28302480.csv" using 1:3 with lines title 'First output'

set term png
set output "adr-pd.png"
replot
set term x11
