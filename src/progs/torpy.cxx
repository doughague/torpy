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
  // Initialize TimeStamp and globalRand
    TimeStamp startTime;
    Random globalRand(startTime.uts());

  // --------------------------------------------
  // Welcome the user and show time stamp
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
  tout << "* It's " << startTime.asDescription() << " (" << startTime.uts() << " UTS)" << endl;
  tout << "*****************************************************************" << endl;


  // --------------------------------------------
  // Initialize warrior vector, warrior variables, and initial warriors
    vector<Warrior> warv;
    int vs1(0), vs2(1); // used to select vector node of warriors fighting replaces old w1/w2 system.
    string entryn(""), entryt("");
    double entryd1(0),entryd2(0),entryd3(0),entryd4(0);
    int entryw(0),entrym(0);

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
    warv.push_back(w2); // coding note: changes to warv[1] != changes to w2
  
    // initialize fatigue to health and bleed; loss of health or fatigue per round
    warv[vs1].fatigue().setValue(warv[vs1].health().value());
    warv[vs2].fatigue().setValue(warv[vs2].health().value());
    
    int w1bleedh (0);
    int w2bleedh (0);
    int w1bleedf (0);
    int w2bleedf (0);

    
  // --------------------------------------------
  // Print warrior info
  tout << endl;
  tout << "***********************************" << endl;
  tout << "Warriors:" << endl;
    // print warrior menu
    for (int i = 0; i < warv.size(); i++) {
        warv[i].getVal(2,i);
    }
  tout << "***********************************" << endl;

  // --------------------------------------------
  // command event loop
  string cmd("m"); // initializes to command menu
  while(cmd != "quit"){
 
      // --------------------------------------------
      // Print command menu

      if(cmd == "m"){
          
      tout << endl;
      tout << "***********************************" << endl;
      tout << "Commands: " << endl;
      tout << "  c (for choose): select other fighers " << endl;
      tout << "  s (for swing): Swing-by-swing fight of " << warv[vs1].name() << " against " << warv[vs2].name() <<"." << endl;
      tout << "  d (for death): To the death fight between " << warv[vs1].name() << " and " << warv[vs2].name() <<"." << endl;
      tout << "  r (for register): Register new warrior." << endl;
      tout << "  quit:  Quit the game and exit." << endl;
      tout << "***********************************" << endl;
          
          // instruct user
          tout << "Command your warriors: ";
          // read command
          std::cin >> cmd;

      }
      
      if(cmd == "c"){
          
          tout << "Warriors: " << endl;
          // print warrior menu
          for (int i = 0; i < warv.size(); i++) {
              warv[i].getVal(2,i);
          }

          tout << "Choose first fighter:";
          std::cin >> vs1;
          tout << "Choose opponent:";
          std::cin >> vs2;
          
          // re-initialize fatigue to health and bleed; loss of health or fatigue per round
          warv[vs1].fatigue().setValue(warv[vs1].health().value());
          warv[vs2].fatigue().setValue(warv[vs2].health().value());
          
          cmd = "m"; // return to main menu

      } // cmd==c
      
      
    // --------------------------------------------
    // replace warrior attributes or add new warriors
    if(cmd == "r"){
        
        // variables initialized above
        // print warrior menu
        for (int i = 0; i < warv.size(); i++) {
            warv[i].getVal(2,i);
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
            
            // reprint warrior menu
            for (int i = 0; i < warv.size(); i++) {
                warv[i].getVal(2,i);
            }
        }
        
        // update warrior values
        
        tout << "Choose number of warrior to update ==> ";
        std::cin >> entryw;
        warv[entryw].getVal(1,entryw);
        
        tout << "Choose attribute (0-5) to update ==> ";
        std::cin >> entrym;
        
        switch (entrym) {
            case 0:
                std::getline(std::cin,entryn); // error handler only; if deleted, programs skips straight to title.
                tout << "enter new warrior name ==> ";
                std::getline(std::cin,entryn);
                tout << "enter new warrior title ==> ";
                std::getline(std::cin,entryt);
                tout << warv[entryw].name() << ", " << warv[entryw].title() << " is now..." << endl;
                warv[entryw].setNameTitle(entryn.c_str(),entryt.c_str());
                tout << warv[entryw].name() << ", " << warv[entryw].title() << endl;
                break;
                
            case 1:
                tout << "enter new prowess value ==> ";
                std::cin >> entryd1;
                tout << "enter new prowess error ==> ";
                std::cin >> entryd2;
                tout << "enter new prowess min ==> ";
                std::cin >> entryd3;
                tout << "enter new prowess max ==> ";
                std::cin >> entryd4;
                warv[entryw].prowess().set(entryd1,entryd2,entryd3,entryd4);
                warv[entryw].getVal(1,entryw);
                break;

            case 2:
                tout << "enter new agility value ==> ";
                std::cin >> entryd1;
                tout << "enter new agility error ==> ";
                std::cin >> entryd2;
                tout << "enter new agility min ==> ";
                std::cin >> entryd3;
                tout << "enter new agility max ==> ";
                std::cin >> entryd4;
                warv[entryw].agility().set(entryd1,entryd2,entryd3,entryd4);
                warv[entryw].getVal(1,entryw);
                break;
                
            case 3:
                tout << "enter new intelligence value ==> ";
                std::cin >> entryd1;
                tout << "enter new intelligence error ==> ";
                std::cin >> entryd2;
                tout << "enter new intelligence min ==> ";
                std::cin >> entryd3;
                tout << "enter new intelligence max ==> ";
                std::cin >> entryd4;
                warv[entryw].intelligence().set(entryd1,entryd2,entryd3,entryd4);
                warv[entryw].getVal(1,entryw);
                break;
                
            case 4:
                tout << "enter new personality value ==> ";
                std::cin >> entryd1;
                tout << "enter new personality error ==> ";
                std::cin >> entryd2;
                tout << "enter new personality min ==> ";
                std::cin >> entryd3;
                tout << "enter new personality max ==> ";
                std::cin >> entryd4;
                warv[entryw].personality().set(entryd1,entryd2,entryd3,entryd4);
                warv[entryw].getVal(1,entryw);
                break;
                
            case 5:
                tout << "enter new health value ==> ";
                std::cin >> entryd1;
                tout << "enter new health error ==> ";
                std::cin >> entryd2;
                tout << "enter new health min ==> ";
                std::cin >> entryd3;
                tout << "enter new health max ==> ";
                std::cin >> entryd4;
                warv[entryw].health().set(entryd1,entryd2,entryd3,entryd4);
                warv[entryw].getVal(1,entryw);
                break;

            default:
                tout << "that's not a valid entry." << endl;
                break;
                
        }
        
        cmd = "m"; // reprint main menu
        
    } // cmd == d

    // --------------------------------------------
    // execute fight, continuously "d" or stepwise "s"
      while(cmd == "d" || cmd == "s"){

        tout << endl;
          
          // determine if attacking or not
        bool w1forf = warv[vs1].forf(); bool w2forf = warv[vs2].forf();
      tout << "fightorflight ==> " << endl;
      !w1forf ? tout << warv[vs1].name() << " prepares a defense." << endl : tout << warv[vs1].name() << " moves to attack." << endl;
      !w2forf ? tout << warv[vs2].name() << " prepares a defense." << endl : tout << warv[vs2].name() << " moves to attack." << endl;

        warv[vs1].disable(warv[vs1].health().value(),warv[vs1].fatigue().value(),w1forf);
        warv[vs2].disable(warv[vs2].health().value(),warv[vs2].fatigue().value(),w2forf);
        
    if(!w1forf && !w2forf){ // more fatigued if already fatigued; recover / adrenaline if not fatigued
          tout << "The two warriors circle each other ==>" << endl;
        if(warv[vs1].fatigue().value()>50){
            tout << warv[vs1].name() << " regains some strength." << endl;
            warv[vs1].fatigue().setValue(warv[vs1].fatigue().value()-3);
        }
        else {
            tout << warv[vs1].name() << " tires slightly." << endl;
            warv[vs1].fatigue().setValue(warv[vs1].fatigue().value()+3);
        }
        
        if(warv[vs2].fatigue().value()>50){
            tout << warv[vs2].name() << " regains some strength." << endl;
            warv[vs2].fatigue().setValue(warv[vs2].fatigue().value()-3);
        }
        else {
            tout << warv[vs2].name() << " tires slightly." << endl;
            warv[vs2].fatigue().setValue(warv[vs2].fatigue().value()+3);
        }
        

    } // both defending
      // if not both defending, then execute fight.
    else {
      tout << "clash ==> " << endl;

        double w1swing = warv[vs1].swing(); double w2swing = warv[vs2].swing();
      tout << warv[vs1].name() << ": " << w1swing << " vs " << warv[vs2].name() << ": " << w2swing << endl;
        double swingResult = w1swing - w2swing;

      tout << "swing result: " << swingResult << endl;
      // after calculating swingresult (who came out ahead in the swing), resolve damage
      if(swingResult<-100){
	tout << warv[vs2].name() << " deals a grievous blow." << endl;
          warv[vs1].health().setValue(warv[vs1].health().value()-20);
          w1bleedh+=5;
          w1bleedf+=5;
      }
      else if(swingResult<-50){
	tout << warv[vs2].name() << " deals a serious blow." << endl;
          warv[vs1].health().setValue(warv[vs1].health().value()-10);
          warv[vs1].fatigue().setValue(warv[vs1].fatigue().value()-10);
      }
      else if(swingResult<50){
	tout << "Weapons clash as the warriors look for an opening." << endl;
          warv[vs1].fatigue().setValue(warv[vs1].fatigue().value()-6);
          warv[vs2].fatigue().setValue(warv[vs2].fatigue().value()-6);
      }
      else if(swingResult<100){
	tout << warv[vs1].name() << " deals a serious blow." << endl;
          warv[vs2].health().setValue(warv[vs2].health().value()-10);
          warv[vs2].fatigue().setValue(warv[vs2].fatigue().value()-10);
      }
      else if(swingResult>=100){
	tout << warv[vs1].name() << " deals a grievous blow." << endl;
          warv[vs2].health().setValue(warv[vs2].health().value()-20);
          w2bleedh+=5;
          w2bleedf+=5;
      }
      else tout << "==> An arrow fletched with human hair lands between the fighters. The demons are displeased and have ended the fight." << endl; // error message only
      
        } // not both defending

        // resolve bleeding

        if(w1bleedh>0||w1bleedf>0) tout << warv[vs1].name() << " continues to bleed." << endl;
        if(w2bleedh>0||w2bleedf>0) tout << warv[vs1].name() << " continues to bleed." << endl;
        
        warv[vs1].health().setValue(warv[vs1].health().value()-w1bleedh);
        warv[vs2].health().setValue(warv[vs2].health().value()-w2bleedh);
        warv[vs1].fatigue().setValue(warv[vs1].fatigue().value()-w1bleedf);
        warv[vs2].fatigue().setValue(warv[vs2].fatigue().value()-w2bleedf);

        // show snapshot of fight.
        tout << warv[vs1].name() << " health: " << warv[vs1].health().value() << "-" << w1bleedh << " per rd, fatigue: " << warv[vs1].fatigue().value() << "-" << w1bleedf << " per rd" << endl;
        if (warv[vs1].health().value() <= 0 || warv[vs1].fatigue().value() <= 0) tout << warv[vs1].name() << " collapses. *****" << endl;
        tout << warv[vs2].name() << " health: " << warv[vs2].health().value() << "-" << w2bleedh << " per rd, fatigue: " << warv[vs2].fatigue().value() << "-" << w2bleedf << " per rd" << endl;
        if (warv[vs2].health().value() <= 0 || warv[vs2].fatigue().value() <= 0) tout << warv[vs2].name() << " collapses. *****" << endl;
        
        // see if a fighter is defeated
        // update: should account for if both are defeated
        if(warv[vs1].health().value()<=0 || warv[vs2].health().value()<=0 || warv[vs1].fatigue().value()<=0 || warv[vs2].fatigue().value()<=0){
            tout << "The fight has ended. *****" << endl;
            cmd = "m";
        }
        else tout << "Awaiting next round." << endl;
        
        // resolve disabilities
        warv[vs1].disable(warv[vs1].health().value(),warv[vs1].fatigue().value(),w1forf);
        warv[vs2].disable(warv[vs2].health().value(),warv[vs2].fatigue().value(),w2forf);
        
        tout << warv[vs1].name() << " disabilities: " << warv[vs1].stun().value() << "/" << warv[vs1].disarm().value() << "/" << warv[vs1].fallen().value() << endl;
        tout << warv[vs2].name() << " disabilities: " << warv[vs2].stun().value() << "/" << warv[vs2].disarm().value() << "/" << warv[vs2].fallen().value() << endl;
          
    if(cmd == "s") { tout << "The fight rages on. Choose s to continue. *****" << endl; cmd = "m"; }
   
      } // while cmd == d
      
  } // while cmd not quit

  // --------------------------------------------
  // clean & return
  // DO NOT REMOVE
  return 0;
}

