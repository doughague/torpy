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
static const string kPrefix = "[BloBB]";
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
  tout << "*                 /---\\ |        /---\\ /---\\     Bleed          *" << endl;
  tout << "*                 |___/ | /---\\  |___/ |___/     or             *" << endl;
  tout << "*                 |   \\ | |   |  |   \\ |   \\     Be             *" << endl;
  tout << "*                 |___/ | \\___/  |___/ |___/     Bled           *" << endl;
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
  tout << "*****************************************************************" << endl;
  tout << "It's " << startTime.asDescription() << " (" << startTime.uts() << " UTS)" << endl;
  tout << "*****************************************************************" << endl;

  // --------------------------------------------
  // Initialize/seed our "global" random number generator 
  // with the program start time
  Random globalRand(startTime.uts());

  // --------------------------------------------
  // Initialize warriors
  // Alice
  Warrior w1("Alice", "A stronger Warrior");
  w1.setRandom(globalRand);
  w1.prowess().set(60., 20., 0. ,100.);
  w1.agility().set(60., 15., 0. ,100.);
  w1.intelligence().set(60., 5., 0. ,100.);
  w1.personality().set(60., 10., 0. ,100.);
  w1.health().set(60., 5., 0. ,100.);
  // Bob
  Warrior w2("Bob", "A weaker Warrior");
  w2.setRandom(globalRand);
  w2.prowess().set(57.5, 20., 0. ,100.);
  w2.agility().set(50., 15., 0. ,100.);
  w2.intelligence().set(50., 5., 0. ,100.);
  w2.personality().set(50., 10., 0. ,100.);
  w2.health().set(50., 5., 0. ,100.);
    
  // nextround: 
  // the swing-by-swing fight returns here after each swing, 
  // unless the fight is over, assuming I've used the 'goto' function properly.

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
  tout << "  fight: Have " << w1.name() << " fight " << w2.name() << "." << endl;
  tout << "  swing: Pit " << w1.name() << " against " << w2.name() <<"." << endl;
  tout << "  quit:  Quit the game and exit." << endl;
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
 
    if(cmd == "swing"){
      tout << "fightorflight ==> " << endl;
      !w1.forf() ? tout << "1 will attack." << endl : tout << "1 will defend." << endl;
      !w2.forf() ? tout << "2 will attack." << endl : tout << "2 will defend." << endl;
        
      tout << "clash ==> " << endl;
      if(!w1.forf() && !w2.forf()){
	tout << "warriors circle each other" << endl;
	//   w1.fatigue().value()-=3;
	//   w2.fatigue().value()=w2.fatigue().value()-3;
	tout << "1's less fatigued now : " << w1.fatigue().value() << endl;
	tout << "2's less fatigued now : " << w1.fatigue().value() << endl;
      }
      tout << w1.name() << ": " << w1.swing() << ", " << w2.name() << ": " << w2.swing() << endl;
        
      tout << "swings =>" << w1.swing() << endl;
      tout << "swings =>" << w1.swing() << endl;
      tout << "swings =>" << w1.swing() << endl;
      tout << "swings =>" << w1.swing() << endl;
      tout << "swings =>" << w1.swing() << endl;
      tout << "swings =>" << w1.swing() << endl;
      tout << "swings =>" << w1.swing() << endl;
      tout << "swings =>" << w1.swing() << endl;
      tout << "swings =>" << w1.swing() << endl;
        
      double swingResult = w1.swing() - w2.swing();

      tout << "swing result: " << swingResult << endl;
        
      if(swingResult<-100){
	tout << w2.name() << " deals a grievous blow." << endl;
	// health -20, fatigue-5 per round?
      }
      else if(swingResult<-50){
	tout << w2.name() << " deals a serious blow." << endl;
	// health -10, fatigue-5
      }
      else if(swingResult<50){
	tout << "Weapons clash as the warriors look for an opening." << endl;
	// increase fatigue for both
      }
      else if(swingResult<100){
	tout << w1.name() << " deals a serious blow." << endl;
	// health -10, fatigue-5
      }
      else if(swingResult>=100){
	tout << w1.name() << " deals a grievous blow." << endl;
	// health -20, health -5 per round, fatigue-5 per round
      }
      else tout << "the demons have intervened." << endl;
        
      tout << "awaiting next round." << endl;
        
    }
      

    //     switch(swingResult){ // The switch function goes through every logical swingResult value, assigning damage to the fighter with the lower swingResult accordig to how much lower it is.
    //         case <-100.:
    //             if (w1.health().value()<=20) {
    //                 tout << " ==> " w2.name() << "deals a deadly blow!" << endl;
    //                 break; // if less than 20, the fighter is dead and the fight breaks out to continue outside the fight if statement to close out the fight.
    //             }
    //             else {
    //               w1.health().value()-=20; // reduce health by 20 - just a simple result and then the fight goes back to the next round. if/else order required to ensure value doesn't fall below allowed minimum.
    //               tout << " ==> " w2.name() << " hits " << w1.name() << endl;
    //                 goto nextround;
    //             }
    //         case <-50.:
    //             if (w1.health().value()<=10) {
    //                 tout << " ==> " w2.name() << "deals a deadly blow!" << endl;
    //                 break;
    //             }
    //             else {
    //                 w1.health().value()-=10;
    //                 tout << " ==> " w2.name() << " hits " << w1.name() << endl;
    //                 goto nextround;
    //             }
    //         case <50.:
    //             tout << " ==> weapons clash and the fight continues.";
    //             goto nextround;
    //         case <100.:
    //             if (w2.health().value()<=10) {
    //                 tout << " ==> " w1.name() << "deals a deadly blow!" << endl;
    //                 break;
    //             }
    //             else {
    //                 w2.health().value()-=10;
    //                 tout << " ==> " w1.name() << " hits " << w1.name() << endl;
    //                 goto nextround;
    //             }
    //         case >=100.:
    //             if (w2.health().value()<=20) {
    //                 tout << " ==> " w1.name() << "deals a deadly blow!" << endl;
    //                 break;
    //             }
    //             else {
    //                 w2.health().value()-=20;
    //                 tout << " ==> " w1.name() << " hits " << w1.name() << endl;
    //                 goto nextround;
    //             }
    //         default: // accounts for errors only. should never show.
    //             tout << " ==> An arrow fletched with human hair lands between the fighters. The demons are displeased and have ended the fight.";
    //             break;
    //     } // swing result switch
    // } // swing command

      
  } // while cmd not quit

  // --------------------------------------------
  // clean & return
  // DO NOT REMOVE
  return 0;
}

