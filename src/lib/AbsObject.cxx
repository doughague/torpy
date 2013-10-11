/** \file      AbsObject.cxx 
    \brief     Source for AbsObject class.
    \author    Doug Hague
    \date      03.10.2013
    \copyright See License.txt
*/
#include "Torpy/AbsObject.hh"   // this class

namespace Torpy {

//_____________________________________________________________________________
/** Default constructor. */
AbsObject::AbsObject(const char* classType) 
  : mClassType(classType)
{}  

//_____________________________________________________________________________
/** Copy constructor. */
AbsObject::AbsObject(const AbsObject& other, const char* /*newName = ""*/) 
  : mClassType(other.mClassType)
{}

//_____________________________________________________________________________
/** Assignment operator. */
AbsObject& AbsObject::operator=(const AbsObject& rhs)
{
  mClassType = rhs.mClassType;
  return *this;
}

//_____________________________________________________________________________
/** Get the class type */
const char* AbsObject::classType() const 
{ 
  return mClassType.c_str(); 
}

//_____________________________________________________________________________
/** Set the class type. */
void AbsObject::setClassType(const char* classType)
{ 
  mClassType = classType; 
}

//_____________________________________________________________________________
/** Is this the same class-type as classType? */
bool AbsObject::isA(const char* classType) const
{
  return (mClassType == classType);
}

//_____________________________________________________________________________
/** Is this the same address as other? */
bool AbsObject::isSame(const AbsObject& other) const
{ 
  return (this == &other); 
}

//_____________________________________________________________________________
/** Is this the same class-type as other? */
bool AbsObject::isSameClass(const AbsObject& other) const
{
  return (mClassType == other.classType());
}

//_____________________________________________________________________________
/** Does this equal other? */
bool AbsObject::isEqual(const AbsObject& other) const
{
  return (isSame(other) && isSameClass(other));
}

//_____________________________________________________________________________
/** Is this object sortable? */
bool AbsObject::isSortable() const 
{ 
  return false; 
}

//_____________________________________________________________________________
/** Compare objects. 
    Derived implementations should return:
    - -1 if other is "less than" this
    - +1 if other is "greater than" this
    -  0 else
*/
  int AbsObject::compare(const AbsObject& /*other*/) const 
{ 
  return 0; 
}

//_____________________________________________________________________________
/** Equivalence operator */
bool AbsObject::operator==(const AbsObject& rhs) const 
{ 
  return isEqual(rhs); 
}

//_____________________________________________________________________________
/** Anti-equivalence operator */
bool AbsObject::operator!=(const AbsObject& rhs) const 
{ 
  return !isEqual(rhs); 
}

//_____________________________________________________________________________
/** Less than operator. */
bool AbsObject::operator<(const AbsObject& other) const
{
  return (compare(other) == -1); 
}

//_____________________________________________________________________________
/** Less than or equal operator. */
bool AbsObject::operator<=(const AbsObject& other) const
{
  return (compare(other) <= 0); 
}

//_____________________________________________________________________________
/** Greater than operator. */
bool AbsObject::operator>(const AbsObject& other) const
{
  return (compare(other) == 1); 
}

//_____________________________________________________________________________
/** Greater than or equal operator. */
bool AbsObject::operator>=(const AbsObject& other) const
{
  return (compare(other) >= 0); 
}

} // end namespace Torpy
