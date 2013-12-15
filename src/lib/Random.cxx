/** \file      src/lib/Random.cxx 
    \brief     Source for Random class
    \author    Doug Hague
    \date      04.10.2013
    \copyright See License.txt
*/
#include <ctime>            // time
#include "Torpy/Math.hh"    // math library
#include "Torpy/Random.hh"  // this class

namespace Torpy {

    // tout for test purposes
    static const string kPrefix = "[BloBB]";
#define tout cout << kPrefix.c_str() << ">  "

    
//_____________________________________________________________________________
/** The maximum integer returned by the std::rand function.

    The RAND_MAX macro expands to an integral constant expression whose value is the 
    maximum value returned by the std::rand function.
    This value is library-dependent, but is guaranteed to be at least 32767 
    on any standard library implementation.
 */
const unsigned int Random::mRandMax = RAND_MAX;

//_____________________________________________________________________________
/** Default constructor. 
    Default argument, seed = 0, seeds the random number generator to value to local "now" time.
 */
Random::Random(unsigned int seed)
  : AbsObject("Random"),
    mSeed(seed)
{
  setSeed(mSeed);
}

//_____________________________________________________________________________
/** Copy constructor. */
Random::Random(const Random& other)
  : AbsObject(other),
    mSeed(other.mSeed)
{}

//_____________________________________________________________________________
/** Cloner. */
AbsObject* Random::clone(const char* /*newName*/) const
{
  return new Random(*this);
}

//_____________________________________________________________________________
/** Assignment operator. */
Random& Random::operator=(const Random& rhs)
{
  AbsObject::operator=(rhs);
  mSeed = rhs.mSeed;
  return *this;
}

//_____________________________________________________________________________
/** Is this peak empty? */
bool Random::isEmpty() const 
{ 
  return (mSeed == 1); 
}

//_____________________________________________________________________________
/** Clear (zero) the support range(s). */
void Random::clear()
{ 
  setSeed(1);
}

//_____________________________________________________________________________
/** Does this equal other? */
bool Random::isEqual(const AbsObject& other) const
{
  if(isSame(other)) return true;

  // check cast
  Random* r = (Random*)(&other);
  if(!r) return false;

  // check members
  if(mSeed != r->seed()) return false;

  //return
  return true;
}

//_____________________________________________________________________________
/** Get the seed value. */
unsigned int Random::seed() const 
{ 
  return mSeed; 
}

//_____________________________________________________________________________
/** Seed the random number generator.
    Default argument, seed = 0, seeds the random number generator to value to local "now" time.
    If seed is set to 1, the generator is reinitialized to its initial value 
    and produces the same values as before any call to rand or srand.
*/
void Random::setSeed(unsigned int seed)
{
  unsigned int s = seed;
  if(seed == 0) s = time(NULL);
  mSeed = s;
  srand(mSeed);
}


//_____________________________________________________________________________
/** A uniform random floating-point number in the range [0., max]. 
    If max == 0., a maximum of 1. is used.
*/
double Random::rndm(double max) const
{
  if(max == 0.) return double(rand()) / double(mRandMax);
  else return max * double(rand()) / double(mRandMax);
}

//_____________________________________________________________________________
/** A uniform random integer number in the range [0, max-1]. 
    If max == 0., a maximum of mRandMax is used.
*/
unsigned int Random::integer(unsigned int max) const
{
  if(max == 0) return rand();
  else return rand() % max;
}

//_____________________________________________________________________________
/** A uniform random double number in the range [min, max]. */
double Random::uniform(double min, double max) const
{
  return min + rndm()*(max-min);
}

//_____________________________________________________________________________
/** An exponential random variate: \f$ e^{-t/\tau} \f$. */
double Random::exponential(double tau) const
{
  return (-tau * Math::Ln(rndm()));
}

//_____________________________________________________________________________
/** A gaussian random variate with mean and sigma: 
    \f[ \frac{e^{-(t-\mu)^2/\sigma^2}}{\sqrt{2\pi\sigma^{2}}} \f]. 

    This method was taken from <a href="http://root.cern.ch/root/html/src/TRandom.cxx.html">TRandom</a> 
    on 04.10.2013 by Doug Hague and included the following documentation:

    Samples a random number from the Gaussian Distribution 
    with the given mean and sigma.                                                 
    Uses the Acceptance-complement ratio from W. Hoermann and G. Derflinger 
    This is one of the fastest existing method for generating normal random variables. 
    It is a factor 2/3 faster than the polar (Box-Muller) method used in the previous 
    version of TRandom::Gaus. The speed is comparable to the Ziggurat method (from Marsaglia)
    implemented for example in GSL and available in the MathMore library. 
                                                                            
    REFERENCE:  - W. Hoermann and G. Derflinger (1990):                       
    The ACR Method for generating normal random variables,       
    OR Spektrum 12 (1990), 181-185.                             
                                                                            
    Implementation taken from 
    UNURAN (c) 2000  W. Hoermann & J. Leydold, Institut f. Statistik, WU Wien 
*/
double Random::gaussian(double mean, double sigma) const
{
  static const double kC1 = 1.448242853;
  static const double kC2 = 3.307147487;
  static const double kC3 = 1.46754004;
  static const double kD1 = 1.036467755;
  static const double kD2 = 5.295844968;
  static const double kD3 = 3.631288474;
  static const double kHm = 0.483941449;
  static const double kZm = 0.107981933;
  static const double kHp = 4.132731354;
  static const double kZp = 18.52161694;
  static const double kPhln = 0.4515827053;
  static const double kHm1 = 0.516058551;
  static const double kHp1 = 3.132731354;
  static const double kHzm = 0.375959516;
  static const double kHzmp = 0.591923442;
  static const double kAs = 0.8853395638;
  static const double kBs = 0.2452635696;
  static const double kCs = 0.2770276848;
  static const double kB  = 0.5029324303;
  static const double kX0 = 0.4571828819;
  static const double kYm = 0.187308492 ;
  static const double kS  = 0.7270572718 ;
  static const double kT  = 0.03895759111;

  double result;
  double rn,x,y,z;
tout<<"random access==>";//test
  do {
    y = rndm();
      tout<<"y"<<y;//test
    if (y>kHm1) {
      result = kHp*y-kHp1; break; }
  
    else if (y<kZm) {  
      rn = kZp*y-1;tout<<"rna"<<rn;//test
      result = (rn>0) ? (1+rn) : (-1+rn);
      break;
    } 

    else if (y<kHm) {  
        rn = rndm();tout<<"rnb1-"<<rn;//test
        rn = rn-1+rn;tout<<"rnb2-"<<rn;//test
      z = (rn>0) ? 2-rn : -2-rn;
      if ((kC1-y)*(kC3+Math::Abs(z))<kC2) {
	result = z; break; }
      else {  
	x = rn*rn;
	if ((y+kD1)*(kD3+x)<kD2) {
	  result = rn; break; }
	else if (kHzmp-y<Math::Exp(-(z*z+kPhln)/2)) {
	  result = z; break; }
	else if (y+kHzm<Math::Exp(-(x+kPhln)/2)) {
	  result = rn; break; }
      }
    }

    while (1) {
      x = rndm();
      y = kYm * rndm();
      z = kX0 - kS*x - y;
      if (z>0) 
	rn = 2+y/x;
      else {
	x = 1-x;
	y = kYm-y;
	rn = -(2+y/x);
      }
      if ((y-kAs+x)*(kCs+x)+kBs<0) {
	result = rn; break; }
      else if (y<x+kT)
	if (rn*rn<4*(kB-Math::Ln(x))) {
	  result = rn; break; }
    }
  } while(0);
    tout<<mean<<"+"<<sigma<<"*"<<result<<endl;
  return mean + sigma * result;
}

//_____________________________________________________________________________
/** An Poisson random variate: \f$ \mu^{t} e^{-\mu} / t! \f$. */
double Random::poisson(double mean) const
{
  int n;
  if (mean <= 0) return 0;
  if (mean < 25) {
    double expmean = Math::Exp(-mean);
    double pir = 1;
    n = -1;
    while(1) {
      n++;
      pir *= rndm();
      if (pir <= expmean) break;
    }
    return static_cast<double>(n);
  }
  // for large value we use inversion method
  else if (mean < 1E9) {
    double em, t, y;
    double sq, alxm, g;

    sq = Math::Sqrt(2.0*mean);
    alxm = Math::Ln(mean);
    g = mean*alxm - Math::LnGamma(mean + 1.0);

    do {
      do {
	y = Math::Tan(Math::Pi()*rndm());
	em = sq*y + mean;
      } while( em < 0.0 );

      em = Math::Floor(em);
      t = 0.9*(1.0 + y*y)* Math::Exp(em*alxm - Math::LnGamma(em + 1.0) - g);
    } while( rndm() > t );

    return em;

  } else {
    // use Gaussian approximation for very large values
    return gaussian(0,1)*Math::Sqrt(mean) + mean +0.5;
  }
}

//_____________________________________________________________________________
/** An Power-Law random variate: 
    \f[ \frac{\gamma-1}{x_{min}} \left( \frac{x}{x_{min}} \right)^{-\gamma} \f]. 
*/
double Random::powerlaw(double xmin, double gamma) const
{
  if(gamma != 1.0) return xmin * Math::Pow((1.-rndm()), -1./(gamma-1.));
  else return 0.;
}

//_____________________________________________________________________________
/** An Power-Law random variate:
Simple random distribution around a mean, plus or minus given range.
 */
double Random::basic(double mean, int range) const
{
    srand ( (unsigned) time(NULL) );
    tout << "mean-" << mean << ", range-" << range << ", rand-"<< rand() << endl;
    if(range==0) return mean;
    else return mean - range + (rand() % range);
}

    
} // end namespace Torpy
