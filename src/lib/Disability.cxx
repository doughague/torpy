/** \file      src/lib/Disability.cxx 
    \brief     Source for Disability 
    \author    Jason Torpy, Doug Hague
    \date      24.07.2013
    \copyright See License.txt
*/
#include "Torpy/Disability.hh"  // this class

namespace Torpy {

//_____________________________________________________________________________
/** Default constructor. */
Disability::Disability()
  : Parameters()
{
  // add the specific attributes
  add("fatigue", "Fatigue", 0., 0., 0. ,100.);
  add("stun", "Stun", 0., 0., 0. ,1.);
  add("disarm", "Disarm", 0., 0., 0. ,1.);
  add("fallen", "Fallen", 0., 0., 0. ,1.);
  add("fatigue-time", "Fatigue per Time", 0., 0., 0. ,1.);
  add("health-time", "Health per Time", 0., 0., 0. ,1.);
}

//_____________________________________________________________________________
/** Copy constructor. */
Disability::Disability(const Disability& other, const char* /*newName*/)
  : Parameters(other)
{}

//_____________________________________________________________________________
/** Cloner. */
AbsObject* Disability::clone(const char* /*newName*/) const
{
  return new Disability(*this);
}

//_____________________________________________________________________________
/** Assignment operator. */
Disability& Disability::operator=(const Disability& rhs)
{
  Parameters::operator=(rhs);
  return *this;
}

} // end namespace Torpy

