/** \file      src/lib/Parameter.cxx 
    \brief     Source for Parameter 
    \author    Doug Hague
    \date      24.07.2013
    \copyright See License.txt
*/
#include "Torpy/Parameter.hh"   // this class

namespace Torpy {

//_____________________________________________________________________________
/** Default constructor. */
Parameter::Parameter(const char* name, const char* title,
		     double value, double error,
		     double min, double max)
  : Named("Parameter", name, title),
    mValue(value),
    mError(error),
    mMin(min),
    mMax(max)
{}

//_____________________________________________________________________________
/** Copy constructor. */
Parameter::Parameter(const Parameter& other, const char* newName)
  : Named(other,newName), 
    mValue(other.mValue),
    mError(other.mError),
    mMin(other.mMin),
    mMax(other.mMax)
{
  if(newName && strlen(newName)!=0) setName(newName);
}

//_____________________________________________________________________________
/** Cloner. */
AbsObject* Parameter::clone(const char* newName) const
{
  return new Parameter(*this, newName);
}

//_____________________________________________________________________________
/** Assignment operator. */
Parameter& Parameter::operator=(const Parameter& rhs)
{
  Named::operator=(rhs);
  set(rhs.mValue, rhs.mError, rhs.mMin, rhs.mMax);
  return *this;
}

//_____________________________________________________________________________
/** Equivalence to "zero". 
    Checks is all members are zero.
*/
bool Parameter::isEmpty() const
{
  return (mValue == 0. && 
	  mError == 0. && 
	  mMin   == 0. && 
	  mMax   == 0.);
}

//_____________________________________________________________________________
/** Set all values to zero. */
void Parameter::clear()
{
  mValue = 0.; 
  mError = 0.; 
  mMin   = 0.; 
  mMax   = 1.;
}

//_____________________________________________________________________________
/** Equivalence. 
    Compares Torpy::Named, then member values.
*/
bool Parameter::isEqual(const AbsObject& other) const
{
  if(isSame(other)) return true;

  // check cast
  Parameter* p = (Parameter*)(&other);
  if(!p) return false;

  // check named
  if(string(name()) != p->name()) return false;
  if(string(title()) != p->title()) return false;

  // check members
  return (mValue == p->value() && 
	  mError == p->error() && 
	  mMin   == p->min() && 
	  mMax   == p->max());
}

//_____________________________________________________________________________
/** Set the members values. */
void Parameter::set(double value, double error, double min, double max)
{
  mValue = value;
  mError = error;
  mMin   = min;
  mMax   = max;  
}

//_____________________________________________________________________________
/** Set the range of a parameter. */
void Parameter::setRange(double min, double max)
{
  mMin = min;
  mMax = max;
}

//_____________________________________________________________________________
/** Get the range of a parameter. */
void Parameter::range(double& min, double& max)
{
  min = mMin;
  max = mMax;  
}

} // end namespace Torpy

