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
/** This warrior determines its fight action.
 This breaks down to basic attack or defense.
 \return true or false.
 */
bool Warrior::forf()
{
    // --------------------------------------------
    // initialize random number generator
    Random random;
    
    // --------------------------------------------
    // attack based on personality and personal status, only for this warrior.
    double ourForF   = random.gaussian(50., prowess().error())+personality().value(); // should be a random number from 1-100 minus a personality value which is also 1-100.
    int cur_dis = stun().value()+disarm().value()+fallen().value(); // may need to initialize variable, and translate to double.
    ourForF = ourForF - 20.*cur_dis; // reduce likelihood of attack for each disability
    if(ourForF > 50) return true; // true = attacking
    else return false; // false = defending
}

//_____________________________________________________________________________
/** This warrior takes a swing or other attack action.
 This provides basic attack quality to be compared against opponent(s).
 \return result attack quality.
 */

double Warrior::swing()
{
    // --------------------------------------------
    // initialize random number generator
    Random random;
    
    // --------------------------------------------
    // prowess
    double swingQual   = random.gaussian(prowess().value(), prowess().error())*3+agility().value()+intelligence().value()+(100.-fatigue().value()); // triple prowess + agility and intel less fatigue.
    return swingQual;
}
    
} // end namespace Torpy

