#ifndef FUNCTION_H
#define FUNCTION_H
#include <cmath>
#include <functional>
#include <QVector>
#include <QDebug>

//Типы функции
double ParabolicFunction(double parameterSecondDegree, double parameterFirstDegree, double parameterZeroDegree, double x);

double PereodicFunction(double parameterSin, double parameterCos, double parameterX,  double x);

double LogarithmicFunction(double parameterLogarithm, double parameterX, double x);

double InversePeriodicFunction(double parameterNumerator, double denominator, double x);



double calculation(double (*foo)(double first, double second, double third, double x), double A, double B, double C,
                 QVector<double>& y, QVector<double>& x);

double calculation(double (*foo)(double first, double second, double x), double A, double B,
                 QVector<double>& y, QVector<double>& x);
#endif // FUNCTION_H
