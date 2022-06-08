#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

const double Lm=0.0;
const double Rm=0.2;
const double Km=2.0e-3;
const double Jm=6.0e-3;
const double Cq=1.0e-8;
const double Dm=0.0;


//Equation of current
//Lm di/dt + Rm i + Km omega = u
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
//value[0]:i
double omega_dot(double omega, double t, double *value)
{
  double i=value[0];
  double TL=Cq * omega * omega * omega;
  return (Km * i - Dm * omega - TL)/Jm;

}

double euler(double (*dxdt)(double, double, double*), double x, double t, double h, int n, ...)
{
  va_list args;
  double *value;
  double k1;

  value=(double*)malloc(sizeof(double) * n);
  va_start(args , n);
  for(int i=0;i<n;i++)
  {
    value[i]=va_arg(args, double);
  }
  va_end(args);
  
  k1 = h * dxdt(x, t, value);

  free(value);
  
  return x+k1;
}

void main(void)
{
}
