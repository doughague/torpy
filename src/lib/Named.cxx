/** \file      src/lib/Named.cxx
\brief     Source for Named class.
\author    Doug Hague
\date      03.10.2013
\copyright See License.txt
*/
#include "Torpy/Named.hh"       // this class

namespace Torpy {

//_____________________________________________________________________________
/** Default constructor. */
Named::Named(const char* name, const char* title)
: AbsObject("Named"),
mName(name),
mTitle(title)
{}

//_____________________________________________________________________________
/** Protected "reach up" constructor. */
Named::Named(const char* classType,
             const char* name, const char* title)
: AbsObject(classType),
mName(name),
mTitle(title)
{}

//_____________________________________________________________________________
/** Copy constructor. */
Named::Named(const Named& other, const char* newName)
: AbsObject(other),
mName(other.mName),
mTitle(other.mTitle)
{
    if(newName && (newName[0]!='\0'))
        setName(newName);
}

//_____________________________________________________________________________
/** Cloner. */
AbsObject* Named::clone(const char* newName) const
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
    return *this;
}

//_____________________________________________________________________________
/** Are the members filled? */
bool Named::isEmpty() const
{
    return (!hasName() && !hasTitle());
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
