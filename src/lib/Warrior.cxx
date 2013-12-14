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
    
//_____________________________________________________________________________
/** establish fight-or-flight; decided whether the warrior will attack or defend.
 \return result true or false.
 */
double Warrior::forf()
{
    // --------------------------------------------
    // initialize random number generator.
    Random random;

    // --------------------------------------------
    // assess level of disability and apply to personality to determine willingness to attack.
    double cur_dis = stun().value()+disarm().value()+fallen().value();
    double thisForF = random.gaussian(personality().value(), personality().error())-(cur_dis*20.);
    
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
    // initialize random number generator.
    Random random;
    
    // --------------------------------------------
    // use attributes including fatigue and disabilities to determine quality of attack
    double swingQual   = random.gaussian(prowess().value(), prowess().error())*3+random.gaussian(agility().value(), agility().error())+random.gaussian(intelligence().value(), intelligence().error())-fatigue().value(); // triple prowess + agility and intel less fatigue.
    return swingQual;
}

double Warrior::recover() // need to bring in a number to decrement by and a warrior to use it.
{
    // --------------------------------------------
    // change attribute values based on input.
    return 3.;

}
    
    
} // end namespace Torpy

