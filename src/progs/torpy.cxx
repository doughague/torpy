/** \file      torpy.cxx
    \brief     Source for binary executable for torpy.
    \author    Jason Torpy, Doug Hague
    \date      11.10.2013
    \copyright See License.txt
*/
#include "Torpy/Common.hh"
#include "Torpy/TimeStamp.hh"
#include "Torpy/Warrior.hh"


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
/** Printing instructions. */
static const string kPrefix = "[BloBB]";
#define tout cout << kPrefix.c_str() << ">  "

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
  tout << "*           This aspires to be a combat simulator.              *" << endl;
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
  // Initialize warriors & warrior vector listing
    
    
    vector<Warrior> warv;
    
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

    warv.push_back(w1);
    warv.push_back(w2);
    
    // initialize fatigue to health and bleed; loss of health or fatigue per round
    w1.fatigue().setValue(w1.health().value());
    w2.fatigue().setValue(w2.health().value());

    int w1bleedh (0);
    int w2bleedh (0);
    int w1bleedf (0);
    int w2bleedf (0);

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
  tout << "  s (for swing): Swing-by-swing fight of " << w1.name() << " against " << w2.name() <<"." << endl;
  tout << "  d (for death): To the death fight between " << w1.name() << " and " << w2.name() <<"." << endl;
  tout << "  r (for register): Register new warrior." << endl;
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
    
    // replace warrior attributes (w1 or w2 only to start, but add new warriors or select from available warriors in the future; preferrably from warrior database.)
    if(cmd == "r"){

        // add additional warriors to warrior vector warv
        
        string entryn(""), entryt("");
        double entryd1(0),entryd2(0),entryd3(0),entryd4(0);
        int entryw(0),entrym(0);
        
        // print warrior menu
        for (int i = 0; i < warv.size(); i++) {
            tout << warv[i].getVal(2,i);
        }

        // ask if new warrior
        
        tout << "register new (n) or update existing (u)? ==>";
        std::cin >> entryn;
        
        if(entryn=="n"){
            std::getline(std::cin,entryn); // error handler only; if deleted, programs skips straight to title.
            
            tout << "enter new warrior name ==> ";
            std::getline(std::cin,entryn);
            
            tout << "enter new warrior title ==> ";
            std::getline(std::cin,entryt);
            
            Warrior w3(entryn.c_str(), entryt.c_str());
            w3.setRandom(globalRand);
            warv.push_back(w3);
        }
        
        // update warriors if necessary

        tout << "Choose number of warrior to update:";
        std::cin >> entryw;
        warv[entryw].getVal(1,entryw);
        
        tout << "Choose attribute (0-5) to update ==> ";
        std::cin >> entrym;
        
        switch (entrym) {
            case 0:
                std::getline(std::cin,entryn); // error handler only; if deleted, programs skips straight to title.d
                tout << "enter new warrior name ==> ";
                std::getline(std::cin,entryn);
                tout << "enter new warrior title ==> ";
                std::getline(std::cin,entryt);
                tout << warv[entryw].name() << ", " << warv[entryw].title() << " is now..." << endl;
                warv[entryw].setNameTitle(entryn.c_str(),entryt.c_str());
                tout << warv[entryw].name() << ", " << warv[entryw].title() << endl;
                break;
                
            case 1:
                tout << "enter new prowess value ==>";
                std::cin >> entryd1;
                tout << "enter new prowess error ==>";
                std::cin >> entryd2;
                tout << "enter new prowess min ==>";
                std::cin >> entryd3;
                tout << "enter new prowess max ==>";
                std::cin >> entryd4;
                warv[entryw].prowess().set(entryd1,entryd2,entryd3,entryd4);
                warv[entryw].getVal(1,entryw);
                break;

            case 2:
                tout << "enter new agility value ==>";
                std::cin >> entryd1;
                tout << "enter new agility error ==>";
                std::cin >> entryd2;
                tout << "enter new agility min ==>";
                std::cin >> entryd3;
                tout << "enter new agility max ==>";
                std::cin >> entryd4;
                warv[entryw].agility().set(entryd1,entryd2,entryd3,entryd4);
                warv[entryw].getVal(1,entryw);
                break;
                
            case 3:
                tout << "enter new intelligence value ==>";
                std::cin >> entryd1;
                tout << "enter new intelligence error ==>";
                std::cin >> entryd2;
                tout << "enter new intelligence min ==>";
                std::cin >> entryd3;
                tout << "enter new intelligence max ==>";
                std::cin >> entryd4;
                warv[entryw].intelligence().set(entryd1,entryd2,entryd3,entryd4);
                warv[entryw].getVal(1,entryw);
                break;
                
            case 4:
                tout << "enter new personality value ==>";
                std::cin >> entryd1;
                tout << "enter new personality error ==>";
                std::cin >> entryd2;
                tout << "enter new personality min ==>";
                std::cin >> entryd3;
                tout << "enter new personality max ==>";
                std::cin >> entryd4;
                warv[entryw].personality().set(entryd1,entryd2,entryd3,entryd4);
                warv[entryw].getVal(1,entryw);
                break;
                
            case 5:
                tout << "enter new health value ==>";
                std::cin >> entryd1;
                tout << "enter new health error ==>";
                std::cin >> entryd2;
                tout << "enter new health min ==>";
                std::cin >> entryd3;
                tout << "enter new health max ==>";
                std::cin >> entryd4;
                warv[entryw].health().set(entryd1,entryd2,entryd3,entryd4);
                warv[entryw].getVal(1,entryw);
                break;

            default:
                tout << "that's not a valid entry." << endl;
                break;
                
        }
        
        tout << "enter r, s, d, quit (new warriors not yet implemented for fights)." << endl;
                
    } // cmd == d
        
    // execute fight, continuously "d" or stepwise "s"
      while(cmd == "d" || cmd == "s"){
          
        tout << endl;
          
          // determine if attacking or not
        bool w1forf = w1.forf(); bool w2forf = w2.forf();
      tout << "fightorflight ==> " << endl;
      !w1forf ? tout << w1.name() << " prepares a defense." << endl : tout << w1.name() << " moves to attack." << endl;
      !w2forf ? tout << w2.name() << " prepares a defense." << endl : tout << w2.name() << " moves to attack." << endl;

        w1.disable(w1.health().value(),w1.fatigue().value(),w1forf);
        w2.disable(w2.health().value(),w2.fatigue().value(),w2forf);
        
    if(!w1forf && !w2forf){ // if neither w attacks, no action, just minimal fatigue increase.
          tout << "The two warriors circle each other ==>" << endl;
     // reduce fatigue (recover) if already over 50, become more fatigued if fatigue is low.
        if(w1.fatigue().value()>50){
            tout << w1.name() << " regains some strength." << endl;
            w1.fatigue().setValue(w1.fatigue().value()-3);
        }
        else {
            tout << w1.name() << " tires slightly." << endl;
            w1.fatigue().setValue(w1.fatigue().value()+3);
        }
        
        if(w2.fatigue().value()>50){
            tout << w2.name() << " regains some strength." << endl;
            w2.fatigue().setValue(w2.fatigue().value()-3);
        }
        else {
            tout << w2.name() << " tires slightly." << endl;
            w2.fatigue().setValue(w2.fatigue().value()+3);
        }
        

    } // both defending
      // if not both defending, then execute fight.
    else {
      tout << "clash ==> " << endl;

        double w1swing = w1.swing(); double w2swing = w2.swing();

      tout << w1.name() << ": " << w1swing << " vs " << w2.name() << ": " << w2swing << endl;

          double swingResult = w1swing - w2swing;

      tout << "swing result: " << swingResult << endl;
      // after calculating swingresult (who came out ahead in the swing), resolve damage
      if(swingResult<-100){
	tout << w2.name() << " deals a grievous blow." << endl;
          w1.health().setValue(w1.health().value()-20);
          w1bleedh+=5;
          w1bleedf+=5;
      }
      else if(swingResult<-50){
	tout << w2.name() << " deals a serious blow." << endl;
          w1.health().setValue(w1.health().value()-10);
          w1.fatigue().setValue(w1.fatigue().value()-10);
      }
      else if(swingResult<50){
	tout << "Weapons clash as the warriors look for an opening." << endl;
          w1.fatigue().setValue(w1.fatigue().value()-6);
          w2.fatigue().setValue(w2.fatigue().value()-6);
      }
      else if(swingResult<100){
	tout << w1.name() << " deals a serious blow." << endl;
          w2.health().setValue(w2.health().value()-10);
          w2.fatigue().setValue(w2.fatigue().value()-10);
      }
      else if(swingResult>=100){
	tout << w1.name() << " deals a grievous blow." << endl;
          w2.health().setValue(w2.health().value()-20);
          w2bleedh+=5;
          w2bleedf+=5;
      }
      else tout << "==> An arrow fletched with human hair lands between the fighters. The demons are displeased and have ended the fight." << endl; // error message only
      
        } // not both defending

        // resolve bleeding

        if(w1bleedh>0||w1bleedf>0) tout << w1.name() << " continues to bleed." << endl;
        if(w2bleedh>0||w2bleedf>0) tout << w2.name() << " continues to bleed." << endl;
        
        w1.health().setValue(w1.health().value()-w1bleedh);
        w2.health().setValue(w2.health().value()-w2bleedh);
        w1.fatigue().setValue(w1.fatigue().value()-w1bleedf);
        w2.fatigue().setValue(w2.fatigue().value()-w2bleedf);

        // show snapshot of fight.
        tout << w1.name() << " health: " << w1.health().value() << "-" << w1bleedh << " per rd, fatigue: " << w1.fatigue().value() << "-" << w1bleedf << " per rd" << endl;
        if (w1.health().value() <= 0 || w1.fatigue().value() <= 0) tout << w1.name() << " collapses." << endl;
        tout << w2.name() << " health: " << w2.health().value() << "-" << w2bleedh << " per rd, fatigue: " << w2.fatigue().value() << "-" << w2bleedf << " per rd" << endl;
        if (w2.health().value() <= 0 || w2.fatigue().value() <= 0) tout << w2.name() << " collapses." << endl;
        
        // see if a fighter is defeated
        // update: should account for if both are defeated
        if(w1.health().value()<=0 || w2.health().value()<=0 || w1.fatigue().value()<=0 || w2.fatigue().value()<=0){
            tout << "The fight has ended." << endl;
            cmd = "quit";
        }
        else tout << "Awaiting next round." << endl;
        
        // resolve disabilities
        w1.disable(w1.health().value(),w1.fatigue().value(),w1forf);
        w2.disable(w2.health().value(),w2.fatigue().value(),w2forf);
        
        tout << w1.name() << " disabilities: " << w1.stun().value() << "/" << w1.disarm().value() << "/" << w1.fallen().value() << endl;
        tout << w2.name() << " disabilities: " << w2.stun().value() << "/" << w2.disarm().value() << "/" << w2.fallen().value() << endl;
    
    if(cmd == "s") { cmd = "m"; }
   
      } // while cmd == d
      
  } // while cmd not quit

  // --------------------------------------------
  // clean & return
  // DO NOT REMOVE
  return 0;
}

