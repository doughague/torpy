/** \file      src/lib/Named.cxx 
    \brief     Source for Named class.
    \author    Doug Hague
    \date      03.10.2013
    \copyright See License.txt
*/
#include "Torpy/Named.hh"       // this class

namespace Torpy {
// added ID to default const, reach up const, copy const, cloner
    
//_____________________________________________________________________________
/** Default constructor. */
Named::Named(const char* name, const char* title, const int* id)
  : AbsObject("Named"),
    mName(name),
    mTitle(title),
    mID(id)
{}

//_____________________________________________________________________________
/** Protected "reach up" constructor. */
Named::Named(const char* classType, 
	     const char* name, const char* title, const int* id)
  : AbsObject(classType),
    mName(name),
    mTitle(title)    
{}  

//_____________________________________________________________________________
/** Copy constructor. */
Named::Named(const Named& other, const char* newName, const int* id)
  : AbsObject(other),
    mName(other.mName),
    mTitle(other.mTitle)
{
  if(newName && (newName[0]!='\0'))
    setName(newName);
}

//_____________________________________________________________________________
/** Cloner. */
AbsObject* Named::clone(const char* newName, const int* id) const
{
  return new Named(*this, newName);
}

//_____________________________________________________________________________
/** Assignment operator. */
Named& Named::operator=(const Named& rhs)
{
  AbsObject::operator=(rhs);
  mName      = rhs.mName;
  mTitle     = rhs.mTitle;
  mID        = rhs.ID; // added ID
  return *this;
}

//_____________________________________________________________________________
/** Are the members filled? */
bool Named::isEmpty() const
{
  return (!hasName() && !hasTitle() && !hasID());
}

//_____________________________________________________________________________
/** Clear (zero) the name and title. */
void Named::clear()
{ 
  mName  = "";
  mTitle = "";
}

//_____________________________________________________________________________
/** Does this equal other? 
    \note Checks first AbsObject, then name member only
*/
bool Named::isEqual(const AbsObject& other) const
{
  if(isSame(other)) return true;

  // check cast
  Named* named = (Named*)(&other);
  if(!named) return false;

  // check members
  if(mName != named->name()) return false;
  if(mTitle != named->title()) return false;

  //return
  return true;
}

//_____________________________________________________________________________
/** Set the name and title. */
void Named::setNameTitle(const char* name, const char* title)
{
  mName  = name;
  mTitle = title;  
}

} // end namespace Torpy
