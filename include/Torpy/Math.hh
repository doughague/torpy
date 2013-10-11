/** \file      Math.hh 
    \brief     Mathematical includes and usings header.
    \author    Doug Hague
    \date      29.07.2013
    \copyright See License.txt
*/
#ifndef TP_MATH_HH
#define TP_MATH_HH

namespace Torpy {

namespace Math {

// numerical limits 
double Infinity();
double Epsilon();

// numerical constants 
double E();
double Ln10();
double LogE();
double Pi();
double Sqrt2Pi();
double InvSqrt2Pi();
double DegToRad();
double RadToDeg();
double Sqrt2();
double InvSqrt2();

// trigonometric functions
double ToRadians(double degrees);
double ToDegrees(double radians);
double Cos(double radians);
double Sin(double radians);
double Tan(double radians);
double ACos(double x);
double ASin(double x);
double ATan(double x);
double ATan2(double y, double x);

// exponential functions
double Exp(double x);
double Ln(double x);
double Exp10(double x);
double Log(double x);

// power functions
double Pow(double base, double exponent);
double Sqrt(double x);

// rounding functions
double Remainder(double numerator, double denominator);
double FracPart(double x, double& intPart);
double Abs(double x);
double Ceil(double x);
double Floor(double x);
double Min(double a, double b);
double Max(double a, double b);

// error functions
double Erf(double x);
double Erfc(double x);

// polynomial functions
double PolynomialEval(double x, const double* a, unsigned int N);
double PolynomialEval1(double x, const double* a, unsigned int N);

// gamma functions
double Factorial(unsigned int n);
double Gamma(double x);
double LnGamma(double x);
double LowerIncGamma(double a, double x);
double UpperIncGamma(double a, double x);

// chi-squared functions
double Chi2Cdf(double x, double r, double x0 = 0.);
double Chi2Survival(double x, double r, double x0 = 0.);
double Chi2Prob(double chi2, unsigned int ndf);

} // end namespace Math

} // end namespace Torpy


#endif // end TP_MATH_HH
