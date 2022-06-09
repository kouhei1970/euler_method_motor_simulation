#gnuplotでオイラー法とルンゲクッタ法の差をプロット
#角速度
set grid
set xlabel "Time[s]"
set ylabel "Omega diff[rad/s]"
plot "motor.dat" u 1:($4-$5) w l lw 2
