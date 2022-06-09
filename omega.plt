#gnuplotで角速度プロット（ルンゲクッタ）
set grid
set xlabel "Time[s]"
set ylabel "Omega[rad/s]"
plot "motor.dat" u 1:5 w l lw 2
