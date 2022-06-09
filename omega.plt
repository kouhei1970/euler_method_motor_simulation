set grid
set xlabel "Time[s]"
set ylabel "Omega[A]"
plot "motor.dat" u 1:($5) w l lw 2
