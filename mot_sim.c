/****************************
 *                          *
 * オイラー法による         *
 * DCモータシミュレーション *
 * サンプルプログラム       *
 *                          *
 ****************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> //可変長引数関数を使うために必要

const double Lm = 3.7e-4;//Inductance[H]
const double Rm = 1.2e-1;//Resistance[Ohm]
const double Km = 3.3e-3;//Torque constant[Nm/A]
const double Jm = 8.1e-6;//Moment of inertia[kg m^2]
const double Cq = 3.0e-8;//Cofficient of torque (Propeller)
const double Dm = 0.0;   //Cofficient of viscous damping [Nm s]
const double End_time = 0.05;//Time [s]

//Equation of current
//Lm di/dt + Rm i + Km omega = u
//i:current
//t:time
//value[0]:omega
//value[1]:u
double i_dot(double i, double t, double *value)
{
  double omega = value[0];
  double u = value[1];
  return (u - Rm * i - Km * omega)/Lm;
}

//Equation of motion
//TL = Cq omega^3
//Jm domega/dt + Dm omega + TL = Km i
//omega:angular velocity
//t:time
//value[0]:i
double omega_dot(double omega, double t, double *value)
{
  double i=value[0];
  double TL=Cq * omega * omega * omega;
  return (Km * i - Dm * omega - TL)/Jm;
}

//Euler method
//dxdy:derivative
//x:state
//t:time
//h:step size
//n:argument
double euler(double (*dxdt)(double, double, double*), double x, double t, double h, int n, ...)
{
  va_list args;//可変長マクロで必要なデータ型を宣言
  double *value;
  double k1;

  value=(double*)malloc(sizeof(double) * n);//可変長引数メモリ確保
  va_start(args , n);//可変長引数処理開始
  for(int i=0;i<n;i++)
  {
    value[i]=va_arg(args, double);
  }
  va_end(args);//引数処理終了
  //Euler method
  k1 = h * dxdt(x, t, value);
  free(value);//メモリ解放
  return x+k1;
}

//Runge Kutta method
//dxdy:derivative
//x:state
//t:time
//h:step size
//n:argument
double rk4(double (*dxdt)(double, double, double*), double x, double t, double h, int n, ...)
{
  va_list args;
  double *value;
  double k1,k2,k3,k4;

  value=(double*)malloc(sizeof(double) * n);
  va_start(args , n);
  for(int i=0;i<n;i++)
  {
    value[i]=va_arg(args, double);
  }
  va_end(args);
  
  k1 = h * dxdt(x, t, value);
  k2 = h * dxdt(x+0.5*h*k1, t+0.5*h, value);
  k3 = h * dxdt(x+0.5*h*k2, t+0.5*h, value);
  k4 = h * dxdt(x+h*k3, t+h, value);

  free(value);
  
  return x+(k1 + k2*2.0 + k3*2.0 + k4)/6;
}

void main(void)
{
  double t     = 0.0; //time
  double omega_e = 0.0; //angular verocity
  double i_e     = 0.0; //current
  double omega_r = 0.0; //angular verocity
  double i_r     = 0.0; //current
  double u     = 7.4; //input voltage
  double h     = 0.0001;//step size
  double _i_e, _omega_e, _i_r, _omega_r;  //for old state

  printf("%11.8f %11.8f %11.8f %11.8f %11.8f\n",t, i_e, i_r, omega_e, omega_r);
  while(t < End_time )    
  {
    //Save state
    _i_e = i_e;
    _omega_e = omega_e;
    _i_r = i_r;
    _omega_r = omega_r;

    //Update(Euler method)
    i_e = euler(i_dot, _i_e, t, h, 2, _omega_e, u);
    omega_e = euler(omega_dot, _omega_e, t, h, 1, _i_e);
    //Update(Runge-Kutta method)
    i_r = rk4(i_dot, _i_r, t, h, 2, _omega_r, u);
    omega_r = rk4(omega_dot, _omega_r, t, h, 1, _i_r);
    t = t + h;
    //Output
    printf("%11.8f %11.8f %11.8f %11.8f %11.8f\n",t, i_e, i_r, omega_e, omega_r);
  }
}
