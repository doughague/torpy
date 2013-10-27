/** \file      WarriorAttribs.hh 
    \brief     Header for WarriorAttribs
    \author    Jason Torpy, Doug Hague
    \date      03.10.2013
    \copyright See License.txt
*/
#ifndef TP_WARRIORATTRIBS_HH
#define TP_WARRIORATTRIBS_HH

#include "Torpy/Parameters.hh"  // mother class

namespace Torpy {

/** \class WarriorAttribs
    \brief For holding warrior attributes.
*/
class WarriorAttribs : public Parameters { 
public:
  WarriorAttribs();
  WarriorAttribs(const WarriorAttribs& other, const char* /*newName*/);
  virtual AbsObject* clone(const char* /*newName*/) const;
  virtual WarriorAttribs& operator=(const WarriorAttribs& rhs);
  inline virtual ~WarriorAttribs() { }
};

} // end namespace Torpy

#endif // TP_WARRIORATTRIBS_HH
