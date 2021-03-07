#include "function.h"
#include "algorithm"
#include <QMessageBox>


double ParabolicFunction(double parameterSecondDegree, double parameterFirstDegree, double parameterZeroDegree, double x)
{

   return  (parameterSecondDegree * pow(x, 2) + parameterFirstDegree * x + parameterZeroDegree);
}

double PereodicFunction(double parameterSin, double parameterCos, double parameterX,  double x)
{
    return (parameterSin * sin(x) + parameterCos * cos( parameterX * x ));
}

double LogarithmicFunction(double parameterLogarithm, double parameterX, double x)
{

    return parameterLogarithm * log10(parameterX * x);
}

double InversePeriodicFunction(double parameterNumerator, double denominator, double x)
{

    return parameterNumerator / (sin(pow(x,2)) * denominator);
}



double calculation(double (*foo)(double first, double second, double third, double x), double A, double B, double C,
                 QVector<double>& y, QVector<double>& x)
{

    for(int i = 0; i < x.size(); ++i)
    {
        y[i] = foo(A, B, C, x[i]);

    }
    double max_Y = *std::max_element(y.begin(), y.end());

   return max_Y;

}

double calculation(double (*foo)(double first, double second, double x), double A, double B,
                 QVector<double>& y, QVector<double>& x)
{

    for(int i = 0; i < x.size(); ++i)
    {
        y[i] = foo(A, B, x[i]);
    }
    double max_Y = *std::max_element(y.begin(), y.end());

    return max_Y;
}
