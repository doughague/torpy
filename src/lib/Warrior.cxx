/** \file      src/lib/Warrior.cxx 
    \brief     Source for Warrior 
    \author    Jason Torpy, Doug Hague
    \date      24.07.2013
    \copyright See License.txt
*/
#include "Torpy/Random.hh"   // random numbers
#include "Torpy/Warrior.hh"  // this class

namespace Torpy {

//_____________________________________________________________________________
/** Default constructor. */
Warrior::Warrior(const char* name, const char* title)
  : Named("Warrior", name, title),
    mAttribs(),
    mDisability()
{}

//_____________________________________________________________________________
/** Copy constructor. */
Warrior::Warrior(const Warrior& other, const char* newName)
  : Named(other,newName), 
    mAttribs(other.mAttribs),
    mDisability(other.mDisability)
{}

//_____________________________________________________________________________
/** Cloner. */
AbsObject* Warrior::clone(const char* newName) const
{
  return new Warrior(*this, newName);
}

//_____________________________________________________________________________
/** Assignment operator. */
Warrior& Warrior::operator=(const Warrior& rhs)
{
  Named::operator=(rhs);
  mAttribs = rhs.mAttribs;
  mDisability = rhs.mDisability;
  return *this;
}

//_____________________________________________________________________________
/** Equivalence to "zero". 
    Checks is all members are zero.
*/
bool Warrior::isEmpty() const
{
  return (mAttribs.isEmpty() && 
	  mDisability.isEmpty());
}

//_____________________________________________________________________________
/** Set all values to zero. */
void Warrior::clear()
{
  mAttribs.clear();
  mDisability.clear();
}

//_____________________________________________________________________________
/** Equivalence. */
bool Warrior::isEqual(const AbsObject& other) const
{
  if(isSame(other)) return true;

  // check cast
  Warrior* w = (Warrior*)(&other);
  if(!w) return false;

  // check members
  return (mAttribs == w->attribs() &&
	  mDisability == w->disability());
}

//_____________________________________________________________________________
/** This warrior fights other warrior. 
    This is just a simple example for now.
    \return result code.
*/
int Warrior::fight(Warrior& other)
{
  // --------------------------------------------
  // initialize random number generator
  Random random;

  // --------------------------------------------
  // prowess
  double ourProwess   = random.gaussian(prowess().value(), prowess().error());
  double otherProwess = random.gaussian(other.prowess().value(), other.prowess().error());
  if(ourProwess > otherProwess) return 1;
  else if(ourProwess < otherProwess) return -1;
  else return 0;
}

} // end namespace Torpy

