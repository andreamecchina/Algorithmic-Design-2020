reset
set grid
set border lw 0.2;  
set key Left left font ",11"
set tics font ",11"
set xlabel "n" font ",12"
set ylabel "execution time" font ",12"   
set xrange [0:16384] 
plot "times.dat" every ::1 u 1:2 w l title "On Heaps",\
     "times.dat" every ::1 u 1:3 w l title "On Arrays"
