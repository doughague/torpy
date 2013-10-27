/** \file      src/lib/Parameters.cxx 
    \brief     Source for Parameters class
    \author    Doug Hague
    \date      03.10.2013
    \copyright See License.txt
*/
#include "Torpy/LogService.hh"
#include "Torpy/Exception.hh"
#include "Torpy/Parameters.hh"

namespace Torpy {

//_____________________________________________________________________________
/** Constructor. */
Parameters::Parameters()
  : AbsObject("Parameters"),
    mPars()
{}

//_____________________________________________________________________________
/** Copy constructor. */
Parameters::Parameters(const Parameters& other, const char* newName)
  : AbsObject(other,newName),
    mPars(other.mPars)
{}

//_____________________________________________________________________________
/** Cloner. */
AbsObject* Parameters::clone(const char* newName) const
{
  return new Parameters(*this, newName);
}

//_____________________________________________________________________________
/** Assignment operator. */
Parameters& Parameters::operator=(const Parameters& rhs)
{
  AbsObject::operator=(rhs);
  mPars = rhs.mPars;
  return *this;
}

//_____________________________________________________________________________
/** Are all the parameters empty? */
bool Parameters::isEmpty() const 
{ 
  if(mPars.empty()) return true;
  for(parCIter it = mPars.begin(); it != mPars.end(); ++it)
    if(!(it->second).isEmpty())
      return false;
  return true;
}

//_____________________________________________________________________________
/** Clear delete all parameter(s). */
void Parameters::clear()
{ 
  mPars.clear();
}

//_____________________________________________________________________________
/** Does this equal other? */
bool Parameters::isEqual(const AbsObject& other) const
{
  if(isSame(other)) return true;

  // check cast
  Parameters* pars = (Parameters*)(&other);
  if(!pars) return false;

  // check size
  if(size() != pars->size()) return false;

  // check members
  for(parCIter it = mPars.begin(); it != mPars.end(); ++it){
    if(!pars->contains(it->first))
      return false;
    if((it->second) != pars->parameter(it->first))
      return false;    
  }
  return true;  
}

//_____________________________________________________________________________
/** Add a parameter to the end of the list. */
bool Parameters::add(const Parameter& parameter)
{
  string pn(parameter.name());
  if(mPars.count(pn) == 1){
    loutW(InputArguments) << "Parameters::add: Parameter with name " << pn.c_str() 
			  << " already in list." << endl;
    return true;    
  }
  mPars[pn] = parameter;
  return false;
}

//_____________________________________________________________________________
/** Remove (erase) a parameter at index idx from the list. */
bool Parameters::erase(string parName)
{
  parIter it = mPars.find(parName);
  if(it == end()){
    loutW(InputArguments) << "Parameters::eraseParameter: Parameter with name " << parName.c_str() 
			  << " not found." << endl;
    return true;
  }
  mPars.erase(it);    
  return false;
}

//_____________________________________________________________________________
/** Set the parameter at index idx in the list. */
bool Parameters::set(const Parameter& parameter)
{
  if(!contains(parameter)){
    loutW(InputArguments) << "Parameters::set: Parameter with name " << parameter.name() 
			  << " not found." << endl;
    return true;
  }
  mPars[string(parameter.name())] = parameter;    
  return false;
}

//_____________________________________________________________________________
/** const Retrieve a parameter named parName from the list. 
    \note Will throw Exception if parName not found.
*/
const Parameter& Parameters::parameter(string parName) const
{
  try{ return mPars.at(parName); } 
  catch(const out_of_range& oor) {
    throw Exception("Parameters::parameter: Parameter not found.");
  }
}

//_____________________________________________________________________________
/** const array-style accessor. 
    \note Will throw Exception if parName not found.
*/
const Parameter& Parameters::operator[](string parName) const
{
  // return mPars[parName];
  return parameter(parName);
}

//_____________________________________________________________________________
/** Retrieve a parameter named parName from the list. */
Parameter& Parameters::parameter(string parName)
{
  try{ return mPars.at(parName); } 
  catch(const out_of_range& oor) {
    throw Exception("Parameters::parameter: Parameter not found.");
  }
}

//_____________________________________________________________________________
/** array-style accessor. 
    \warning Will create at run time if parName not found!
*/
Parameter& Parameters::operator[](string parName)
{
  return mPars[parName];
}

//_____________________________________________________________________________
/** \return true if any of the parameters are equal to parameter. */
bool Parameters::contains(string parName) const
{
  return (mPars.count(parName) == 1);
}

//_____________________________________________________________________________
/** \return true if any of the parameters are equal to parameter. */
bool Parameters::contains(const Parameter& parameter) const
{
  return contains(string(parameter.name()));
}

} // end namespace Torpy
