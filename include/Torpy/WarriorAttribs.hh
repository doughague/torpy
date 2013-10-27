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

/** \class WarriorAttribsAttribs
    \brief For holding warrior attributes.
*/
class WarriorAttribs : public Parameters { 
public:
  WarriorAttribs();
  WarriorAttribs(const WarriorAttribs& other, const char* /*newName*/);
  virtual AbsObject* clone(const char* /*newName*/) const;
  virtual WarriorAttribs& operator=(const WarriorAttribs& rhs);
  inline virtual ~WarriorAttribs() { }

  // // set / get
  // inline const Parameter& prowess() const { return mProwess; }
  // inline Parameter& prowess(){ return mProwess; }
  // inline const Parameter& agility() const { return mAgility; }
  // inline Parameter& agility(){ return mAgility; }
  // inline const Parameter& intelligence() const { return mIntelligence; }
  // inline Parameter& intelligence(){ return mIntelligence; }
  // inline const Parameter& personality() const { return mPersonality; }
  // inline Parameter& personality(){ return mPersonality; }
  // inline const Parameter& health() const { return mHealth; }
  // inline Parameter& health(){ return mHealth; }
};

} // end namespace Torpy

#endif // TP_WARRIORATTRIBS_HH
