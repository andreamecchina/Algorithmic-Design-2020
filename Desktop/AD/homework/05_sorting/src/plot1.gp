reset
set grid
set border lw 0.2;  
set key Left left font ",11"
set tics font ",11"
set xlabel "n" font ",12"
set ylabel "execution time" font ",12"   
set xrange [4:8192] 
plot "times1.dat" u 1:2 w l title "Insertion Sort Random Case",\
     "times1.dat" u 1:3 w l title "Quick Sort Random Case",\
     "times1.dat" u 1:4 w l title "Bubble Sort Random Case",\
     "times1.dat" u 1:5 w l title "Selection Sort Random Case",\
     "times1.dat" u 1:6 w l title "Heap Sort Random Case"