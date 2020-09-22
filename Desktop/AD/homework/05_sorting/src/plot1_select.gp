reset
set grid
set border lw 0.2;  
set key Left left font ",11"
set tics font ",11"
set xlabel "n" font ",12"
set ylabel "execution time" font ",12"   
set xrange [4:1048576]
plot "times1_select.dat" u 1:2 w l title "Quick Sort Random Case",\
     "times1_select.dat" u 1:3 w l title "Quick Sort Select Random Case"