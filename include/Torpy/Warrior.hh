/** \file      Warrior.hh 
    \brief     Header for Warrior
    \author    Jason Torpy, Doug Hague
    \date      03.10.2013
    \copyright See License.txt
*/
#ifndef TP_WARRIOR_HH
#define TP_WARRIOR_HH

#include "Torpy/Named.hh"      // mother class
#include "Torpy/Parameter.hh"  // parameter

namespace Torpy {

/** \class Warrior 
    \brief For holding warrior information.
*/
class Warrior : public Named { 
public:
  Warrior(const char* name = "", const char* title = "");
  Warrior(const Warrior& other, const char* newName = "");
  virtual AbsObject* clone(const char* newName = "") const;
  virtual Warrior& operator=(const Warrior& rhs);
  inline virtual ~Warrior() { }

  // abstract
  bool isEmpty() const;
  void clear();
  bool isEqual(const AbsObject& other) const;

  // set / get
  inline const Parameter& prowess() const { return mProwess; }
  inline Parameter& prowess(){ return mProwess; }
  inline const Parameter& agility() const { return mAgility; }
  inline Parameter& agility(){ return mAgility; }
  inline const Parameter& intelligence() const { return mIntelligence; }
  inline Parameter& intelligence(){ return mIntelligence; }
  inline const Parameter& personality() const { return mPersonality; }
  inline Parameter& personality(){ return mPersonality; }
  inline const Parameter& health() const { return mHealth; }
  inline Parameter& health(){ return mHealth; }

  // fight
  int fight(Warrior& other);

private:
  Parameter mProwess;
  Parameter mAgility;
  Parameter mIntelligence;
  Parameter mPersonality;
  Parameter mHealth;
};

} // end namespace Torpy

#endif // TP_WARRIOR_HH
