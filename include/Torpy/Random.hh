/** \file      Random.hh 
    \brief     Header for Random class
    \author    Doug Hague
    \date      04.10.2013
    \copyright See License.txt
*/
#ifndef TP_RANDOM_HH
#define TP_RANDOM_HH

#include "Torpy/AbsObject.hh"  // mother class

namespace Torpy {

/** \class Random
    \brief A random number generator.

    This class currently uses std::rand() which might not 
    be suited for statistical studies.
*/
class Random : public AbsObject {
public:
  Random(unsigned int seed = 0);
  Random(const Random& other);
  virtual AbsObject* clone(const char* /*newName*/) const;
  virtual Random& operator=(const Random& rhs);
  inline virtual ~Random() { }

  virtual bool isEmpty() const;
  virtual void clear();
  virtual bool isEqual(const AbsObject& other) const;

  unsigned int seed() const;
  virtual void setSeed(unsigned int seed = 0);

  // core method
  virtual double rndm(double max = 0.) const;
  virtual unsigned int integer(unsigned int max = 0) const;

  // distributions
  double uniform(double min = 0., double max = 1.) const;
  double exponential(double tau = 1.) const;
  double gaussian(double mean = 0., double sigma = 1.) const;
  double poisson(double mean = 1.) const;
  double powerlaw(double xmin = 1., double gamma = 2.) const;
  double basic(double mean=0.,int range=1.) const; // default
    
private:
  //! Seed for the random number generator
  unsigned int mSeed;
  //! The maximum integer returned by the rand function.
  static const unsigned int mRandMax;
};

} // end namespace Torpy

#endif // TP_RANDOM_HH
