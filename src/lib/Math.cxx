/** \file      Math.cxx 
    \brief     Source for math functions.
    \author    Doug Hague
    \date      24.07.2013
    \copyright See License.txt
    \note      Most of this code was copied dirrectly from the 
               appropriate ROOT::TMath sources.
*/
#include <cmath>          // C math library
#include <limits>         // C++ limits of typed numbers
#include "Torpy/Math.hh"  // these methods

namespace Torpy {

namespace Math {

// numerical limits
static const double kInfinity = std::numeric_limits<double>::infinity();
static const double kEpsilon  = std::numeric_limits<double>::epsilon();

//______________________________________________________________________________
/** Machine \f$ \infty \f$ = std::numeric_limits<double>::infinity(). */
double Infinity()
{
  return kInfinity;
}

//______________________________________________________________________________
/** Machine epsilon \f$ 1/\infty \f$. */
double Epsilon()
{
  return kEpsilon;
}

//______________________________________________________________________________
/** Base of the natural logarithm: \f$e\f$. */
double E()
{
  return 2.71828182845904509;
}

//______________________________________________________________________________
/** The natural logarithm of 10: \f$\ln{10}\f$. */
double Ln10()
{
  return 2.30258509299404590;
}

//______________________________________________________________________________
/** The common logarithm of base of the natural logarithm: \f$\log{e}\f$. */
double LogE()
{
  return 4.34294481903251817e-01;
}

//______________________________________________________________________________
/** Pi: \f$\pi\f$. */
double Pi()
{
  return 3.14159265358979323846;
}

//______________________________________________________________________________
/** \f$ \sqrt{2\pi} \f$. */
double Sqrt2Pi()
{
  return 2.50662827463100024;
}

//______________________________________________________________________________
/** \f$ \frac{1}{\sqrt{2\pi}} \f$. */
double InvSqrt2Pi()
{
  return 0.398942280401432703;
}

//______________________________________________________________________________
/** Conversion factor for converting degrees to radians: \f$ \pi/180 \f$
    One degree is equivalent to PI/180 radians. 
*/
double DegToRad()
{
  return 1.74532925199432955e-02;
}

//______________________________________________________________________________
/** Conversion factor for converting radians to degrees: \f$ 180/\pi \f$
    One radian is equivalent to 180/PI degrees. 
*/
double RadToDeg()
{
  return 5.72957795130823229e+01;
}

//______________________________________________________________________________
/** \f$ \sqrt{2} \f$. */
double Sqrt2()
{
  return 1.41421356237309515;
}

//______________________________________________________________________________
/** \f$ 1/\sqrt{2} \f$. */
double InvSqrt2()
{
  return 0.707106781186547462;
}

//______________________________________________________________________________
/** Convert input degrees to radians: \f$  degrees \times \pi / 180 \f$. */
double ToRadians(double degrees)
{
  return degrees * DegToRad();
}

//______________________________________________________________________________
/** Convert input radians to degrees: \f$  radians \times 180 / \pi \f$. */
double ToDegrees(double radians)
{
  return radians * RadToDeg();
}

//______________________________________________________________________________
/** The cosine function: \f$ \cos{x} \f$. */
double Cos(double radians)
{
  return std::cos(radians);
}

//______________________________________________________________________________
/** The sine function: \f$ \sin{x} \f$. */
double Sin(double radians)
{
  return std::sin(radians);
}

//______________________________________________________________________________
/** The tangent function: \f$ \tan{x} \f$. */
double Tan(double radians)
{
  return std::tan(radians);
}

//______________________________________________________________________________
/** The principal value of the arc cosine of x, expressed in radians:
    \f$ \cos^{-1}{x} \f$. 
*/
double ACos(double x)
{
  return std::acos(x);
}

//______________________________________________________________________________
/** The principal value of the arc sine of x, expressed in radians:
    \f$ \sin^{-1}{x} \f$. 
*/
double ASin(double x)
{
  return std::asin(x);
}

//______________________________________________________________________________
/** The principal value of the arc tangent of x, expressed in radians:
    \f$ \tan^{-1}{x} \f$. 
*/
double ATan(double x)
{
  return std::atan(x);
}

//______________________________________________________________________________
/** Returns the principal value of the arc tangent of y/x, expressed in radians:
    \f$ \tan^{-1}{y/x} \f$. 
*/
double ATan2(double y, double x)
{
  return std::atan2(y,x);
}

//______________________________________________________________________________
/** The exponential function: \f$ e^{x} \f$. */
double Exp(double x)
{
  return std::exp(x);
}

//______________________________________________________________________________
/** The natural logarithm function: \f$ \ln{x} \f$. */
double Ln(double x)
{
  return std::log(x);
}

//______________________________________________________________________________
/** Ten raised to the power exponent: \f$ 10^{a} \f$. */
double Exp10(double exponent)
{
  return std::pow(10., exponent);
}

//______________________________________________________________________________
/** The common logarithm function: \f$ \log{x} \f$. */
double Log(double x)
{
  return std::log10(x);
}

//______________________________________________________________________________
/** The base raised to the power exponent: \f$ x^{a} \f$. */
double Pow(double base, double exponent)
{
  return std::pow(base, exponent);
}

//______________________________________________________________________________
/** The square-root function: \f$ \sqrt{x} \f$. */
double Sqrt(double x)
{
  // if(x<0.){
  //   loutE(InputArguments) << "Math::Sqrt: Negative input argument." << endl;
  //   return 0.;
  // }
  // else return std::sqrt(x);
  return std::sqrt(x);
}

//______________________________________________________________________________
/** Returns the floating-point remainder of numer/denom (rounded towards zero).
    \return numerator - tquot * denominator 
    Where tquot is the truncated (i.e., rounded towards zero) result of: numer/denom. 
*/
double Remainder(double numerator, double denominator)
{
  return std::fmod(numerator, denominator);
}

//______________________________________________________________________________
/** Breaks x into an integral and a fractional part.
    The integer part is stored in the object pointed by intpart, and the fractional part is returned by the function.
    Both parts have the same sign as x. 
*/
double FracPart(double x, double& intPart)
{
  return std::modf(x, &intPart);
}

//______________________________________________________________________________
/** The absolute value: \f$ |x| \f$. */
double Abs(double x)
{
  return std::abs(x);
}

//______________________________________________________________________________
/** Rounds x upward, returning the smallest integral value that is not less than x: 
    \f$ \lceil x \rceil \f$. */
double Ceil(double x)
{
  return std::ceil(x);
}

//______________________________________________________________________________
/** Rounds x downward, returning the largest integral value that is not greater than x: 
    \f$ \lfloor x \rfloor \f$. */
double Floor(double x)
{
  return std::floor(x);
}

//______________________________________________________________________________
/** Returns the smallest of a and b. If both are equivalent, a is returned. */
double Min(double a, double b)
{
  return fmin(a, b);
}

//______________________________________________________________________________
/** Returns the largest of a and b. If both are equivalent, a is returned. */
double Max(double a, double b)
{
  return fmax(a, b);
}

//______________________________________________________________________________
/** The error function.
    \f[ \frac{1}{\sqrt{\pi}} \int_{0}^{x} e^{-t^2} dt \f]
*/
double Erf(double x)
{
  return 1. - Erfc(x);
}

//______________________________________________________________________________
/** The complementary error function.
    \f[ \frac{1}{\sqrt{\pi}} \int_{x}^{\infty} e^{-t^2} dt \f]
  
    \author Nve 14-nov-1998 UU-SAP Utrecht
*/
double Erfc(double x)
{
  // The parameters of the Chebyshev fit
  static const double erfca1 = -1.26551223;
  static const double erfca2 = 1.00002368;
  static const double erfca3 =  0.37409196;
  static const double erfca4 = 0.09678418;
  static const double erfca5 = -0.18628806;
  static const double erfca6 = 0.27886807;
  static const double erfca7 = -1.13520398;
  static const double erfca8 = 1.48851587;
  static const double erfca9 = -0.82215223;
  static const double erfca10 = 0.17087277;

  double v = 1;       // The return value
  double z = Abs(x);
  if(z <= 0) return v; // erfc(0)=1
  double t = 1/(1+0.5*z);
  v = t*exp((-z*z) +erfca1+t*(erfca2+t*(erfca3+t*(erfca4+t*(erfca5+t*(erfca6+t*(erfca7+t*(erfca8+t*(erfca9+t*erfca10)))))))));
  if (x < 0) v = 2-v; // erfc(-x)=2-erfc(x)
  return v;
}

//______________________________________________________________________________
/** Calculates a value of a polynomial of the form:
    \f$ a_{0}x^{N} + a_{1}x^{N-1} + ... + a_{N} \f$
  
    \author Nve 14-nov-1998 UU-SAP Utrecht
*/
double PolynomialEval(double x, const double* a, unsigned int N)
{
   if (N==0) return a[0];
   else{
     double pom = a[0];
     for(unsigned int i=1; i <= N; i++)
       pom = pom *x + a[i];
     return pom;
   }
}

//______________________________________________________________________________
/** Calculates a value of a polynomial of the form:
    \f$ x^{N} + a_{0}x^{N-1} + ... + a_{N-1} \f$
  
    \author Nve 14-nov-1998 UU-SAP Utrecht
*/
double PolynomialEval1(double x, const double* a, unsigned int N)
{
   if (N==0) return a[0];
   else{
     double pom = x + a[0];
     for(unsigned int i=1; i < N; i++)
       pom = pom *x + a[i];
     return pom;
   }
}

//______________________________________________________________________________
/** The factorial function: \f$ x! \f$. */
double Factorial(unsigned int n)
{
  if(n == 0) return 1.;
  double x(1.);
  unsigned int b(0);
  do {
    b++;
    x *= b;
  } while (b != n);
  return x;
}

// local numbers
static const double kBig    = 4.503599627370496e15;
static const double kBiginv = 2.22044604925031308085e-16;
static const double kLS2PI  = 0.91893853320467274178;
static const double kMACHEP = 1.11022302462515654042363166809e-16;
static const double kMAXLOG = 709.782712893383973096206318587;
static const double kMAXLGM = 2.556348e305;

//______________________________________________________________________________
/** The Gamma function. 
    \f[ \Gamma(x) = \int_{0}^{\infty} e^{-t} t^{x-1} dt \f]
*/
double Gamma(double x)
{
  return exp( LnGamma(x) );
}

//______________________________________________________________________________
/** (Natural) Logarithm of gamma function.
  
    \author Nve 14-nov-1998 UU-SAP Utrecht
*/
double LnGamma(double x)
{

  // lngA[]: Stirling's formula expansion of log gamma
  static const double lngA[] = {
    8.11614167470508450300E-4,
    -5.95061904284301438324E-4,
    7.93650340457716943945E-4,
    -2.77777777730099687205E-3,
    8.33333333333331927722E-2
  };

  // lngB[], lngC[]: log gamma function between 2 and 3
  static const double lngB[] = {
    -1.37825152569120859100E3,
    -3.88016315134637840924E4,
    -3.31612992738871184744E5,
    -1.16237097492762307383E6,
    -1.72173700820839662146E6,
    -8.53555664245765465627E5
  };
  static const double lngC[] = {
    -3.51815701436523470549E2,
    -1.70642106651881159223E4,
    -2.20528590553854454839E5,
    -1.13933444367982507207E6,
    -2.53252307177582951285E6,
    -2.01889141433532773231E6
  };

  //
  // The Method
  //
  double p, q, u, w, z;
  int i;
  int sgngam = 1;

  if (x >= kInfinity)
    return(kInfinity);

  if( x < -34.0 )
    {
      q = -x;
      w = LnGamma(q); 
      p = Floor(q);
      if( p==q )
	return (kInfinity);
      i = (int) p;
      if( (i & 1) == 0 )
	sgngam = -1;
      else
	sgngam = 1;
      z = q - p;
      if( z > 0.5 )
	{
	  p += 1.0;
	  z = p - q;
	}
      z = q * Sin( Pi() * z );
      if( z == 0 )
	return (kInfinity);
      /*	z = Ln(Pi()) - Ln( z ) - w;*/
      z = Ln(Pi()) - Ln( z ) - w;
      return( z );
    }

  if( x < 13.0 )
    {
      z = 1.0;
      p = 0.0;
      u = x;
      while( u >= 3.0 )
	{
	  p -= 1.0;
	  u = x + p;
	  z *= u;
	}
      while( u < 2.0 )
	{
	  if( u == 0 )
            return (kInfinity);
	  z /= u;
	  p += 1.0;
	  u = x + p;
	}
      if( z < 0.0 )
	{
	  sgngam = -1;
	  z = -z;
	}
      else
	sgngam = 1;
      if( u == 2.0 )
	return( Ln(z) );
      p -= 2.0;
      x = x + p;
      p = x * PolynomialEval(x, lngB, 5 ) / PolynomialEval1( x, lngC, 6);
      return( Ln(z) + p );
    }

  if( x > kMAXLGM )
    return( sgngam * kInfinity );

  q = ( x - 0.5 ) * Ln(x) - x + kLS2PI;
  if( x > 1.0e8 )
    return( q );

  p = 1.0/(x*x);
  if( x >= 1000.0 )
    q += ((   7.9365079365079365079365e-4 * p
	      - 2.7777777777777777777778e-3) *p
	  + 0.0833333333333333333333) / x;
  else
    q += PolynomialEval( p, lngA, 4 ) / x;
  return( q );
}

//______________________________________________________________________________
/** The "normalized" lower incomplete gamma function.

    \f[ \gamma(a,x) = \frac{1}{\Gamma(a)} \int_{0}^{x} e^{-t} t^{a-1} dt \f]

    It is normalized such that \f$ \gamma(a,x) = 1 - \Gamma(a,x) \f$.
    
    \author Nve 14-nov-1998 UU-SAP Utrecht
*/
double LowerIncGamma( double a, double x )
{
  double ans, ax, c, r;

  // LM: for negative values returns 1.0 instead of zero
  // This is correct if a is a negative integer since Gamma(-n) = +/- inf
  if (a <= 0)  return 1.0;  

  if (x <= 0)  return 0.0;

  if( (x > 1.0) && (x > a ) )
    return( 1.0 - UpperIncGamma(a,x) );

  /* Compute  x**a * exp(-x) / gamma(a)  */
  ax = a * Ln(x) - x - LnGamma(a);
  if( ax < -kMAXLOG )
    return( 0.0 );

  ax = exp(ax);

  /* power series */
  r = a;
  c = 1.0;
  ans = 1.0;

  do
    {
      r += 1.0;
      c *= x/r;
      ans += c;
    }
  while( c/ans > kMACHEP );

  return( ans * ax/a );
}

//______________________________________________________________________________
/** The "normalized" upper incomplete gamma function.

    \f[ \Gamma(a,x) = \frac{1}{\Gamma(a)} \int_{x}^{\infty} e^{-t} t^{a-1} dt \f]

    It is normalized such that \f$ \Gamma(a,x) = 1 - \gamma(a,x) \f$.

    In this implementation both arguments must be positive.
    The integral is evaluated by either a power series or
    continued fraction expansion, depending on the relative
    values of a and x.
    
    \author Nve 14-nov-1998 UU-SAP Utrecht
*/
double UpperIncGamma(double a, double x)
{
  double ans, ax, c, yc, r, t, y, z;
  double pk, pkm1, pkm2, qk, qkm1, qkm2;

  // LM: for negative values returns 0.0
  // This is correct if a is a negative integer since Gamma(-n) = +/- inf
  if (a <= 0)  return 0.0;  

  if (x <= 0) return 1.0;

  if( (x < 1.0) || (x < a) )
    return( 1.0 - LowerIncGamma(a,x) );

  ax = a * Ln(x) - x - LnGamma(a);
  if( ax < -kMAXLOG )
    return( 0.0 );

  ax = exp(ax);

  /* continued fraction */
  y = 1.0 - a;
  z = x + y + 1.0;
  c = 0.0;
  pkm2 = 1.0;
  qkm2 = x;
  pkm1 = x + 1.0;
  qkm1 = z * x;
  ans = pkm1/qkm1;

  do
    { 
      c += 1.0;
      y += 1.0;
      z += 2.0;
      yc = y * c;
      pk = pkm1 * z  -  pkm2 * yc;
      qk = qkm1 * z  -  qkm2 * yc;
      if(qk)
	{
	  r = pk/qk;
	  t = Abs( (ans - r)/r );
	  ans = r;
	}
      else
	t = 1.0;
      pkm2 = pkm1;
      pkm1 = pk;
      qkm2 = qkm1;
      qkm1 = qk;
      if( Abs(pk) > kBig )
	{
	  pkm2 *= kBiginv;
	  pkm1 *= kBiginv;
	  qkm2 *= kBiginv;
	  qkm1 *= kBiginv;
	}
    }
  while( t > kMACHEP );

  return( ans * ax );  
}

//______________________________________________________________________________
/** The Chi-squared cummulative distribution funcion. */
double Chi2Cdf(double x, double r, double x0)
{
  return 1. - Chi2Survival(x, r, x0);
}

//______________________________________________________________________________
/** The Chi-squared survival funcion: \f$1-F(x)\f$ where \f$F(x)\f$ 
    is the CDF of the Chi-squared distribution.
    
    \author Nve 14-nov-1998 UU-SAP Utrecht
*/
double Chi2Survival(double x, double r, double x0)
{
  return LowerIncGamma(0.5*r, 0.5*(x-x0));
}

//______________________________________________________________________________
/** Computation of the probability for a certain Chi-squared (chi2)
    and number of degrees of freedom (ndf).
   
    P(chi2,ndf) represents the probability that the observed Chi-squared
    for a correct model should be less than the value chi2.
   
    The returned probability corresponds to Chi2Prob() = 1-P(chi2,ndf),
    which denotes the probability that an observed Chi-squared exceeds
    the value chi2 by chance, even for a correct model.

    \note Calculations are based on the incomplete gamma function P(a,x),
    where a=ndf/2 and x=chi2/2.
   
    \author NvE 14-nov-1998 UU-SAP Utrecht
*/
double Chi2Prob(double chi2, unsigned int ndf)
{
  // Set CL to zero in case ndf <= 0
  if(ndf <= 0) return 0.;
  if(chi2 <= 0.){
    if(chi2 < 0.) return 0.;
    else          return 1.;
  }
  return Chi2Survival(chi2, ndf); 
}

} // end namespace Math

} // end namespace Torpy

