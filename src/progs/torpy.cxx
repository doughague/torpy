/** \file      torpy.cxx
    \brief     Source for binary executable for torpy.
    \author    Jason Torpy, Doug Hague
    \date      11.10.2013
    \copyright See License.txt
*/
#include "Torpy/Common.hh"
#include "Torpy/TimeStamp.hh"
#include "Torpy/Warrior.hh"

namespace Torpy {
static const string kPrefix = "[torpy]";
#define tout cout << kPrefix.c_str() << ">  "
}

// usings
using namespace Torpy;

//_____________________________________________________________________________
//! print usage to stream
void PrintUsage(ostream& os)
{
  os << endl;
  os << "Usage: torpy" << endl;
  os << "Example: ./bin/torpy" << endl;
}

//_____________________________________________________________________________
//! main method testing the CipCurlData class.
int main(int /*argc*/, char** /*argv*/)
{
  // --------------------------------------------
  // Welcome the user
  tout << "*****************************************************************" << endl;
  tout << "*                 /---\\ /---\\ ----\\ ----\\ \\   /                 *" << endl;
  tout << "*                   |   |   | |_  | |___/  \\ /                  *" << endl;
  tout << "*                   |   |   | |  \\  |       |                   *" << endl;
  tout << "*                   |   \\---/ |   \\ |       |                   *" << endl;
  tout << "*****************************************************************" << endl;
  tout << "* Copyright (C) 2013  Jason Torpy, Doug Hague                   *" << endl;
  tout << "*           This program comes with ABSOLUTELY NO WARRANTY.     *" << endl;
  tout << "*           This is free software, and you are welcome          *" << endl;
  tout << "*           to redistribute it under the conditions of GNU GPL; *" << endl;
  tout << "*           see License.txt                                     *" << endl;
  tout << "*****************************************************************" << endl;

  // Start time-stamp
  TimeStamp startTime;
  tout << endl;
  tout << "***********************************" << endl;
  tout << "It's " << startTime.asDescription() << endl;
  tout << "***********************************" << endl;

  // --------------------------------------------
  // Initialize warriors
  // Alice
  Warrior w1("Alice", "A stronger Warrior");
  w1.prowess().set(60., 5., 0. ,100.);
  w1.agility().set(60., 5., 0. ,100.);
  w1.intelligence().set(60., 5., 0. ,100.);
  w1.personality().set(60., 5., 0. ,100.);
  w1.health().set(60., 5., 0. ,100.);
  // Bob
  Warrior w2("Bob", "A weaker Warrior");
  w2.prowess().set(57.5, 5., 0. ,100.);
  w2.agility().set(50., 5., 0. ,100.);
  w2.intelligence().set(50., 5., 0. ,100.);
  w2.personality().set(50., 5., 0. ,100.);
  w2.health().set(50., 5., 0. ,100.);
    
nextround: // the swing-by-swing fight returns here after each swing, unless the fight is over, assuming I've used the 'goto' function properly.

  // --------------------------------------------
  // Print warrior info
  tout << endl;
  tout << "***********************************" << endl;
  tout << "Warriors: " << endl;
  tout << w1.name() << ": " << w1.title() << endl;
  tout << w2.name() << ": " << w2.title() << endl;
  tout << "***********************************" << endl;

  // --------------------------------------------
  // Print command info
  tout << endl;
  tout << "***********************************" << endl;
  tout << "Commands: " << endl;
  tout << "  fight:  Have " << w1.name() << " fight " << w2.name() << "." << endl;
    tout << "  fight:  Have " << w1.name() << " and " << w2.name() << " trade blows." << endl;
  tout << "   quit:  Quit the game and exit." << endl;
  tout << "***********************************" << endl;

  // --------------------------------------------
  // command event loop
  tout << endl;
  string cmd("");
  while(cmd != "quit"){
    // instruct user
    tout << "Command your warriors: ";
    // read command
    std::cin >> cmd;

    // have a fight
    if(cmd == "fight"){
      int fightResult = w1.fight(w2);
      if(fightResult >= 1) 
	tout << " ==> " << w1.name() << " wins!" << endl;
      else if(fightResult <= -1) 
	tout << " ==> " << w2.name() << " wins!" << endl;
      else 
	tout << " ==> " << "Draw" << endl;
    }
      
      // resolve fight by swings
      if(cmd == "swing"){
          if(!w1.forf() && !w2.forf()) { // forf should resolve as true or false so this should read if w1 forf is false and w2 forf is false, but let me know if it's not.
              if(w1.fatigue().value()>=3.){
                  w1.fatigue().value().set+=3.;
              }
              else w1.fatigue().value()=0;
              if(w2.fatigue().value()>=3.){
                  w2.fatigue().value().set+=3.;
              }
              else w2.fatigue().value()=0;
          tout << " ==> The two warriors circle each other." << endl;
              goto nextround;
          }
          /* In the if statement above, why can't I use the short form for the if above: w1.fatigue().value()>=3 ? w1.fatigue().value()-=3 : w1.fatigue().value()=0;
          */
      // swing results to be expanded below, but simple results is below. Need to initialize swingResult variable.
          double swingResult=w1.swing().value()-w2.swing().value();
          
          switch(swingResult){
              case <-100.:
                  if (w1.health().value()<=20) {
                      tout << " ==> " w2.name() << "deals a deadly blow!" << endl;
                      break;
                  }
                  else {
                    w1.health().value()-=20; // reduce health by 20 - just a simple result and restart. if/else order required to ensure value doesn't fall below allowed minimum.
                    tout << " ==> " w2.name() << " hits " << w1.name() << endl;
                      goto nextround;
                  }
              case <-50.:
                  if (w1.health().value()<=10) {
                      tout << " ==> " w2.name() << "deals a deadly blow!" << endl;
                      break;
                  }
                  else {
                      w1.health().value()-=10;
                      tout << " ==> " w2.name() << " hits " << w1.name() << endl;
                      goto nextround;
                  }
              case <50.:
                  tout << " ==> weapons clash and the fight continues.";
                  goto nextround;
              case <100.: // will trigger on 50-99
                  if (w2.health().value()<=10) {
                      tout << " ==> " w1.name() << "deals a deadly blow!" << endl;
                      break;
                  }
                  else {
                      w2.health().value()-=10;
                      tout << " ==> " w1.name() << " hits " << w1.name() << endl;
                      goto nextround;
                  }
              case >=100.:
                  if (w2.health().value()<=20) {
                      tout << " ==> " w1.name() << "deals a deadly blow!" << endl;
                      break;
                  }
                  else {
                      w2.health().value()-=20;
                      tout << " ==> " w1.name() << " hits " << w1.name() << endl;
                      goto nextround;
                  }
              default: // accounts for
                  tout << " ==> weapons clash and the fight continues.";
                  goto nextround;
          } // swing result switch
      } // swing command

      
  } // while cmd not quit

  // --------------------------------------------
  // clean & return
  return 0;
}

