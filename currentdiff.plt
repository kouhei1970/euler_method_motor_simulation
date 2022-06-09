#gnuplotでオイラー法とルンゲクッタ法の差をプロット
#電流
set grid
set xlabel "Time[s]"
set ylabel "Current diff[A]"
plot "motor.dat" u 1:($2-$3) w l lw 2
