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
  }

  // --------------------------------------------
  // clean & return
  return 0;
}

