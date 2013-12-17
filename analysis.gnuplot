#!/usr/bin/env gnuplot

reset
set terminal pdfcairo color enhanced dashed
set pointsize 0.5
set output "analysis.pdf"

set multiplot layout 2,2

set xlabel "t"
set title "EKin"
plot "EKin.dat" u 1:2 w l notitle
set title "COM motion"
plot "Q.dat" u 1:2 w l notitle

set xlabel "N"
set title "Sigma stuff"
plot "Var.dat" u 1:2 w p pt 6 notitle
set title "Time"
plot "Var.dat" u 1:3 w p pt 6 notitle

unset multiplot
