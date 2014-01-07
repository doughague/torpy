/** \file      Warrior.hh 
    \brief     Header for Warrior
    \author    Jason Torpy, Doug Hague
    \date      03.10.2013
    \copyright See License.txt
*/
#ifndef TP_WARRIOR_HH
#define TP_WARRIOR_HH

#include "Torpy/Named.hh"           // mother class
#include "Torpy/WarriorAttribs.hh"  // warrior attributes
#include "Torpy/Disability.hh"      // warrior disabilityies
#include "Torpy/Random.hh"          // random number helper

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

  // set / get attributes
  inline const WarriorAttribs& attribs() const { return mAttribs; }
  inline WarriorAttribs& attribs(){ return mAttribs; }  
  // set / get individual attributes
  inline const Parameter& prowess() const { return mAttribs["prowess"]; }
  inline Parameter& prowess(){ return mAttribs["prowess"]; }
  inline const Parameter& agility() const { return mAttribs["agility"]; }
  inline Parameter& agility(){ return mAttribs["agility"]; }
  inline const Parameter& intelligence() const { return mAttribs["intelligence"]; }
  inline Parameter& intelligence(){ return mAttribs["intelligence"]; }
  inline const Parameter& personality() const { return mAttribs["personality"]; }
  inline Parameter& personality(){ return mAttribs["personality"]; }
  inline const Parameter& health() const { return mAttribs["health"]; }
  inline Parameter& health(){ return mAttribs["health"]; }

  // set / get disability
  inline const Disability& disability() const { return mDisability; }
  inline Disability& disability(){ return mDisability; }  
  // set / get individual disabilities
  inline const Parameter& fatigue() const { return mDisability["fatigue"]; }
  inline Parameter& fatigue(){ return mDisability["fatigue"]; }
  inline const Parameter& stun() const { return mDisability["stun"]; }
  inline Parameter& stun(){ return mDisability["stun"]; }
  inline const Parameter& disarm() const { return mDisability["disarm"]; }
  inline Parameter& disarm(){ return mDisability["disarm"]; }
  inline const Parameter& fallen() const { return mDisability["fallen"]; }
  inline Parameter& fallen(){ return mDisability["fallen"]; }
  inline const Parameter& fatigueTime() const { return mDisability["fatigue-time"]; }
  inline Parameter& fatigueTime(){ return mDisability["fatigue-time"]; }
  inline const Parameter& healthTime() const { return mDisability["health-time"]; }
  inline Parameter& healthTime(){ return mDisability["health-time"]; }

  // random helpers
  inline void setRandom(const Random& r){ mRandom = r; }
  inline const Random& getRandom(){ return mRandom; }

  //
  // Action methods
  //
  // fight
  int fight(Warrior& other);
  // choice of attacking - fight or flight
  bool forf();
  // attack action
  double swing();
  // disabilities update
  double disable(int hstat, int fstat);
  // recover after a rest
  double recover();

private:
  WarriorAttribs mAttribs;
  Disability mDisability;
  Random mRandom;
};

} // end namespace Torpy

#endif // TP_WARRIOR_HH
