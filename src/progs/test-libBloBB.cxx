/** \file      torpy.cxx
    \brief     Source for binary executable for torpy.
    \author    Jason Torpy, Doug Hague
    \date      11.10.2013
    \copyright See License.txt
*/
#include "Torpy/Common.hh"
#include "Torpy/TimeStamp.hh"
#include "Torpy/Math.hh"
#include "Torpy/Random.hh"

// usings
using namespace Torpy;

//_____________________________________________________________________________
//! print usage to stream
void PrintUsage(ostream& os)
{
  os << endl;
  os << "Usage: test-libBloBB" << endl;
  os << "Example: ./bin/test-libBloBB" << endl;
}

//_____________________________________________________________________________
/** Calculate the frequency of prime numbers less than n. 
    This method is used as a litmus test for bench-marking.
    Taken from <a href="http://www.cplusplus.com/reference/ctime/clock/">ctime/clock</a>.
*/
unsigned int frequency_of_primes(unsigned int n) 
{
  unsigned int i,j;
  unsigned int freq = n-1;
  for(i=2; i<=n; ++i) for (j=Math::Sqrt(i);j>1;--j) if (i%j==0) {--freq; break;}
  return freq;
}

//_____________________________________________________________________________
//! main method testing the CipCurlData class.
int main(int /*argc*/, char** /*argv*/)
{
  // --------------------------------------------
  // Start time-stamp
  TimeStamp startTime;
  clog << endl;
  clog << "*****************************************************************" << endl;
  clog << "It's " << startTime.asDescription() << endl;
  clog << "*****************************************************************" << endl;

  // --------------------------------------------
  // Random
  clog << endl;
  clog << "*****************************************************************" << endl;
  clog << "Testing Random ... " << endl;

  // this seeds a random number generator with the current time
  // every time you run this program you will get different output
  Random r0;
  clog << "r0.rndm()  = " << r0.rndm() << endl;
  clog << "r0.rndm()  = " << r0.rndm() << endl;

  // this seeds a _different_ random number generator with the number 42
  // every(!) time you run this program you will get exaclty he same output:
  // r42.rndm() = 0.0334699
  // r42.rndm() = 0.329964
  // r42.rndm() = 0.690636
  // r42.rndm() = 0.422487
  Random r42(42);
  clog << "r42.rndm() = " << r42.rndm() << endl;
  clog << "r42.rndm() = " << r42.rndm() << endl;
  clog << "r42.rndm() = " << r42.rndm() << endl;
  clog << "r42.rndm() = " << r42.rndm() << endl;

  // If I make a new instance of our cool home-brew random number helper,
  // with the _same_seed_, i will get the same answers 
  // r42_.rndm() = 0.0334699
  // r42_.rndm() = 0.329964
  // r42_.rndm() = 0.690636
  // r42_.rndm() = 0.422487
  Random r42_2(42);
  clog << "r42_2.rndm() = " << r42.rndm() << endl;
  clog << "r42_2.rndm() = " << r42.rndm() << endl;
  clog << "r42_2.rndm() = " << r42.rndm() << endl;
  clog << "r42_2.rndm() = " << r42.rndm() << endl;

  // Now lets do something that takes a bit of time
  // so that clock time will pass and the default constructor
  // of the Random class will use a different seed value (time)
  const unsigned int maxTestPrime = 1000000;
  unsigned int freqTestPrime = frequency_of_primes(maxTestPrime);

  // this seeds a random number generator with the current time
  // every time you run this program you will get different output
  // _and_ it will be different from r0
  Random r01;
  clog << "r01.rndm() = " << r01.rndm() << endl;
  clog << "r01.rndm() = " << r01.rndm() << endl;

  // now let's make two default instances within a second
  Random ra,rb;
  // they are very likely to give the same exact sequence of 
  // random numbers as r01 above
  clog << "ra.rndm() = " << ra.rndm() << endl;
  clog << "rb.rndm() = " << rb.rndm() << endl;
  

  // Since the Random generator on the interval (0,1] is working as advertized
  // and the code to generate random ariates of other distributions
  // is _thoroughly_ tested (elsewhere), I conclude that there is no bug in Random

  // --------------------------------------------
  // clean & return
  return 0;
}

