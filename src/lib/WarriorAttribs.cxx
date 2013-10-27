/** \file      src/lib/WarriorAttribs.cxx 
    \brief     Source for WarriorAttribs 
    \author    Jason Torpy, Doug Hague
    \date      24.07.2013
    \copyright See License.txt
*/
#include "Torpy/WarriorAttribs.hh"  // this class

namespace Torpy {

//_____________________________________________________________________________
/** Default constructor. */
WarriorAttribs::WarriorAttribs()
  : Parameters()
{
  // add the specific attributes
  add("prowess","Prowess", 0., 0., 0. ,100.);
  add("agility","Agility", 0., 0., 0. ,100.);
  add("intelligence","Intelligence", 0., 0., 0. ,100.);
  add("personality","Personality", 0., 0., 0. ,100.);
  add("health","Health", 0., 0., 0. ,100.);
}

//_____________________________________________________________________________
/** Copy constructor. */
WarriorAttribs::WarriorAttribs(const WarriorAttribs& other, const char* /*newName*/)
  : Parameters(other)
{}

//_____________________________________________________________________________
/** Cloner. */
AbsObject* WarriorAttribs::clone(const char* /*newName*/) const
{
  return new WarriorAttribs(*this);
}

//_____________________________________________________________________________
/** Assignment operator. */
WarriorAttribs& WarriorAttribs::operator=(const WarriorAttribs& rhs)
{
  Parameters::operator=(rhs);
  return *this;
}

} // end namespace Torpy

