set title "buck_disc_qss"
set ylabel "State Variables"
set xlabel "Time"
set xrange [0:0.01]
set grid
plot "/opt/qss-solver/output/buck_disc_qss/QSSIntegrator_1_y[1].dat" with lines title "QSSIntegrator_1_y[1]", "/opt/qss-solver/output/buck_disc_qss/QSSIntegrator_2_y[1].dat" with lines title "QSSIntegrator_2_y[1]" 
