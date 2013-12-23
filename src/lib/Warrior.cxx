/** \file      src/lib/Warrior.cxx 
    \brief     Source for Warrior 
    \author    Jason Torpy, Doug Hague
    \date      24.07.2013
    \copyright See License.txt
*/
#include "Torpy/Warrior.hh"  // this class

namespace Torpy {

//_____________________________________________________________________________
/** Default constructor. */
Warrior::Warrior(const char* name, const char* title)
  : Named("Warrior", name, title),
    mAttribs(),
    mDisability(),
    mRandom()
{}

//_____________________________________________________________________________
/** Copy constructor. */
Warrior::Warrior(const Warrior& other, const char* newName)
  : Named(other,newName), 
    mAttribs(other.mAttribs),
    mDisability(other.mDisability),
    mRandom(other.mRandom)
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
  mAttribs    = rhs.mAttribs;
  mDisability = rhs.mDisability;
  mRandom     = rhs.mRandom;
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
  mRandom.clear();
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
  // prowess
  double ourProwess   = mRandom.gaussian(prowess().value(), prowess().error());
  double otherProwess = mRandom.gaussian(other.prowess().value(), other.prowess().error());
  if(ourProwess > otherProwess) return 1;
  else if(ourProwess < otherProwess) return -1;
  else return 0;
}
    
//_____________________________________________________________________________
/** establish fight-or-flight; decided whether the warrior will attack or defend.
    \return result true or false.
*/
bool Warrior::forf()
{
  // --------------------------------------------
  // assess level of disability and apply to personality to determine willingness to attack.
  double cur_dis = stun().value()+disarm().value()+fallen().value();
  double thisForF = mRandom.gaussian(personality().value(), personality().error())-(cur_dis*20.);

  // Jason: Be careful, the function signature was expecting you to return a double,
  // but you're returning a boolean. 
  // fixed, but this could have lead to undefined behavior.
  if(thisForF > 55.) return true; // 55 will split.
  else return false;
}
    
//_____________________________________________________________________________
/** determine quality of attack action.
    \return result quantity.
*/
double Warrior::swing()
{
  // --------------------------------------------
  // use attributes including fatigue and disabilities to determine quality of attack
  // triple prowess + agility and intel less fatigue.
  double swingQual = mRandom.gaussian(prowess().value(), prowess().error())*3 + 
                     mRandom.gaussian(agility().value(), agility().error()) + 
                     mRandom.gaussian(intelligence().value(), intelligence().error()) - 
                     fatigue().value(); 
  return swingQual;
}

//_____________________________________________________________________________
/** ... need to bring in a number to decrement by and a warrior to use it ... 
    \return some kind of double
*/
double Warrior::recover() // 
{
    // --------------------------------------------
    // change attribute values based on input.
    return 3.;
}
    
    
} // end namespace Torpy

