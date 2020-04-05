set term pngcairo
set output "stddev.png"

set xlabel "Number of Samples"
set ylabel "Std. Dev."
set log xy

p "test.dat" u 1:4 t "Data" pt 6\
, 0.28/sqrt(x) lt 1 lc rgb "black" t "1/sqrt(x)"
