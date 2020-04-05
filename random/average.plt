set term pngcairo
set output "average.png"

set xrange [300:10000] 
set yrange [0.46:0.54] 
set xlabel "Number of Samples"
set ylabel "Average and Std. Dev."
set xtics 2000
set ytics 0.02
unset key
p "test.dat" u 1:2:4 with errorbars, 0.5 lc rgb "black"
