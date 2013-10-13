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
    mProwess("prowess","Prowess", 0., 0., 0. ,100.),
    mAgility("agility","Agility", 0., 0., 0. ,100.),
    mIntelligence("intelligence","Intelligence", 0., 0., 0. ,100.),
    mPersonality("personality","Personality", 0., 0., 0. ,100.),
    mHealth("health","Health", 0., 0., 0. ,100.)
{}

//_____________________________________________________________________________
/** Copy constructor. */
Warrior::Warrior(const Warrior& other, const char* newName)
  : Named(other,newName), 
    mProwess(other.mProwess),
    mAgility(other.mAgility),
    mIntelligence(other.mIntelligence),
    mPersonality(other.mPersonality),
    mHealth(other.mHealth)
{
  if(newName && strlen(newName)!=0) setName(newName);
}

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
  mProwess      = rhs.mProwess;
  mAgility      = rhs.mAgility;
  mIntelligence = rhs.mIntelligence;
  mPersonality  = rhs.mPersonality;
  mHealth       = rhs.mHealth;
  return *this;
}

//_____________________________________________________________________________
/** Equivalence to "zero". 
    Checks is all members are zero.
*/
bool Warrior::isEmpty() const
{
  return (mProwess.isEmpty() &&
	  mAgility.isEmpty() &&
	  mIntelligence.isEmpty() &&
	  mPersonality.isEmpty() &&
	  mHealth.isEmpty());
}

//_____________________________________________________________________________
/** Set all values to zero. */
void Warrior::clear()
{
  mProwess.clear();
  mAgility.clear();
  mIntelligence.clear();
  mPersonality.clear();
  mHealth.clear(); 
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
  return (mProwess      == w->prowess() &&
	  mAgility      == w->agility() &&
	  mIntelligence == w->intelligence() &&
	  mPersonality  == w->Personality() &&
	  mHealth       == w->health());
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
  double ourProwess   = random.gaussian(mProwess.value(), mProwess.error());
  double otherProwess = random.gaussian(other.prowess().value(), other.prowess().error());
  if(ourProwess > otherProwess) return 1;
  else if(ourProwess < otherProwess) return -1;
  else return 0;
}

} // end namespace Torpy

